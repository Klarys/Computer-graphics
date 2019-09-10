#include "mywindow.h"
#include "ui_mywindow.h"

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);

    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    img = new QImage(szer,wys,QImage::Format_RGB32);
    cpy = new QImage(szer,wys,QImage::Format_RGB32);
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_exitButton_clicked()
{
    qApp->quit();
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}

void MyWindow::on_cleanButton_clicked()
{
    czysc();
    update();
}



void MyWindow::czysc()
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 0; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 0; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 0; // Skladowa RED
        }
    }
}

void MyWindow::zapalpiksel(int x, int y)
{
    int r, g, b;
    kolorPobrany.getRgb(&r, &g, &b);

    if(x>=0 && y>=0 && x<szer && y<wys)
    {
        unsigned char *ptr;
        ptr = img->bits();
        ptr[szer*4*y + 4*x] = b;
        ptr[szer*4*y + 4*x + 1] = g;
        ptr[szer*4*y + 4*x + 2] = r;
    }

    /*
    ptr[szer*4*(y+1) + 4*(x+1)] = 64;
    ptr[szer*4*(y+1) + 4*(x+1) + 1] = 64;
    ptr[szer*4*(y+1) + 4*(x+1) + 2] = 64;
    ptr[szer*4*(y-1) + 4*(x-1)] = 64;
    ptr[szer*4*(y-1) + 4*(x-1) + 1] = 64;
    ptr[szer*4*(y-1) + 4*(x-1) + 2] = 64;
    */
}

void MyWindow::rysujodcinek(int xp, int yp, int xk, int yk)
{
    double a, b, x, y, tmp;
    a = (double)(yk-yp)/(double)(xk-xp);
    b = yk - (a*xk);

    if ((xp>=0)&&(yp>=0)&&(xp<szer)&&(yp<wys))
    {
        if ((xk>=0)&&(yk>=0)&&(xk<szer)&&(yk<wys))
        {

            if(xk != xp)
            {
                if(xk < xp)
                {
                    for(x=xp; x>xk; x--)
                    {
                        y = (a*x) + b;
                        zapalpiksel(x, y);
                    }
                }
                else
                {
                    for(x=xp; x<xk; x++)
                    {
                        y = (a*x) + b;
                        zapalpiksel(x, y);
                    }
                }
                if(yk < yp)
                {
                    for(y=yp; y>yk; y--)
                    {
                        x = (double)(y-b)/a;
                        zapalpiksel(x, y);
                    }
                }
                else
                {
                    for(y=yp; y<yk; y++){
                        x = (double)(y-b)/a;
                        zapalpiksel(x, y);
                    }
                }
            }
            else
            {
                if(yk < yp)
                {
                    tmp=yk;
                    yk=yp;
                    yp=tmp;
                }
                for(y=yp; y<yk; y++)
                {
                    zapalpiksel(xp, y);
                }
            }
        }
    }
}

void MyWindow::rysujokrag()
{
    double radius = qSqrt(((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0)));
    for(int i=0; i<=(radius/sqrt(2)); i++)
    {

        double y = sqrt((radius*radius)-(i*i));
        //zapalpiksel(i,100);

        zapalpiksel(x0+i, y0+qRound(y));
        zapalpiksel(x0+qRound(y), y0+i);

        zapalpiksel(x0+qRound(y),y0-i);
        zapalpiksel(x0+i,y0-qRound(y));

        zapalpiksel(x0-i, y0+qRound(y));
        zapalpiksel(x0-qRound(y), y0+i);

        zapalpiksel(x0-qRound(y), y0-i);
        zapalpiksel(x0-i, y0-qRound(y));
    }
}

void MyWindow::rysujelipse()
{
    double a,b;
    a = x1-x0;
    b = y1-y0;

    for(double t=0; t<2*M_PI; t+=0.001)
    {
        zapalpiksel(x0 - a*cos(t), y0 - b*sin(t));
    }
}

