#include "Tor.h"
#include <math.h>

Tor::Tor(int wys,int szer)
{
    this->tekstura = new QImage(":/tekstury/TorTekstura2.jpg");
    *this->tekstura = this->tekstura->scaled(szer, wys);
    this->wys = wys;
    this->szer = szer;
}




void Tor::obliczTrojkaty3d()
{
    QVector <double> punkt3d;
    QVector <QVector <double> > trojkat;

    //0 trojkat
    punkt3d.push_back(-300.0);
    punkt3d.push_back(120.0);
    punkt3d.push_back(0);
    trojkat.push_back(punkt3d);
    punkt3d.clear();

    punkt3d.push_back(-300.0);
    punkt3d.push_back(-500.0);
    punkt3d.push_back(300.0);
    trojkat.push_back(punkt3d);
    punkt3d.clear();

    punkt3d.push_back(300.0);
    punkt3d.push_back(-500.0);
    punkt3d.push_back(300.0);
    trojkat.push_back(punkt3d);
    punkt3d.clear();
    this->trojkaty3d.push_back(trojkat);
    trojkat.clear();
    //1 trojkat
    punkt3d.push_back(300.0);
    punkt3d.push_back(-500.0);
    punkt3d.push_back(300.0);
    trojkat.push_back(punkt3d);
    punkt3d.clear();

    punkt3d.push_back(300.0);
    punkt3d.push_back(120.0);
    punkt3d.push_back(0);
    trojkat.push_back(punkt3d);
    punkt3d.clear();

    punkt3d.push_back(-300.0);
    punkt3d.push_back(120.0);
    punkt3d.push_back(0);
    trojkat.push_back(punkt3d);
    punkt3d.clear();
    this->trojkaty3d.push_back(trojkat);
    trojkat.clear();
}

void Tor::obliczTrojkaty2d()
{
    int d = 100.0;
    QVector <double> punkt2d;
    QVector <QVector <double> > trojkat;
    for(int i=0; i<this->trojkaty3d.size(); i++)
    {
        for(int j=0; j<this->trojkaty3d[i].size(); j++)
        {
            punkt2d.push_back((this->trojkaty3d[i][j][0] * d)/(this->trojkaty3d[i][j][2]+d) +300.0);  //x
            punkt2d.push_back((this->trojkaty3d[i][j][1] * d)/(this->trojkaty3d[i][j][2]+d) +450.0);  //y
            trojkat.push_back(punkt2d);
            punkt2d.clear();
        }
        this->trojkaty2d.push_back(trojkat);
        trojkat.clear();
    }
}

void Tor::obliczWektoryNormalne()
{
    QVector <double> a;
    QVector <double> b;
    QVector <double> wynik;
    for(int i=0; i<this->trojkaty3d.size(); i++)
    {
        for(int j=0; j<3; j++)
        {
            a.push_back(this->trojkaty3d[i][1][j] - this->trojkaty3d[i][0][j]);
            b.push_back(this->trojkaty3d[i][2][j] - this->trojkaty3d[i][0][j]);
        }
        //axb
        wynik.push_back(a[1] * b[2] - a[2] * b[1]);
        wynik.push_back(a[0] * b[2] - a[2] * b[0]);
        wynik.push_back(a[0] * b[1] - a[1] * b[0]);
        this->wektoryNormalne.push_back(wynik);

        a.clear();
        b.clear();
        wynik.clear();
    }

    for(int i=0; i<this->wektoryNormalne.size(); i++)
    {
        double dlugosc = sqrt(this->wektoryNormalne[i][0]*this->wektoryNormalne[i][0] + this->wektoryNormalne[i][1]*this->wektoryNormalne[i][1]+ this->wektoryNormalne[i][2]*this->wektoryNormalne[i][2]);
        for(int j=0; j<3; j++)
        {
            this->wektoryNormalne[i][j] = (double)this->wektoryNormalne[i][j]/dlugosc;
        }
    }
}

