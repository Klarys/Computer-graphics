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

    obrazwyswietlany = new QImage(szer,wys,QImage::Format_RGB32);

    bialeTlo();
    obliczwspolrzedne2d();
    rysujszescian();
    update();
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

void MainWindow::obliczwspolrzedne2d() // obserwatora w punkcie z=-d
{
    int d = 100;
    for(int i=0; i<8; i++)
    {
         wspolrzedne2d[i][0] = (szescianwynikowy[i][0] * d)/(szescianwynikowy[i][2]+d) +300;  //x
         wspolrzedne2d[i][1] = (szescianwynikowy[i][1] * d)/(szescianwynikowy[i][2]+d) +300;  //y
    }
}

void MainWindow::rysujszescian()
{
    for(int i=0; i<8; i++)
    {
         zapalPiksel(wspolrzedne2d[i][0], wspolrzedne2d[i][1]);
    }
    rysujodcinek(wspolrzedne2d[0][0], wspolrzedne2d[0][1], wspolrzedne2d[1][0], wspolrzedne2d[1][1]);
    rysujodcinek(wspolrzedne2d[0][0], wspolrzedne2d[0][1], wspolrzedne2d[2][0], wspolrzedne2d[2][1]);
    rysujodcinek(wspolrzedne2d[0][0], wspolrzedne2d[0][1], wspolrzedne2d[4][0], wspolrzedne2d[4][1]);

    rysujodcinek(wspolrzedne2d[3][0], wspolrzedne2d[3][1], wspolrzedne2d[1][0], wspolrzedne2d[1][1]);
    rysujodcinek(wspolrzedne2d[3][0], wspolrzedne2d[3][1], wspolrzedne2d[2][0], wspolrzedne2d[2][1]);
    rysujodcinek(wspolrzedne2d[3][0], wspolrzedne2d[3][1], wspolrzedne2d[7][0], wspolrzedne2d[7][1]);

    rysujodcinek(wspolrzedne2d[5][0], wspolrzedne2d[5][1], wspolrzedne2d[1][0], wspolrzedne2d[1][1]);
    rysujodcinek(wspolrzedne2d[5][0], wspolrzedne2d[5][1], wspolrzedne2d[4][0], wspolrzedne2d[4][1]);
    rysujodcinek(wspolrzedne2d[5][0], wspolrzedne2d[5][1], wspolrzedne2d[7][0], wspolrzedne2d[7][1]);

    rysujodcinek(wspolrzedne2d[4][0], wspolrzedne2d[4][1], wspolrzedne2d[6][0], wspolrzedne2d[6][1]);
    rysujodcinek(wspolrzedne2d[6][0], wspolrzedne2d[6][1], wspolrzedne2d[7][0], wspolrzedne2d[7][1]);
    rysujodcinek(wspolrzedne2d[6][0], wspolrzedne2d[6][1], wspolrzedne2d[2][0], wspolrzedne2d[2][1]);
}

void MainWindow::zapalPiksel(int x, int y)
{
    unsigned char *wyswietlany;
    wyswietlany = obrazwyswietlany ->bits();
    if(x<szer && y<wys && x>0  && y>0)
    {
        wyswietlany[szer*4*y + 4*x] = 0;
        wyswietlany[szer*4*y + 4*x + 1] = 0;
        wyswietlany[szer*4*y + 4*x + 2] = 255;
    }
}

void MainWindow::rysujodcinek(int xp, int yp, int xk, int yk)
{
    double a, b, x, y, tmp;
    a = (double)(yk-yp)/(double)(xk-xp);
    b = yk - (a*xk);

            if(xk != xp)
            {
                if(xk < xp)
                {
                    for(x=xp; x>xk; x--)
                    {
                        y = (a*x) + b;
                        zapalPiksel(x, y);
                    }
                }
                else
                {
                    for(x=xp; x<xk; x++)
                    {
                        y = (a*x) + b;
                        zapalPiksel(x, y);
                    }
                }
                if(yk < yp)
                {
                    for(y=yp; y>yk; y--)
                    {
                        x = (double)(y-b)/a;
                        zapalPiksel(x, y);
                    }
                }
                else
                {
                    for(y=yp; y<yk; y++){
                        x = (double)(y-b)/a;
                        zapalPiksel(x, y);
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
                    zapalPiksel(xp, y);
                }
            }
}



void MainWindow::jednostkowa()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(i==j)
            {
                macierzwynikowa[i][j] = 1.0;
            }
            else macierzwynikowa[i][j] = 0;
        }
    }
}


