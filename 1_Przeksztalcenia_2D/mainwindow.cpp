#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <math.h>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    szer = ui->frame->width();
    wys = ui->frame->height();
    poczX = ui->frame->x();
    poczY = ui->frame->y();

    obrazwyswietlany = new QImage(":/new/prefix1/swinek2.png");
    obrazzrodlowy = new QImage(":/new/prefix1/swinek2.png");
    //*obrazwyswietlany = obrazwyswietlany->scaled(szer,wys);
    //*obrazzrodlowy = obrazzrodlowy->scaled(szer,wys);

    jednostkowa();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*obrazwyswietlany);
}

void MainWindow::bialeTlo()
{
    unsigned char *wyswietlany;
    wyswietlany = obrazwyswietlany ->bits();
    for(int i=0; i<szer; i++)
    {
        for(int j=0; j<wys; j++)
        {

            wyswietlany[szer*4*j + 4*i] = 255;
            wyswietlany[szer*4*j + 4*i + 1] = 255;
            wyswietlany[szer*4*j + 4*i + 2] = 255;
        }
    }
}


void MainWindow::jednostkowa()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(i==j)
            {
                macierzwynikowa[i][j] = 1.0;
            }
            else macierzwynikowa[i][j] = 0;
        }
    }
}

void MainWindow::uzupelnijmprzeksztalcen()
{
    przesuniecieX = -300;
    przesuniecieY = -300;
    przesuniecie();

    obrot();
    skalowanie();

    pochylenie();


    przesuniecieX = 300;
    przesuniecieY = 300;
    przesuniecie();


    przesuniecieX = ui->przesuwaniePL->value();
    przesuniecieY = ui->D->value();
    przesuniecie();

    bialeTlo();
    obliczpiksele();
    update();
    jednostkowa();
}

void MainWindow::przesuniecie()
{
    macierzprzeksztalcen[0][0] = 1; //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = 0; //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = -przesuniecieX;
    macierzprzeksztalcen[1][0] = 0;
    macierzprzeksztalcen[1][1] = 1;
    macierzprzeksztalcen[1][2] = -przesuniecieY;
    macierzprzeksztalcen[2][0] = 0;
    macierzprzeksztalcen[2][1] = 0;
    macierzprzeksztalcen[2][2] = 1;

    przypisztmp();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::skalowanie()
{
    macierzprzeksztalcen[0][0] = 1.0/skalowanieX;
    macierzprzeksztalcen[0][1] = 0;
    macierzprzeksztalcen[0][2] = 0;
    macierzprzeksztalcen[1][0] = 0;
    macierzprzeksztalcen[1][1] = 1.0/skalowanieY;
    macierzprzeksztalcen[1][2] = 0;
    macierzprzeksztalcen[2][0] = 0;
    macierzprzeksztalcen[2][1] = 0;
    macierzprzeksztalcen[2][2] = 1;

    przypisztmp();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::obrot()
{
    double kat = katobrotu * M_PI / 180.0;
    macierzprzeksztalcen[0][0] = cos(kat); //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = -sin(kat); //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = 0;
    macierzprzeksztalcen[1][0] = sin(kat);
    macierzprzeksztalcen[1][1] = cos(kat);
    macierzprzeksztalcen[1][2] = 0;
    macierzprzeksztalcen[2][0] = 0;
    macierzprzeksztalcen[2][1] = 0;
    macierzprzeksztalcen[2][2] = 1;

    przypisztmp();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::pochylenie()
{
    macierzprzeksztalcen[0][0] = 1; //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = pochylenieshX; //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = 0;
    macierzprzeksztalcen[1][0] = pochylenieshY;
    macierzprzeksztalcen[1][1] = 1;
    macierzprzeksztalcen[1][2] = 0;
    macierzprzeksztalcen[2][0] = 0;
    macierzprzeksztalcen[2][1] = 0;
    macierzprzeksztalcen[2][2] = 1;

    przypisztmp();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::przypisztmp()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            tmp[i][j] = 0;//macierzwynikowa[i][j];
        }
    }
}

void MainWindow::przypiszwynikowa()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
             macierzwynikowa[i][j] = tmp[i][j];
        }
    }
}


void MainWindow::obliczpiksele() //oblicza wartosci xz i yz z obrazka zrodlowego dla kazdego piksela obrazka wyswietlanego
{
    double xz, yz;
    for(double i=0; i<szer; i++)
    {
        for(double j=0; j<wys; j++)
        {
            xz = (macierzwynikowa[0][0] * i + macierzwynikowa[0][1] * j + macierzwynikowa[0][2]);
            yz = (macierzwynikowa[1][0] * i + macierzwynikowa[1][1] * j + macierzwynikowa[1][2]);
            zapalPiksel(xz, yz, (int)i, (int)j);
        }
    }
}

void MainWindow::zapalPiksel(double xz, double yz, int xd, int yd) //z zrodlowy, d docelowy
{
    unsigned char *zrodlo;
    unsigned char *wyswietlany;
    wyswietlany = obrazwyswietlany ->bits();
    zrodlo = obrazzrodlowy ->bits();
    if(xz<szer && xd<szer && yz<wys && yd<wys && xz>0 && xd>0 && yz>0 && yd>0)
    {
        wyswietlany[szer*4*yd + 4*xd] = zrodlo[szer*4*(int)yz + 4*(int)xz];
        wyswietlany[szer*4*yd + 4*xd + 1] = zrodlo[szer*4*(int)yz + 4*(int)xz +1];
        wyswietlany[szer*4*yd + 4*xd + 2] = zrodlo[szer*4*(int)yz + 4*(int)xz +2];
    }
}



void MainWindow::on_przesuwaniePL_sliderMoved(int position)
{
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_D_sliderMoved(int position)
{
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_SkalowaniePion_sliderMoved(int position)
{
    skalowanieY = position/100.0;
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_SkalowaniePoziom_sliderMoved(int position)
{
    skalowanieX = position/100.0;
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_Obracanie_sliderMoved(int position)
{
    katobrotu = position;
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_PochylanieX_sliderMoved(int position)
{
    pochylenieshX = position/100.0;
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_PochylanieY_sliderMoved(int position)
{
    pochylenieshY = position/100.0;
    uzupelnijmprzeksztalcen();
}
