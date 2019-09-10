#include "Punkt.h"
#include <cmath>

Punkt::Punkt(int z, int szer, int wys, int tor)
{
    this->szer = szer;
    this->wys = wys;
    this->numerToru = tor;
    QVector <double> wspolrzedne;

    if(tor == 0)
    {
        for(int i=0; i<4; i++)
        {
            this->wspolrzedne3d[i][0] = this->wspolrzedne3d[i][0]-100;
        }
    }
    if(tor == 2)
    {
        for(int i=0; i<4; i++)
        {
            this->wspolrzedne3d[i][0] = this->wspolrzedne3d[i][0]+100;
        }
    }

    for(int i=0; i<4; i++)
    {
        this->wspolrzedne3d[i][2] += z;
    }

    for(int i=0; i<4; i++)
    {
        for(int i=0; i<3; i++)
        {
            wspolrzedne.push_back(0);
        }
        wspolrzedne.push_back(1);
        this->wspolrzedne3dprzek.push_back(wspolrzedne);
        wspolrzedne.clear();
    }
}

void Punkt::obliczTrojkaty3d()
{
    QVector <QVector <double> > trojkat;
    QVector <double> wspolrzedne;
    //TROJKAT 0
    //1 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[2][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[2][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[2][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[0][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[0][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[0][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[3][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[3][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[3][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    this->trojkaty3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 1
    //1 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[2][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[2][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[2][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[3][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[3][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[3][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[1][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[1][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[1][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    this->trojkaty3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 2
    //1 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[1][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[1][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[1][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[3][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[3][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[3][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[0][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[0][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[0][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    this->trojkaty3d.push_back(trojkat);
    trojkat.clear();

    //TROJKAT 3
    //1 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[0][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[0][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[0][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //2 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[1][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[1][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[1][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    //3 wierzcholek
    wspolrzedne.push_back(this->wspolrzedne3dprzek[2][0]); //x
    wspolrzedne.push_back(this->wspolrzedne3dprzek[2][1]); //y
    wspolrzedne.push_back(this->wspolrzedne3dprzek[2][2]); //z
    trojkat.push_back(wspolrzedne);
    wspolrzedne.clear();
    this->trojkaty3d.push_back(trojkat);
    trojkat.clear();
}

void Punkt::obliczTrojkaty2d()
{
    int d = 100.0;
    QVector <double> punkt2d;
    QVector <QVector <double> > trojkat;
    for(int i=0; i<this->trojkaty3d.size(); i++)
    {
        for(int j=0; j<this->trojkaty3d[i].size(); j++)
        {
            punkt2d.push_back((this->trojkaty3d[i][j][0] * d)/(this->trojkaty3d[i][j][2]+d) +300.0);  //x
            punkt2d.push_back((this->trojkaty3d[i][j][1] * d)/(this->trojkaty3d[i][j][2]+d) +300.0);  //y
            trojkat.push_back(punkt2d);
            punkt2d.clear();
        }
        this->trojkaty2d.push_back(trojkat);
        trojkat.clear();
    }
}

void Punkt::obliczWektoryNormalne()
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

