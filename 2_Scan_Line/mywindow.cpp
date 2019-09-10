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
    points.clear();
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

/*
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
*/

void MyWindow::scanline()
{
    int i,j;
    int krawedzie=0;
    //zapalpiksel(200,200);
    for(i=0; i<wys; i++)
    {
            for(j=0; j<szer ;j++)
            {
                if(czykrawedz(j,i))
                {
                    krawedzie++;

                }
                    else if(krawedzie%2==1)
                    {
                    //zapalpiksel(200,200);
                        zapalpiksel(j,i);
                    }

            }
            krawedzie=0;
    }

}

bool MyWindow::czykrawedz(int x, int y)
{
    unsigned char *ptr;
    ptr = img->bits();

    int r,g,b;
    kolorZrodla.getRgb(&r, &g, &b);
    if(x>=0 && y>=0 && x<szer && y<wys)
    {
        if(ptr[szer*4*y + 4*x + 2] != r || ptr[szer*4*y + 4*x + 1] != g || ptr[szer*4*y + 4*x] != b)
        {
                if(ptr[szer*4*y + 4*(x+1) + 2] != r || ptr[szer*4*y + 4*(x+1) + 1] != g || ptr[szer*4*y + 4*(x+1)] != b) return false;
                else if((ptr[szer*4*(y+1) + 4*(x+1) + 2] != r || ptr[szer*4*(y+1) + 4*(x+1) + 1] != g || ptr[szer*4*(y+1) + 4*(x+1)] != b)
                        && (ptr[szer*4*(y+1) + 4*(x-1) + 2] != r || ptr[szer*4*(y+1) + 4*(x-1) + 1] != g || ptr[szer*4*(y+1) + 4*(x-1)] != b)) return false;
                //else if((ptr[szer*4*(y-1) + 4*(x+1) + 2] != r || ptr[szer*4*(y-1) + 4*(x+1) + 1] != g || ptr[szer*4*(y-1) + 4*(x+1)] != b)
                        //&& (ptr[szer*4*(y-1) + 4*(x-1) + 2] != r || ptr[szer*4*(y-1) + 4*(x-1) + 1] != g || ptr[szer*4*(y-1) + 4*(x-1)] != b)) return false;
                else return true;
        }
        else return false;
    }
    else return false;
}
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    unsigned char *ptr;
    ptr = img->bits();
    //*cpy = img->copy(0,0,szer,wys);
    x0 = event->x();
    y0 = event->y();

    x0 -= poczX;
    y0 -= poczY;

    kolorZrodla = QColor(ptr[szer*4*y0 + 4*x0 + 2], ptr[szer*4*y0 + 4*x0 + 1], ptr[szer*4*y0 + 4*x0]);

    if(wielokat2)
    {
        QVector <int> input;
        bool tmp = false;

        input.push_back(event->x());
        input.push_back(event->y());

        input[0] -= poczX;
        input[1] -= poczY;

        //sprawdzanie czy kliknieto na istniejacy punkt
        if(points.size()>=1)
        {

            if(input[0] >= points[0][0]-10 && input[0] <= points[0][0]+10 && input[1] >= points[0][1]-10 && input[1] <= points[0][1]+10)
            {
                rysujodcinek(points[points.size()-1][0], points[points.size()-1][1], points[0][0], points[0][1]);
            }
            else //nowy punkt
            {
                rysujodcinek(input[0],input[1], points[points.size()-1][0], points[points.size()-1][1]);
                points.push_back(input);
            }
        }
        else
        {
            points.push_back(input);
        }

    }
    update();
}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{

    x1 = event->x();
    y1 = event->y();

    x1 -= poczX;
    y1 -= poczY;

    if(okrag)
    {
        *img = cpy->copy(0,0,szer,wys);
        rysujokrag();
        update();
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{

    x1 = event->x();
    y1 = event->y();

    x1 -= poczX;
    y1 -= poczY;

    if(okrag)
    {
        *img = cpy->copy(0,0,szer,wys);
        rysujokrag();
        update();
    }


}


void MyWindow::on_checkBox_stateChanged(int arg1)
{
    if(!okrag) okrag = true;
    else okrag = false;
}
/*
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
*/
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

void MyWindow::on_pushButton_2_clicked()
{
    scanline();
     update();
}

void MyWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(!wielokat2)
        wielokat2 = true;

        else wielokat2 = false;
}