void MyWindow::rysujwielokat()
{
    double a,b;
    a = x1-x0;
    b = y1-y0;

    wielokatx0 = x0 - a*cos(0);
    wielokaty0 = y0 - b*sin(0);
    if(katy>=3)
    {
        for(double t=2*M_PI/katy; t<=2*M_PI; t+=2*M_PI/katy)
        {
            wielokatx1 = x0 - a*cos(t);
            wielokaty1 = y0 - b*sin(t);
            if(wielokaty1>wielokaty0) rysujodcinek(wielokatx1, wielokaty1, wielokatx0, wielokaty0);
            else  rysujodcinek(wielokatx0, wielokaty0, wielokatx1, wielokaty1);
            wielokatx0 = wielokatx1;
            wielokaty0 = wielokaty1;
        }
        rysujodcinek(wielokatx1, wielokaty1, x0 - a*cos(0), y0 - b*sin(0));
    }

}

void MyWindow::floodfill(int x,int y)
{
    unsigned char *ptr;
    ptr = img->bits();

    QStack <QPair <int, int> > stos;
    QPair <int, int> punkt;

    punkt.first = x;
    punkt.second = y;

    //if(!czyzakolorowac(x,y)) return;
    stos.push(punkt);
    while(!stos.empty())
    {
        punkt = stos.pop();
        int xstos, ystos;
        xstos = punkt.first;
        ystos = punkt.second;
        if(czyzakolorowac(xstos,ystos))
        {
            int w=xstos;
            int e=xstos;
            while(czyzakolorowac(w,ystos))
            {
                w--;
            }
            while(czyzakolorowac(e,ystos))
            {
                e++;
            }
            for(int i=w+1; i<e; i++)
            {
                zapalpiksel(i,ystos);
            }
            for(int i=w+1; i<e; i++)
            {
                if(czyzakolorowac(i,ystos+1))
                {
                        punkt.first = i;
                        punkt.second = ystos+1;
                        stos.push(punkt);
                }
                if(czyzakolorowac(i,ystos-1))
                {
                        punkt.first = i;
                        punkt.second = ystos-1;
                        stos.push(punkt);
                }
            }
        }
    }
    return;
}

bool MyWindow::czyzakolorowac(int x, int y)
{
    unsigned char *ptr;
    ptr = img->bits();

    int r,g,b;
    kolorZrodla.getRgb(&r, &g, &b);
    if(x>=0 && y>=0 && x<szer && y<wys)
    {
        if(ptr[szer*4*y + 4*x + 2] == r && ptr[szer*4*y + 4*x + 1] == g && ptr[szer*4*y + 4*x] == b) return true;
        else return false;
    }
    else return false;
}
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    unsigned char *ptr;
    ptr = img->bits();
    *cpy = img->copy(0,0,szer,wys);
    x0 = event->x();
    y0 = event->y();

    x0 -= poczX;
    y0 -= poczY;

    kolorZrodla = QColor(ptr[szer*4*y0 + 4*x0 + 2], ptr[szer*4*y0 + 4*x0 + 1], ptr[szer*4*y0 + 4*x0]);
}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    *img = cpy->copy(0,0,szer,wys);
    x1 = event->x();
    y1 = event->y();

    x1 -= poczX;
    y1 -= poczY;

    if(okrag) rysujokrag();

    if(elipsa) rysujelipse();

    if(wielokat) rysujwielokat();

    update();
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    *img = cpy->copy(0,0,szer,wys);
    x1 = event->x();
    y1 = event->y();

    x1 -= poczX;
    y1 -= poczY;

    if(okrag) rysujokrag();

    if(elipsa) rysujelipse();

    if(wielokat) rysujwielokat();

    if(kolorowanie) floodfill(x0,y0);
    update();
}


void MyWindow::on_checkBox_stateChanged(int arg1)
{
    if(!okrag) okrag = true;
    else okrag = false;
}

void MyWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(!elipsa) elipsa = true;
        else elipsa = false;
}

void MyWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(!wielokat) wielokat = true;
        else wielokat = false;
}

void MyWindow::on_spinBox_valueChanged(int arg1)
{
    katy = arg1;
}

void MyWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(!kolorowanie)
        kolorowanie = true;

        else kolorowanie = false;
}

void MyWindow::on_pushButton_clicked()
{
    kolorPobrany = QColorDialog::getColor();
}