void Punkt::przesuwaj(int pikselePrzesuniecia,int katObrotu)
{
   double macierzprzeksztalcen[4][4];

//    macierzprzeksztalcen[0][0] = 1;
//    macierzprzeksztalcen[0][1] = 0;
//    macierzprzeksztalcen[0][2] = 0;
//    macierzprzeksztalcen[0][3] = 0;

//    macierzprzeksztalcen[1][0] = 0;
//    macierzprzeksztalcen[1][1] = 1;
//    macierzprzeksztalcen[1][2] = 0;
//    macierzprzeksztalcen[1][3] = 100;

//    macierzprzeksztalcen[2][0] = 0;
//    macierzprzeksztalcen[2][1] = 0;
//    macierzprzeksztalcen[2][2] = 1;
//    macierzprzeksztalcen[2][3] = -pikselePrzesuniecia; //- bo maja sie przysuwac w strone obserwatora

//    macierzprzeksztalcen[3][0] = 0;
//    macierzprzeksztalcen[3][1] = 0;
//    macierzprzeksztalcen[3][2] = 0;
//    macierzprzeksztalcen[3][3] = 1;

//    for(int i=0; i<4; i++)
//    {

//       this->wspolrzedne3dprzek[i][0] = macierzprzeksztalcen[0][0] * this->wspolrzedne3d[i][0] + macierzprzeksztalcen[0][1] * this->wspolrzedne3d[i][1] +
//               macierzprzeksztalcen[0][2] * this->wspolrzedne3d[i][2] + macierzprzeksztalcen[0][3];

//       this->wspolrzedne3dprzek[i][1] = macierzprzeksztalcen[1][0] * this->wspolrzedne3d[i][0] + macierzprzeksztalcen[1][1] * this->wspolrzedne3d[i][1] +
//               macierzprzeksztalcen[1][2] * this->wspolrzedne3d[i][2] + macierzprzeksztalcen[1][3];

//       this->wspolrzedne3dprzek[i][2] = macierzprzeksztalcen[2][0] * this->wspolrzedne3d[i][0] + macierzprzeksztalcen[2][1] * this->wspolrzedne3d[i][1] +
//               macierzprzeksztalcen[2][2] * this->wspolrzedne3d[i][2] + macierzprzeksztalcen[2][3];
//    }


    double macierzpom[4][4];
    double macierzwynikowa[4][4];
    double kat = 0 * M_PI/180.0;

    macierzprzeksztalcen[0][0] = 1; //0wiersz 0 kol
    macierzprzeksztalcen[0][1] = 0; //0wiersz 1 kol
    macierzprzeksztalcen[0][2] = 0;
    macierzprzeksztalcen[0][3] = 0;

    macierzprzeksztalcen[1][0] = 0;
    macierzprzeksztalcen[1][1] = 1;
    macierzprzeksztalcen[1][2] = 0;
    macierzprzeksztalcen[1][3] = 100;

    macierzprzeksztalcen[2][0] = 0;
    macierzprzeksztalcen[2][1] = 0;
    macierzprzeksztalcen[2][2] = 1;
    macierzprzeksztalcen[2][3] = -pikselePrzesuniecia;

    macierzprzeksztalcen[3][0] = 0;
    macierzprzeksztalcen[3][1] = 0;
    macierzprzeksztalcen[3][2] = 0;
    macierzprzeksztalcen[3][3] = 1;

    macierzpom[0][0] = cos(kat); //0wiersz 0 kol
    macierzpom[0][1] = 0; //0wiersz 1 kol
    macierzpom[0][2] = sin(kat);
    macierzpom[0][3] = 0;

    macierzpom[1][0] = 0;
    macierzpom[1][1] = 1;
    macierzpom[1][2] = 0;
    macierzpom[1][3] = 0;

    macierzpom[2][0] = -sin(kat);
    macierzpom[2][1] = 0;
    macierzpom[2][2] = cos(kat);
    macierzpom[2][3] = 0;

    macierzpom[3][0] = 0;
    macierzpom[3][1] = 0;
    macierzpom[3][2] = 0;
    macierzpom[3][3] = 1;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
             macierzwynikowa[i][j] = 0;
        }
    }


    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                macierzwynikowa[i][j] += (macierzprzeksztalcen[i][k] * macierzpom[k][j]);

            }
        }
    }

    for(int i=0; i<4; i++)
    {

       this->wspolrzedne3dprzek[i][0] = macierzwynikowa[0][0] * this->wspolrzedne3d[i][0] + macierzwynikowa[0][1] * this->wspolrzedne3d[i][1] +
               macierzwynikowa[0][2] * this->wspolrzedne3d[i][2] + macierzwynikowa[0][3];

       this->wspolrzedne3dprzek[i][1] = macierzwynikowa[1][0] * this->wspolrzedne3d[i][0] + macierzwynikowa[1][1] * this->wspolrzedne3d[i][1] +
               macierzwynikowa[1][2] * this->wspolrzedne3d[i][2] + macierzwynikowa[1][3];

       this->wspolrzedne3dprzek[i][2] = macierzwynikowa[2][0] * this->wspolrzedne3d[i][0] + macierzwynikowa[2][1] * this->wspolrzedne3d[i][1] +
               macierzwynikowa[2][2] * this->wspolrzedne3d[i][2] + macierzwynikowa[2][3];
    }

}


void Punkt::rysujPunkt(QImage *obrazDocelowy)
{
    double wyznacznik=0;
    for(int i=0; i<this->wektoryNormalne.size(); i++)
    {
        wyznacznik = (this->trojkaty2d[i][1][0] - this->trojkaty2d[i][0][0]) * (this->trojkaty2d[i][2][1] - this->trojkaty2d[i][0][1]) -
                        (this->trojkaty2d[i][1][1] - this->trojkaty2d[i][0][1]) * (this->trojkaty2d[i][2][0] - this->trojkaty2d[i][0][0]);

        if(wyznacznik>0)
        {
            rysujScianePunktu(i, obrazDocelowy);
        }
    }
}

void Punkt::rysujScianePunktu(int indeksSciany, QImage * obrazDocelowy)
{
    //obliczkolorsciany(indeksSciany);
    double mian = (this->trojkaty2d[indeksSciany][1][0] - this->trojkaty2d[indeksSciany][0][0])*(this->trojkaty2d[indeksSciany][2][1] - this->trojkaty2d[indeksSciany][0][1]) -
            (this->trojkaty2d[indeksSciany][1][1] - this->trojkaty2d[indeksSciany][0][1])*(this->trojkaty2d[indeksSciany][2][0] - this->trojkaty2d[indeksSciany][0][0]);

    double u,v,w;
    unsigned char *wyswietlany;
    wyswietlany = obrazDocelowy ->bits();
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

                    wyswietlany[szer*4*(int)j + 4*(int)i] = 0;
                    wyswietlany[szer*4*(int)j + 4*(int)i + 1] = 255;
                    wyswietlany[szer*4*(int)j + 4*(int)i + 2] = 0;
                }
            }
        }
    }
}

void Punkt::czysc()
{
    this->trojkaty2d.clear();
    this->trojkaty3d.clear();
    this->wektoryNormalne.clear();
}

int Punkt::najmniejszeZ() //zwraca wspolrzedna z najblizej obserwatora
{
    int wynik = 1000000;
    for(int i=0; i<4; i++)
    {
        if(this->wspolrzedne3d[i][2] < wynik)
        {
            wynik = this->wspolrzedne3dprzek[i][2];
        }
    }
    return wynik;
}
