#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "sfera.h"
#include "tor.h"
#include <QTime>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <Wynik.h>
#include <QString>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    szer = ui->frame->width();
    wys = ui->frame->height();
    poczX = ui->frame->x();
    poczY = ui->frame->y();

    obrazzrodlowy = new QImage(szer,wys,QImage::Format_RGB32);
    obrazTor = new QImage(szer,wys,QImage::Format_RGB32);
    obrazPorazka = new QImage(":/tekstury/GameOverScreen.jpg");
    *obrazPorazka = obrazPorazka->scaled(szer, wys);
    obrazWygrana = new QImage(szer,wys,QImage::Format_RGB32);
    obrazWygrana = new QImage(":/tekstury/VictoryScreen.jpg");
    *obrazWygrana = obrazWygrana->scaled(szer, wys);

    generujObiekty();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*obrazzrodlowy);
}

void MainWindow::zapalPiksel(double x, double y)
{
    unsigned char *wyswietlany;
    wyswietlany = obrazzrodlowy ->bits();
    if(x<szer && y<wys && x>0  && y>0)
    {
        wyswietlany[szer*4*(int)y + 4*(int)x] = 211;
        wyswietlany[szer*4*(int)y + 4*(int)x + 1] = 0;
        wyswietlany[szer*4*(int)y + 4*(int)x + 2] = 148;

//        wyswietlany[szer*4*((int)y) + 4*((int)x+1)] = 211;
//        wyswietlany[szer*4*((int)y) + 4*((int)x+1) + 1] = 0;
//        wyswietlany[szer*4*((int)y) + 4*((int)x+1) + 2] = 148;

//        wyswietlany[szer*4*((int)y+1) + 4*((int)x)] = 211;
//        wyswietlany[szer*4*((int)y+1) + 4*((int)x) + 1] = 0;
//        wyswietlany[szer*4*((int)y+1) + 4*((int)x) + 2] = 148;

//        wyswietlany[szer*4*((int)y) + 4*((int)x+1)] = 211;
//        wyswietlany[szer*4*((int)y) + 4*((int)x+1) + 1] = 0;
//        wyswietlany[szer*4*((int)y) + 4*((int)x+1) + 2] = 148;

//        wyswietlany[szer*4*((int)y-1) + 4*((int)x)] = 211;
//        wyswietlany[szer*4*((int)y-1) + 4*((int)x) + 1] = 0;
//        wyswietlany[szer*4*((int)y-1) + 4*((int)x) + 2] = 148;
    }
}