void Tor::rysujTor(QImage * obrazDocelowy)
{
    int wyznacznik=0;
    for(int i=0; i<this->wektoryNormalne.size(); i++)
    {
        //wyznacznik = (this->trojkaty2d[i][1][0] - this->trojkaty2d[i][0][0]) * (this->trojkaty2d[i][2][1] - this->trojkaty2d[i][0][1]) -
                        //(this->trojkaty2d[i][1][1] - this->trojkaty2d[i][0][1]) * (this->trojkaty2d[i][2][0] - this->trojkaty2d[i][0][0]);

       // if(wyznacznik>0)
        //{
            rysujFragmentToru(i, obrazDocelowy);
       // }
    }
}

void Tor::rysujFragmentToru(int indeksSciany, QImage * obrazDocelowy)
{
    //obliczkolorsciany(indeksSciany);
    double mian = (this->trojkaty2d[indeksSciany][1][0] - this->trojkaty2d[indeksSciany][0][0])*(this->trojkaty2d[indeksSciany][2][1] - this->trojkaty2d[indeksSciany][0][1]) -
            (this->trojkaty2d[indeksSciany][1][1] - this->trojkaty2d[indeksSciany][0][1])*(this->trojkaty2d[indeksSciany][2][0] - this->trojkaty2d[indeksSciany][0][0]);

    double u,v,w;
    double xt, yt;
    unsigned char *wyswietlany;
    wyswietlany = obrazDocelowy->bits();
    unsigned char *zrodlo;
    zrodlo = tekstura->bits();
    if(mian != 0)
    {
        double minx = std::min(this->trojkaty2d[indeksSciany][0][0], std::min(this->trojkaty2d[indeksSciany][1][0],this->trojkaty2d[indeksSciany][2][0]));
        double miny = std::min(this->trojkaty2d[indeksSciany][0][1], std::min(this->trojkaty2d[indeksSciany][1][1],this->trojkaty2d[indeksSciany][2][1]));

        double maxx = std::max(this->trojkaty2d[indeksSciany][0][0], std::max(this->trojkaty2d[indeksSciany][1][0],this->trojkaty2d[indeksSciany][2][0]));
        double maxy = std::max(this->trojkaty2d[indeksSciany][0][1], std::max(this->trojkaty2d[indeksSciany][1][1],this->trojkaty2d[indeksSciany][2][1]));
        for(double i=minx; i<=maxx+1; i++)
        {
            for(double j=miny; j<=maxy+1; j++)
            {
                v = ((i-this->trojkaty2d[indeksSciany][0][0])*(this->trojkaty2d[indeksSciany][2][1]-this->trojkaty2d[indeksSciany][0][1])
                        -(j-this->trojkaty2d[indeksSciany][0][1])*(this->trojkaty2d[indeksSciany][2][0]-this->trojkaty2d[indeksSciany][0][0]))/mian;

                w = ((this->trojkaty2d[indeksSciany][1][0] - this->trojkaty2d[indeksSciany][0][0])*(j-this->trojkaty2d[indeksSciany][0][1])
                        -(this->trojkaty2d[indeksSciany][1][1] - this->trojkaty2d[indeksSciany][0][1])*(i-this->trojkaty2d[indeksSciany][0][0]))/mian;

                u = 1.0-v-w;

                //if(v>0 && v<1 && u>0 && u<1 && w>0 && w<1)
                if(v>=0 && v<=1 && u>=0 && u<=1 && w>=0 && w<=1) //jest wewnatrz
                {
                    xt = u * this->trojkaty2d[indeksSciany][0][0] + v * this->trojkaty2d[indeksSciany][1][0] + w * this->trojkaty2d[indeksSciany][2][0];
                    yt = u * this->trojkaty2d[indeksSciany][0][1] + v * this->trojkaty2d[indeksSciany][1][1] + w * this->trojkaty2d[indeksSciany][2][1];
                    if(i<this->szer && j<this->wys && i>0  && j>0)
                    {
                        wyswietlany[szer*4*((int)j) + 4*(int)i] = zrodlo[szer*4*((int)yt) + 4*(int)xt];
                        wyswietlany[szer*4*((int)j) + 4*(int)i + 1] = zrodlo[szer*4*((int)yt) + 4*(int)xt + 1];
                        wyswietlany[szer*4*((int)j) + 4*(int)i + 2] = zrodlo[szer*4*((int)yt) + 4*(int)xt + 2];
                    }
                }
            }
        }
    }
}