void MainWindow::obliczwspolrzedne3d()
{
    for(int i=0; i<8; i++)
    {

       szescianwynikowy[i][0] = macierzwynikowa[0][0] * szescianpoczatkowy[i][0] + macierzwynikowa[0][1] * szescianpoczatkowy[i][1] +
               macierzwynikowa[0][2] * szescianpoczatkowy[i][2] + macierzwynikowa[0][3];

       szescianwynikowy[i][1] = macierzwynikowa[1][0] * szescianpoczatkowy[i][0] + macierzwynikowa[1][1] * szescianpoczatkowy[i][1] +
               macierzwynikowa[1][2] * szescianpoczatkowy[i][2] + macierzwynikowa[1][3];

       szescianwynikowy[i][2] = macierzwynikowa[2][0] * szescianpoczatkowy[i][0] + macierzwynikowa[2][1] * szescianpoczatkowy[i][1] +
               macierzwynikowa[2][2] * szescianpoczatkowy[i][2] + macierzwynikowa[2][3];
    }
}


void MainWindow::uzupelnijmprzeksztalcen()
{
    bialeTlo();
    skalowanie();

    pochylenieOX();
    pochylenieOY();
    pochylenieOZ();


    przesuniecieX = ui->przesuwaniePL->value();
    przesuniecieY = ui->przesuwanieGD->value();
    przesuniecieZ = ui->przesuwaniePT->value();
    przesuniecie();

    obrotOX();
    obrotOY();
    obrotOZ();

    obliczwspolrzedne3d();
    obliczwspolrzedne2d();
    rysujszescian();
    update();
    jednostkowa();
}