void MainWindow::on_pushButton_clicked()
{
    //Sfera testSfera((double)0,9,18);
    //testSfera->obliczWspolrzedne2d();

    generujObiekty();
    zycia = 3;
    zebranePunkty = 0;
    Tor testTor(szer, wys);
    testTor.obliczTrojkaty3d();
    testTor.obliczTrojkaty2d();
    testTor.obliczWektoryNormalne();
    testTor.rysujTor(obrazTor);

    int przesunieciePrzeszkody = 10;

    int katObrotu = 15;
    int katObrotuPunktow = 180;
    bool koniecGry = false;
    bool wygrana = false;


    while(true)
    {
        if(katObrotu+15>360)
        {
            katObrotu = 0;
        }
        else {
            katObrotu += 15;
        }
//        if(katObrotuPunktow+15>360)
//        {
//            katObrotuPunktow = 0;
//        }
//        else {
//            katObrotuPunktow += 15;
//        }
        QTime pause = QTime::currentTime().addMSecs(20);
                    while(QTime::currentTime() < pause){
                        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                    }
        wyswietlObraz(obrazTor);

      testSfera->obracaj(katObrotu);
      testSfera->czysc();
      testSfera->obliczTrojkaty3d();
      testSfera->obliczTrojkaty2d();
      testSfera->obliczWektoryNormalne();
      testSfera->obliczTrojkaty2dTekstury();
      rysujZycia();
      rysujLicznikPunktow();

      for(int i=0; i<Punkty.size(); i++)
      {
         Punkty[i]->przesuwaj(przesunieciePrzeszkody, katObrotuPunktow);
         int min = Punkty[i]->najmniejszeZ();
         Punkty[i]->czysc();
         if(min > 0 && min <700) //w tym przedziale obiekty sa widoczne
         {
             Punkty[i]->obliczTrojkaty3d();
             Punkty[i]->obliczTrojkaty2d();
             Punkty[i]->obliczWektoryNormalne();
             Punkty[i]->rysujPunkt(obrazzrodlowy);
         }
         if(min < 0)
          {
             if(Punkty[i]->numerToru == testSfera->pozycja) //wykrycie kolizji
             {
                 zebranePunkty++;
             }
             Punkty.removeFirst();
          }
         rysujZycia();
         rysujLicznikPunktow();
      }

      for(int i=0; i<Przeszkody.size(); i++)
      {
         Przeszkody[i]->przesuwaj(przesunieciePrzeszkody);
         int min = Przeszkody[i]->najmniejszeZ();
         Przeszkody[i]->czysc();
         if(min > 0 && min <700) //w tym przedziale obiekty sa widoczne
         {
             Przeszkody[i]->obliczTrojkaty3d();
             Przeszkody[i]->obliczTrojkaty2d();
             Przeszkody[i]->obliczWektoryNormalne();
             Przeszkody[i]->rysujPrzeszkode(obrazzrodlowy);
         }
         if(min < 0)
          {
             if(Przeszkody[i]->numerToru == testSfera->pozycja) //wykrycie kolizji
             {
                 if(zycia-1<=0)
                 {
                    wyswietlObraz(obrazPorazka);
                    update();
                    koniecGry = true;
                    break;
                 }
                 else
                 {
                    zycia--;
                 }
             }
             if(i==Przeszkody.size()-1 && zycia>0) //oznacza to, ze ostatnia przeszkoda zniknela, wygrana
             {
                 TEST();
                 wyswietlObraz(obrazWygrana);
                 update();
                 koniecGry = true;
                 wygrana = true;
             }

             Przeszkody.removeFirst();
          }
      }
      if(koniecGry)
      {
          break;
      }
      przesunieciePrzeszkody += 5;
      testSfera->rysujSfere(obrazzrodlowy, szer);
      update();
    }
    if(wygrana)
    {
        QString text = QInputDialog::getText(this, "Ranking", "Podaj swój nick:");
        Wynik wynik(text ,zebranePunkty);
        this->ranking.dodajWynik(wynik);
        obrazWygrana = new QImage(":/tekstury/VictoryScreen.jpg");
        *obrazWygrana = obrazWygrana->scaled(szer, wys);
        ranking.rysujRanking(obrazWygrana);
        wyswietlObraz(obrazWygrana);
    }

}

void MainWindow::wyswietlObraz(QImage * obraz)
{
    unsigned char *wyswietlany;
    wyswietlany = obrazzrodlowy ->bits();

    unsigned char *zrodlo;
    zrodlo = obraz ->bits();
    for(int i=0; i<szer; i++)
    {
        for(int j=0; j<wys; j++)
        {

            wyswietlany[szer*4*j + 4*i] =  zrodlo[szer*4*j + 4*i];
            wyswietlany[szer*4*j + 4*i + 1] = zrodlo[szer*4*j + 4*i + 1];
            wyswietlany[szer*4*j + 4*i + 2] = zrodlo[szer*4*j + 4*i + 2];
        }
    }
}


