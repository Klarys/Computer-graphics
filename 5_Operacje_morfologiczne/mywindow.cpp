#include "mywindow.h"
#include "ui_mywindow.h"
#include <QFileDialog>
#include <QString>

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
    zrodlo = new QImage(szer,wys,QImage::Format_RGB32);
    wynik = new QImage(szer,wys,QImage::Format_RGB32);
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

void MyWindow::odcienieszarosci()
{
    int srednia=0;
    unsigned char *ptr;
    ptr = obrazwczytany->bits();

    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            srednia += ptr[szer*4*i + 4*j]; // Skladowa BLUE
            srednia += ptr[szer*4*i + 4*j + 1]; // Skladowa GREEN
            srednia += ptr[szer*4*i + 4*j + 2]; // Skladowa RED
            srednia/=3;
            ptr[szer*4*i + 4*j] = srednia; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = srednia; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = srednia;
        }
    }
}

void MyWindow::czernibiel()
{
    unsigned char *ptr;
    ptr = obrazwczytany->bits();

    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {

            if(ptr[szer*4*i + 4*j] >128) ptr[szer*4*i + 4*j] = 255;
            else ptr[szer*4*i + 4*j] = 0;
            if(ptr[szer*4*i + 4*j + 1] >128)  ptr[szer*4*i + 4*j + 1] = 255;
            else ptr[szer*4*i + 4*j + 1] = 0;
            if(ptr[szer*4*i + 4*j + 2] >128) ptr[szer*4*i + 4*j + 2] = 255;
            else ptr[szer*4*i + 4*j + 2] =0;
        }
    }
}


void MyWindow::zapalpiksel(int x, int y)
{
    unsigned char *ptr;
    ptr = wynik->bits();
    ptr[szer*4*y + 4*x] = 255;
    ptr[szer*4*y + 4*x + 1] = 255;
    ptr[szer*4*y + 4*x + 2] = 255;
}

void MyWindow::zgaspiksel(int x, int y)
{
    unsigned char *ptr;
    ptr = wynik->bits();
    ptr[szer*4*y + 4*x] = 0;
    ptr[szer*4*y + 4*x + 1] = 0;
    ptr[szer*4*y + 4*x + 2] = 0;

}
QColor MyWindow::kolorpiksela(int x, int y)
{
    unsigned char *ptr;
    ptr = zrodlo->bits();

    if(ptr[szer*4*y + 4*x] == 0 && ptr[szer*4*y + 4*x + 1] == 0 && ptr[szer*4*y + 4*x + 2] == 0) return QColor(0,0,0,255);
    else return QColor(255,255,255,255);
}

void MyWindow::dylatacja()
{
    for(int i=0; i<wys; i++)
    {
        for(int j=0; j<szer; j++)
        {
            for(int k=i-bok/2; k<=i+bok/2; k++)
            {
                for(int l=j-bok/2; l<=j+bok/2; l++)
                {
                    if(k<0 || l<0 || k>=wys || l>=szer || (i!=k && j!=l && kolorpiksela(k,l)==QColor(0,0,0,255)))
                    {
                        zgaspiksel(i,j);
                    }
                }
            }
        }
    }
    *img = *wynik;
    *zrodlo = *wynik;
    update();
}

void MyWindow::erozja()
{
    for(int i=0; i<wys; i++)
    {
        for(int j=0; j<szer; j++)
        {
            for(int k=i-bok/2; k<=i+bok/2; k++)
            {
                for(int l=j-bok/2; l<=j+bok/2; l++)
                {
                    if(k>=0 && l>=0 && k<wys && l<szer && (i!=k && j!=l && kolorpiksela(k,l)==QColor(255,255,255,255)))
                    {
                        zapalpiksel(i,j);
                    }
                }
            }
        }
    }
    *img = *wynik;
    *zrodlo = *wynik;
    update();
}
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    //*cpy = img->copy(0,0,szer,wys);
}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    //*img = cpy->copy(0,0,szer,wys);

    x1 = event->x();
    y1 = event->y();
    update();
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //*img = cpy->copy(0,0,szer,wys);

    update();
}


void MyWindow::on_pushButton_5_clicked() //otwieranie pliku
{
    QString nazwa_pliku = QFileDialog::getOpenFileName(this, "otwieranko", "./");
    if(nazwa_pliku != NULL)
    {
        obrazwczytany = new QImage(nazwa_pliku);
        odcienieszarosci();
        czernibiel();
        *zrodlo = *obrazwczytany;
        *wynik = *obrazwczytany;
        *img = *obrazwczytany;
    }
}

void MyWindow::on_pushButton_clicked() //dylatacja
{
    dylatacja();
}

void MyWindow::on_pushButton_2_clicked() //erozja
{
    erozja();
}

void MyWindow::on_pushButton_6_clicked() //reset
{
    *zrodlo = *obrazwczytany;
    *wynik = *obrazwczytany;
    *img = *obrazwczytany;
    update();
}

void MyWindow::on_pushButton_3_clicked()
{
    erozja();
    dylatacja();
}

void MyWindow::on_pushButton_4_clicked()
{
    dylatacja();
    erozja();
}