void MainWindow::przesuniecie()
{
    macierzprzeksztalcen[0][0] = 1; //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = 0; //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = 0;
    macierzprzeksztalcen[0][3] = przesuniecieX;

    macierzprzeksztalcen[1][0] = 0;
    macierzprzeksztalcen[1][1] = 1;
    macierzprzeksztalcen[1][2] = 0;
    macierzprzeksztalcen[1][3] = przesuniecieY;

    macierzprzeksztalcen[2][0] = 0;
    macierzprzeksztalcen[2][1] = 0;
    macierzprzeksztalcen[2][2] = 1;
    macierzprzeksztalcen[2][3] = przesuniecieZ;

    macierzprzeksztalcen[3][0] = 0;
    macierzprzeksztalcen[3][1] = 0;
    macierzprzeksztalcen[3][2] = 0;
    macierzprzeksztalcen[3][3] = 1;

    przypisztmp();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::skalowanie()
{
    macierzprzeksztalcen[0][0] = skalowanieX; //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = 0; //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = 0;
    macierzprzeksztalcen[0][3] = 0;

    macierzprzeksztalcen[1][0] = 0;
    macierzprzeksztalcen[1][1] = skalowanieY;
    macierzprzeksztalcen[1][2] = 0;
    macierzprzeksztalcen[1][3] = 0;

    macierzprzeksztalcen[2][0] = 0;
    macierzprzeksztalcen[2][1] = 0;
    macierzprzeksztalcen[2][2] = skalowanieZ;
    macierzprzeksztalcen[2][3] = 0;

    macierzprzeksztalcen[3][0] = 0;
    macierzprzeksztalcen[3][1] = 0;
    macierzprzeksztalcen[3][2] = 0;
    macierzprzeksztalcen[3][3] = 1;

    przypisztmp();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::obrotOX()
{
    double kat = katobrotuOX * M_PI / 180.0;

    macierzprzeksztalcen[0][0] = 1; //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = 0; //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = 0;
    macierzprzeksztalcen[0][3] = 0;

    macierzprzeksztalcen[1][0] = 0;
    macierzprzeksztalcen[1][1] = cos(kat);
    macierzprzeksztalcen[1][2] = -sin(kat);
    macierzprzeksztalcen[1][3] = 0;

    macierzprzeksztalcen[2][0] = 0;
    macierzprzeksztalcen[2][1] = sin(kat);
    macierzprzeksztalcen[2][2] = cos(kat);
    macierzprzeksztalcen[2][3] = 0;

    macierzprzeksztalcen[3][0] = 0;
    macierzprzeksztalcen[3][1] = 0;
    macierzprzeksztalcen[3][2] = 0;
    macierzprzeksztalcen[3][3] = 1;

    przypisztmp();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::obrotOY()
{
    double kat = katobrotuOY * M_PI / 180.0;

    macierzprzeksztalcen[0][0] = cos(kat); //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = 0; //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = sin(kat);
    macierzprzeksztalcen[0][3] = 0;

    macierzprzeksztalcen[1][0] = 0;
    macierzprzeksztalcen[1][1] = 1;
    macierzprzeksztalcen[1][2] = 0;
    macierzprzeksztalcen[1][3] = 0;

    macierzprzeksztalcen[2][0] = -sin(kat);
    macierzprzeksztalcen[2][1] = 0;
    macierzprzeksztalcen[2][2] = cos(kat);
    macierzprzeksztalcen[2][3] = 0;

    macierzprzeksztalcen[3][0] = 0;
    macierzprzeksztalcen[3][1] = 0;
    macierzprzeksztalcen[3][2] = 0;
    macierzprzeksztalcen[3][3] = 1;

    przypisztmp();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::obrotOZ()
{
    double kat = katobrotuOZ * M_PI / 180.0;

    macierzprzeksztalcen[0][0] = cos(kat); //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = -sin(kat); //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = 0;
    macierzprzeksztalcen[0][3] = 0;

    macierzprzeksztalcen[1][0] = sin(kat);
    macierzprzeksztalcen[1][1] = cos(kat);
    macierzprzeksztalcen[1][2] = 0;
    macierzprzeksztalcen[1][3] = 0;

    macierzprzeksztalcen[2][0] = 0;
    macierzprzeksztalcen[2][1] = 0;
    macierzprzeksztalcen[2][2] = 1;
    macierzprzeksztalcen[2][3] = 0;

    macierzprzeksztalcen[3][0] = 0;
    macierzprzeksztalcen[3][1] = 0;
    macierzprzeksztalcen[3][2] = 0;
    macierzprzeksztalcen[3][3] = 1;

    przypisztmp();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::pochylenieOX()
{
    macierzprzeksztalcen[0][0] = 1; //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = 0; //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = 0;
    macierzprzeksztalcen[0][3] = 0;

    macierzprzeksztalcen[1][0] = pochylenieshY;
    macierzprzeksztalcen[1][1] = 1;
    macierzprzeksztalcen[1][2] = 0;
    macierzprzeksztalcen[1][3] = 0;

    macierzprzeksztalcen[2][0] = pochylenieshZ;
    macierzprzeksztalcen[2][1] = 0;
    macierzprzeksztalcen[2][2] = 1;
    macierzprzeksztalcen[2][3] = 0;

    macierzprzeksztalcen[3][0] = 0;
    macierzprzeksztalcen[3][1] = 0;
    macierzprzeksztalcen[3][2] = 0;
    macierzprzeksztalcen[3][3] = 1;

    przypisztmp();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::pochylenieOY()
{
    macierzprzeksztalcen[0][0] = 1; //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = pochylenieshX; //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = 0;
    macierzprzeksztalcen[0][3] = 0;

    macierzprzeksztalcen[1][0] = 0;
    macierzprzeksztalcen[1][1] = 1;
    macierzprzeksztalcen[1][2] = 0;
    macierzprzeksztalcen[1][3] = 0;

    macierzprzeksztalcen[2][0] = 0;
    macierzprzeksztalcen[2][1] = pochylenieshZ;
    macierzprzeksztalcen[2][2] = 1;
    macierzprzeksztalcen[2][3] = 0;

    macierzprzeksztalcen[3][0] = 0;
    macierzprzeksztalcen[3][1] = 0;
    macierzprzeksztalcen[3][2] = 0;
    macierzprzeksztalcen[3][3] = 1;

    przypisztmp();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::pochylenieOZ()
{
    macierzprzeksztalcen[0][0] = 1; //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = 0; //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = pochylenieshX;
    macierzprzeksztalcen[0][3] = 0;

    macierzprzeksztalcen[1][0] = 0;
    macierzprzeksztalcen[1][1] = 1;
    macierzprzeksztalcen[1][2] = pochylenieshY;
    macierzprzeksztalcen[1][3] = 0;

    macierzprzeksztalcen[2][0] = 0;
    macierzprzeksztalcen[2][1] = 0;
    macierzprzeksztalcen[2][2] = 1;
    macierzprzeksztalcen[2][3] = 0;

    macierzprzeksztalcen[3][0] = 0;
    macierzprzeksztalcen[3][1] = 0;
    macierzprzeksztalcen[3][2] = 0;
    macierzprzeksztalcen[3][3] = 1;

    przypisztmp();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                tmp[i][j] += (macierzwynikowa[i][k] * macierzprzeksztalcen[k][j]);

            }
        }
    }
    przypiszwynikowa();
}

void MainWindow::przypisztmp()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            tmp[i][j] = 0;
        }
    }
}

void MainWindow::przypiszwynikowa()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
             macierzwynikowa[i][j] = tmp[i][j];
        }
    }
}

void MainWindow::on_przesuwaniePL_sliderMoved(int position)
{
   uzupelnijmprzeksztalcen();
}

void MainWindow::on_przesuwanieGD_sliderMoved(int position)
{
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_przesuwaniePT_sliderMoved(int position)
{
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_SkalowanieX_sliderMoved(int position)
{
    skalowanieX = position/100.0;
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_SkalowanieY_sliderMoved(int position)
{
    skalowanieY = position/100.0;
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_SkalowanieZ_sliderMoved(int position)
{
    skalowanieZ = position/100.0;
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_ObracanieX_sliderMoved(int position)
{
    katobrotuOX = position;
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_ObracanieY_sliderMoved(int position)
{
    katobrotuOY = position;
    uzupelnijmprzeksztalcen();
}

void MainWindow::on_ObracanieZ_sliderMoved(int position)
{
    katobrotuOZ = position;
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

void MainWindow::on_PochylanieZ_sliderMoved(int position)
{
    pochylenieshZ = position/100.0;
    uzupelnijmprzeksztalcen();
}
