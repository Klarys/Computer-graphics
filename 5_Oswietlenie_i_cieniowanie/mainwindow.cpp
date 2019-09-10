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

    czarneTlo();
    obliczwspolrzedne2d();
    rysujszescian();
    if(sciany)
    {
        oblicztrojkaty();
        widocznoscscian();
    }
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

void MainWindow::czarneTlo()
{
    unsigned char *wyswietlany;
    wyswietlany = obrazwyswietlany ->bits();
    for(int i=0; i<szer; i++)
    {
        for(int j=0; j<wys; j++)
        {

            wyswietlany[szer*4*j + 4*i] = 0;
            wyswietlany[szer*4*j + 4*i + 1] = 0;
            wyswietlany[szer*4*j + 4*i + 2] = 0;
        }
    }
}

void MainWindow::oblicztrojkaty()
{
    trojkatyscian2d[0][0] = std::pair<int, int>(wspolrzedne2d[7][0], wspolrzedne2d[7][1]);
    trojkatyscian2d[0][1] = std::pair<int, int>(wspolrzedne2d[5][0], wspolrzedne2d[5][1]);
    trojkatyscian2d[0][2] = std::pair<int, int>(wspolrzedne2d[1][0], wspolrzedne2d[1][1]);

    trojkatyscian2d[1][0] = std::pair<int, int>(wspolrzedne2d[1][0], wspolrzedne2d[1][1]);
    trojkatyscian2d[1][1] = std::pair<int, int>(wspolrzedne2d[3][0], wspolrzedne2d[3][1]);
    trojkatyscian2d[1][2] = std::pair<int, int>(wspolrzedne2d[7][0], wspolrzedne2d[7][1]);

    trojkatyscian2d[2][0] = std::pair<int, int>(wspolrzedne2d[3][0], wspolrzedne2d[3][1]);
    trojkatyscian2d[2][1] = std::pair<int, int>(wspolrzedne2d[1][0], wspolrzedne2d[1][1]);
    trojkatyscian2d[2][2] = std::pair<int, int>(wspolrzedne2d[0][0], wspolrzedne2d[0][1]);

    trojkatyscian2d[3][0] = std::pair<int, int>(wspolrzedne2d[0][0], wspolrzedne2d[0][1]);
    trojkatyscian2d[3][1] = std::pair<int, int>(wspolrzedne2d[2][0], wspolrzedne2d[2][1]);
    trojkatyscian2d[3][2] = std::pair<int, int>(wspolrzedne2d[3][0], wspolrzedne2d[3][1]);

    trojkatyscian2d[4][0] = std::pair<int, int>(wspolrzedne2d[6][0], wspolrzedne2d[6][1]);
    trojkatyscian2d[4][1] = std::pair<int, int>(wspolrzedne2d[4][0], wspolrzedne2d[4][1]);
    trojkatyscian2d[4][2] = std::pair<int, int>(wspolrzedne2d[5][0], wspolrzedne2d[5][1]);

    trojkatyscian2d[5][0] = std::pair<int, int>(wspolrzedne2d[5][0], wspolrzedne2d[5][1]);
    trojkatyscian2d[5][1] = std::pair<int, int>(wspolrzedne2d[7][0], wspolrzedne2d[7][1]);
    trojkatyscian2d[5][2] = std::pair<int, int>(wspolrzedne2d[6][0], wspolrzedne2d[6][1]);

    trojkatyscian2d[6][0] = std::pair<int, int>(wspolrzedne2d[2][0], wspolrzedne2d[2][1]);
    trojkatyscian2d[6][1] = std::pair<int, int>(wspolrzedne2d[0][0], wspolrzedne2d[0][1]);
    trojkatyscian2d[6][2] = std::pair<int, int>(wspolrzedne2d[4][0], wspolrzedne2d[4][1]);

    trojkatyscian2d[7][0] = std::pair<int, int>(wspolrzedne2d[4][0], wspolrzedne2d[4][1]);
    trojkatyscian2d[7][1] = std::pair<int, int>(wspolrzedne2d[6][0], wspolrzedne2d[6][1]);
    trojkatyscian2d[7][2] = std::pair<int, int>(wspolrzedne2d[2][0], wspolrzedne2d[2][1]);

    trojkatyscian2d[8][0] = std::pair<int, int>(wspolrzedne2d[5][0], wspolrzedne2d[5][1]);
    trojkatyscian2d[8][1] = std::pair<int, int>(wspolrzedne2d[4][0], wspolrzedne2d[4][1]);
    trojkatyscian2d[8][2] = std::pair<int, int>(wspolrzedne2d[0][0], wspolrzedne2d[0][1]);

    trojkatyscian2d[9][0] = std::pair<int, int>(wspolrzedne2d[0][0], wspolrzedne2d[0][1]);
    trojkatyscian2d[9][1] = std::pair<int, int>(wspolrzedne2d[1][0], wspolrzedne2d[1][1]);
    trojkatyscian2d[9][2] = std::pair<int, int>(wspolrzedne2d[5][0], wspolrzedne2d[5][1]);

    trojkatyscian2d[10][0] = std::pair<int, int>(wspolrzedne2d[6][0], wspolrzedne2d[6][1]);
    trojkatyscian2d[10][1] = std::pair<int, int>(wspolrzedne2d[7][0], wspolrzedne2d[7][1]);
    trojkatyscian2d[10][2] = std::pair<int, int>(wspolrzedne2d[3][0], wspolrzedne2d[3][1]);

    trojkatyscian2d[11][0] = std::pair<int, int>(wspolrzedne2d[3][0], wspolrzedne2d[3][1]);
    trojkatyscian2d[11][1] = std::pair<int, int>(wspolrzedne2d[2][0], wspolrzedne2d[2][1]);
    trojkatyscian2d[11][2] = std::pair<int, int>(wspolrzedne2d[6][0], wspolrzedne2d[6][1]);

    QVector <int> wspolrzedne;
    QVector <QVector <int> > trojkat;

    //TROJKAT 0
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[7][0]); //x
    wspolrzedne.push_back(szescianwynikowy[7][1]); //y
    wspolrzedne.push_back(szescianwynikowy[7][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[5][0]); //x
    wspolrzedne.push_back(szescianwynikowy[5][1]); //y
    wspolrzedne.push_back(szescianwynikowy[5][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[1][0]); //x
    wspolrzedne.push_back(szescianwynikowy[1][1]); //y
    wspolrzedne.push_back(szescianwynikowy[1][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 1
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[1][0]); //x
    wspolrzedne.push_back(szescianwynikowy[1][1]); //y
    wspolrzedne.push_back(szescianwynikowy[1][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[3][0]); //x
    wspolrzedne.push_back(szescianwynikowy[3][1]); //y
    wspolrzedne.push_back(szescianwynikowy[3][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[7][0]); //x
    wspolrzedne.push_back(szescianwynikowy[7][1]); //y
    wspolrzedne.push_back(szescianwynikowy[7][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 2
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[3][0]); //x
    wspolrzedne.push_back(szescianwynikowy[3][1]); //y
    wspolrzedne.push_back(szescianwynikowy[3][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[1][0]); //x
    wspolrzedne.push_back(szescianwynikowy[1][1]); //y
    wspolrzedne.push_back(szescianwynikowy[1][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[0][0]); //x
    wspolrzedne.push_back(szescianwynikowy[0][1]); //y
    wspolrzedne.push_back(szescianwynikowy[0][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 3
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[0][0]); //x
    wspolrzedne.push_back(szescianwynikowy[0][1]); //y
    wspolrzedne.push_back(szescianwynikowy[0][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[2][0]); //x
    wspolrzedne.push_back(szescianwynikowy[2][1]); //y
    wspolrzedne.push_back(szescianwynikowy[2][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[3][0]); //x
    wspolrzedne.push_back(szescianwynikowy[3][1]); //y
    wspolrzedne.push_back(szescianwynikowy[3][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 4
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[6][0]); //x
    wspolrzedne.push_back(szescianwynikowy[6][1]); //y
    wspolrzedne.push_back(szescianwynikowy[6][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[4][0]); //x
    wspolrzedne.push_back(szescianwynikowy[4][1]); //y
    wspolrzedne.push_back(szescianwynikowy[4][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[5][0]); //x
    wspolrzedne.push_back(szescianwynikowy[5][1]); //y
    wspolrzedne.push_back(szescianwynikowy[5][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 5
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[5][0]); //x
    wspolrzedne.push_back(szescianwynikowy[5][1]); //y
    wspolrzedne.push_back(szescianwynikowy[5][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[7][0]); //x
    wspolrzedne.push_back(szescianwynikowy[7][1]); //y
    wspolrzedne.push_back(szescianwynikowy[7][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[6][0]); //x
    wspolrzedne.push_back(szescianwynikowy[6][1]); //y
    wspolrzedne.push_back(szescianwynikowy[6][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 6
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[2][0]); //x
    wspolrzedne.push_back(szescianwynikowy[2][1]); //y
    wspolrzedne.push_back(szescianwynikowy[2][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[0][0]); //x
    wspolrzedne.push_back(szescianwynikowy[0][1]); //y
    wspolrzedne.push_back(szescianwynikowy[0][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[4][0]); //x
    wspolrzedne.push_back(szescianwynikowy[4][1]); //y
    wspolrzedne.push_back(szescianwynikowy[4][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 7
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[4][0]); //x
    wspolrzedne.push_back(szescianwynikowy[4][1]); //y
    wspolrzedne.push_back(szescianwynikowy[4][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[6][0]); //x
    wspolrzedne.push_back(szescianwynikowy[6][1]); //y
    wspolrzedne.push_back(szescianwynikowy[6][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[2][0]); //x
    wspolrzedne.push_back(szescianwynikowy[2][1]); //y
    wspolrzedne.push_back(szescianwynikowy[2][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 8
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[5][0]); //x
    wspolrzedne.push_back(szescianwynikowy[5][1]); //y
    wspolrzedne.push_back(szescianwynikowy[5][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[4][0]); //x
    wspolrzedne.push_back(szescianwynikowy[4][1]); //y
    wspolrzedne.push_back(szescianwynikowy[4][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[0][0]); //x
    wspolrzedne.push_back(szescianwynikowy[0][1]); //y
    wspolrzedne.push_back(szescianwynikowy[0][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 9
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[0][0]); //x
    wspolrzedne.push_back(szescianwynikowy[0][1]); //y
    wspolrzedne.push_back(szescianwynikowy[0][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[1][0]); //x
    wspolrzedne.push_back(szescianwynikowy[1][1]); //y
    wspolrzedne.push_back(szescianwynikowy[1][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[5][0]); //x
    wspolrzedne.push_back(szescianwynikowy[5][1]); //y
    wspolrzedne.push_back(szescianwynikowy[5][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 10
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[6][0]); //x
    wspolrzedne.push_back(szescianwynikowy[6][1]); //y
    wspolrzedne.push_back(szescianwynikowy[6][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[7][0]); //x
    wspolrzedne.push_back(szescianwynikowy[7][1]); //y
    wspolrzedne.push_back(szescianwynikowy[7][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[3][0]); //x
    wspolrzedne.push_back(szescianwynikowy[3][1]); //y
    wspolrzedne.push_back(szescianwynikowy[3][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 11
    //1 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[3][0]); //x
    wspolrzedne.push_back(szescianwynikowy[3][1]); //y
    wspolrzedne.push_back(szescianwynikowy[3][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[2][0]); //x
    wspolrzedne.push_back(szescianwynikowy[2][1]); //y
    wspolrzedne.push_back(szescianwynikowy[2][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(szescianwynikowy[6][0]); //x
    wspolrzedne.push_back(szescianwynikowy[6][1]); //y
    wspolrzedne.push_back(szescianwynikowy[6][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    trojkatyscian3d.push_back(trojkat);
    trojkat.clear();

}

void MainWindow::obliczwektorynormalne()
{
    QVector <double> a;
    QVector <double> b;
    QVector <double> wynik;
    for(int i=0; i<trojkatyscian3d.size(); i++)
    {
        for(int j=0; j<3; j++)
        {
            a.push_back(trojkatyscian3d[i][1][j] - trojkatyscian3d[i][0][j]);
            b.push_back(trojkatyscian3d[i][2][j] - trojkatyscian3d[i][0][j]);
        }
        //axb
        wynik.push_back(a[1] * b[2] - a[2] * b[1]);
        wynik.push_back(a[0] * b[2] - a[2] * b[0]);
        wynik.push_back(a[0] * b[1] - a[1] * b[0]);
        wektorynormalne.push_back(wynik);

        a.clear();
        b.clear();
        wynik.clear();
    }

    for(int i=0; i<wektorynormalne.size(); i++)
    {
        double dlugosc = sqrt(wektorynormalne[i][0]*wektorynormalne[i][0] + wektorynormalne[i][1]*wektorynormalne[i][1]+ wektorynormalne[i][2]*wektorynormalne[i][2]);
        for(int j=0; j<3; j++)
        {
            wektorynormalne[i][j] = (double)wektorynormalne[i][j]/dlugosc;
        }
    }
}

void MainWindow::obliczkolorsciany(int indekssciany) //indeks sciany jest indeksem trojkata z trojkatsciany3d
{
    int I = 0;
    int c = 255; //kolor zrodla
    double amb = 0.2; //ambient
    double diff = 0.8; //diffuse
    double cl = 1.0; //kolor swiatla (1)
    int m = 100;
    double sl = 0.3; //specular light
    QVector <double> l{-50,0,-100}; //wektor zrodlo swiatla
    QVector <double> h; //w połowie między zrodlem swiatla a obserwujacym
    QVector <double> v{0,0,-100};


    //normalizowanie l
    double dlugosc = sqrt(l[0]*l[0] + l[1]*l[1] + l[2]*l[2]);
    for(int i=0; i<3; i++)
    {
        l[i] = l[i]/dlugosc;
    }

    dlugosc = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    for(int i=0; i<3; i++)
    {
        v[i] = v[i]/dlugosc;
    }

    //obliczanie h
    for(int i=0; i<3; i++)
    {
        h.push_back(v[i] + l[i]);
    }

    dlugosc = sqrt(h[0]*h[0] + h[1]*h[1] + h[2]*h[2]);
    for(int i=0; i<3; i++)
    {
        h[i] = h[i]/dlugosc;
    }

    //dot product 1
    double product1=0;


    for (int i = 0; i<3; i++)
    {
        product1 = product1 + wektorynormalne[indekssciany][i] * l[i]; //sprawdzic czy nie trzeba znormalizowac zrodla l
    }
    //dot product 2
    double product2=0;


    for (int i = 0; i<3; i++)
    {
        product2 = product2 + wektorynormalne[indekssciany][i] * h[i]; //sprawdzic czy nie trzeba znormalizowac zrodla l
    }

    I = c*(amb +diff*product1) + cl*sl*pow(product2,m);

    double skalar = wektorynormalne[indekssciany][0]*v[0] + wektorynormalne[indekssciany][1]*v[1] + wektorynormalne[indekssciany][2]*v[2];
    if(skalar>=0)
    {
        skalar = 0;
    }
    else {
        skalar = skalar *(-1);
    }


    if(I<0)
    {
        I = I*(-1);
    }

 kolor = skalar*255;
}

void MainWindow::widocznoscscian()
{
    int wyznacznik=0;
    for(int i=0; i<12; i++)
    {
        wyznacznik = (trojkatyscian2d[i][1].first - trojkatyscian2d[i][0].first) * (trojkatyscian2d[i][2].second - trojkatyscian2d[i][0].second) -
                        (trojkatyscian2d[i][1].second - trojkatyscian2d[i][0].second) * (trojkatyscian2d[i][2].first - trojkatyscian2d[i][0].first);

        if(wyznacznik>0)
        {
            rysujsciane(i);
        }
    }
}

void MainWindow::rysujsciane(int indekssciany) //indeks sciany jest indeksem trojkata z trojkatsciany2d
{
    obliczkolorsciany(indekssciany);
    double mian = (trojkatyscian2d[indekssciany][1].first - trojkatyscian2d[indekssciany][0].first)*(trojkatyscian2d[indekssciany][2].second - trojkatyscian2d[indekssciany][0].second) -
            (trojkatyscian2d[indekssciany][1].second - trojkatyscian2d[indekssciany][0].second)*(trojkatyscian2d[indekssciany][2].first - trojkatyscian2d[indekssciany][0].first);

    double u,v,w;
    if(mian != 0)
    {
        for(double i=0; i<wys; i++)
        {
            for(double j=0; j<szer; j++)
            {
                v = ((i-trojkatyscian2d[indekssciany][0].first)*(trojkatyscian2d[indekssciany][2].second-trojkatyscian2d[indekssciany][0].second)
                        -(j-trojkatyscian2d[indekssciany][0].second)*(trojkatyscian2d[indekssciany][2].first-trojkatyscian2d[indekssciany][0].first))/mian;

                w = ((trojkatyscian2d[indekssciany][1].first - trojkatyscian2d[indekssciany][0].first)*(j-trojkatyscian2d[indekssciany][0].second)
                        -(trojkatyscian2d[indekssciany][1].second - trojkatyscian2d[indekssciany][0].second)*(i-trojkatyscian2d[indekssciany][0].first))/mian;

                u = 1.0-v-w;

                if(v>=0 && v<=1 && u>=0 && u<=1 && w>=0 && w<=1) //jest wewnatrz
                {
                    zapalPikselCieniowanie(i, j);
                }

            }
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


void MainWindow::zapalPikselCieniowanie(int x, int y)
{
    unsigned char *wyswietlany;
    wyswietlany = obrazwyswietlany ->bits();
    if(x<szer && y<wys && x>0  && y>0)
    {
        wyswietlany[szer*4*y + 4*x] = 0;
        wyswietlany[szer*4*y + 4*x + 1] = 0;
        wyswietlany[szer*4*y + 4*x + 2] = kolor;
    }
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
    trojkatyscian3d.clear();
    wektorynormalne.clear();
   // trojkatyscian2d.clear();
    czarneTlo();
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
    if(!sciany)rysujszescian();

    if(sciany)
    {
        oblicztrojkaty();
        obliczwektorynormalne();
        widocznoscscian();
    }

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

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(sciany == false)
    {
        sciany = true;
    }
    else
    {
        sciany = false;
    }
    uzupelnijmprzeksztalcen();
}