void MainWindow::czarneTlo()
{
    unsigned char *wyswietlany;
    wyswietlany = obrazzrodlowy ->bits();
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

void MainWindow::on_PozycjaWPrawo_clicked()
{
    testSfera->pozycjaWPrawo();
}

void MainWindow::on_PozycjaWLewo_clicked()
{
    testSfera->pozycjaWLewo();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    iloscPrzeszkod = arg1;

}

void MainWindow::generujObiekty()
{
    Przeszkody.clear();
    Punkty.clear();
    srand( time( NULL ) );
    int odleglosc = 250;
    int tor;
    int torPunktu;
    for(int i=0; i<iloscPrzeszkod; i++)
    {
        tor = (std::rand() % 3);
        if(i%4 == 0)
        {
            do
            {
                torPunktu = (std::rand() % 3);   
            }
            while(torPunktu == tor);
            Punkt* tmp2 = new Punkt(odleglosc, szer, wys, torPunktu);
            Punkty.push_back(tmp2);
        }

        Przeszkoda* tmp = new Przeszkoda(odleglosc, szer, wys, tor);
        //Przeszkoda tmp(odleglosc, szer, wys, tor);
        Przeszkody.push_back(tmp);

        odleglosc += ((std::rand() % 30) + 70);
    }
}

void MainWindow::rysujZycia()
{
    double r = 16;
    double odlegosc=0;
    for (int i=0; i<120; i++)
    {
        for(int j=0; j<40; j++)
        {
            if(zycia >= 1 && sqrt((i-20)*(i-20) + (j-20)*(j-20)) < r)
            {
                zapalPiksel(i,j);
            }
            if(zycia >= 2 &&  sqrt((i-60)*(i-60) + (j-20)*(j-20)) < r)
            {
                zapalPiksel(i,j);
            }
            if(zycia >= 3 && sqrt((i-100)*(i-100) + (j-20)*(j-20)) < r)
            {
                zapalPiksel(i,j);
            }
        }
    }
}

void MainWindow::rysujLicznikPunktow()
{

    jednostki = zero;
    if(zebranePunkty%10 == 1)
    {
        jednostki = jeden;
    }
    else if(zebranePunkty%10 == 2)
    {
        jednostki = dwa;
    }
    else if(zebranePunkty%10 == 3)
    {
        jednostki = trzy;
    }
    else if(zebranePunkty%10 == 4)
    {
        jednostki = cztery;
    }
    else if(zebranePunkty%10 == 5)
    {
        jednostki = piec;
    }
    else if(zebranePunkty%10 == 6)
    {
        jednostki = szesc;
    }
    else if(zebranePunkty%10 == 7)
    {
        jednostki = siedem;
    }
    else if(zebranePunkty%10 == 8)
    {
        jednostki = osiem;
    }
    else if(zebranePunkty%10 == 9)
    {
        jednostki = dziewiec;
    }

     dziesiatki = zero;

    if(zebranePunkty>=10 && zebranePunkty<20)
    {
        dziesiatki = jeden;
    }
    else if(zebranePunkty>=20 && zebranePunkty<30)
    {
        dziesiatki = dwa;
    }
    else if(zebranePunkty>=30 && zebranePunkty<40)
    {
        dziesiatki = trzy;
    }
    else if(zebranePunkty>=40 && zebranePunkty<50)
    {
        dziesiatki = cztery;
    }
    else if(zebranePunkty>=50 && zebranePunkty<60)
    {
        dziesiatki = piec;
    }
    else if(zebranePunkty>=60 && zebranePunkty<70)
    {
        dziesiatki = szesc;
    }
    else if(zebranePunkty>=70 && zebranePunkty<80)
    {
        dziesiatki = siedem;
    }
    else if(zebranePunkty>=80 && zebranePunkty<90)
    {
        dziesiatki = osiem;
    }
    else if(zebranePunkty>=90 && zebranePunkty<100)
    {
        dziesiatki = dziewiec;
    }

    unsigned char *wyswietlany;
    wyswietlany = obrazzrodlowy ->bits();

    unsigned char *zrodlo;
    zrodlo = jednostki ->bits();
    int x;
    for(int i=(szer-40); i<szer; i++)
    {
        for(int j=0; j<40; j++)
        {
            x = i-szer+40;
            if(i<szer && j<wys && i>0  && j>0 && x>0 && x<40)
            {
                //if((int)zrodlo[40*4*j + 4*x]>=0 && (int)zrodlo[40*4*j + 4*x] <=255)
                //{
                    wyswietlany[szer*4*j + 4*i] =  zrodlo[40*4*j + 4*x];
               // }

                //if((int)zrodlo[40*4*j + 4*x + 1]>=0 && (int)zrodlo[40*4*j + 4*x + 1] <=255)
                //{
                    wyswietlany[szer*4*j + 4*i + 1] = zrodlo[40*4*j + 4*x + 1];
                //}
                //if((int)zrodlo[40*4*j + 4*x + 2]>=0 && (int)zrodlo[40*4*j + 4*x + 2] <=255)
               // {
                    wyswietlany[szer*4*j + 4*i + 2] = zrodlo[40*4*j + 4*x + 2];
                //}
            }
        }
    }

    zrodlo = dziesiatki ->bits();

    for(int i=(szer-2*40); i<(szer-40); i++)
    {
        for(int j=0; j<40; j++)
        {
            x = i-szer+80;
            if(i<szer && j<wys && i>0  && j>0 && x>0 && x<40)
            {
                wyswietlany[szer*4*j + 4*i] =  zrodlo[40*4*j + 4*x];
                wyswietlany[szer*4*j + 4*i + 1] = zrodlo[40*4*j + 4*x + 1];
                wyswietlany[szer*4*j + 4*i + 2] = zrodlo[40*4*j + 4*x + 2];
            }
        }
    }
}


void MainWindow::TEST()
{

}
