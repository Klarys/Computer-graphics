#include "Sfera.h"
#include <cmath>
#include <QTime>
#include <QVector>


Sfera::Sfera()
{

}

Sfera::Sfera(double r, int pion, int poziom)
{
    this->tekstura = new QImage(":/tekstury/SferaTekstura.png");

    this->r = r;
    this->pion = pion;
    this->poziom = poziom;

    double pionKrok = (double)M_PI/pion;
    double poziomKrok = (double)(M_PI*2.0)/poziom;

    double pionKat;
    double poziomKat;

    double rcos;
    double rsin;

    for(int i=0; i<=pion; i++)
    {
        pionKat = M_PI/2.0 - i*pionKrok;
        rcos = r * cos(pionKat);
        rsin = r * sin(pionKat);

        for (int j=0; j<= poziom; j++)
        {
            QVector <double> wspolrzednePunktu;

            poziomKat = j*poziomKrok;

            wspolrzednePunktu.push_back(rcos * cos(poziomKat));
            wspolrzednePunktu.push_back(rcos * sin(poziomKat));
            wspolrzednePunktu.push_back(rsin);

            this->wspolrzedne3d.push_back(wspolrzednePunktu);

            QVector <double> wektorNormalny;

            wektorNormalny.push_back(wspolrzednePunktu[0] * 1.0/r);
            wektorNormalny.push_back(wspolrzednePunktu[1] * 1.0/r);
            wektorNormalny.push_back(wspolrzednePunktu[2] * 1.0/r);

            this->wektoryNormalne.push_back(wektorNormalny);

            QVector <double> wspolrzedneTekstur;
            wspolrzedneTekstur.push_back((double)j/(double)poziom * tekstura->width());
            wspolrzedneTekstur.push_back((double)i/(double)pion * tekstura->height());

            this->wspolrzedneTekstury.push_back(wspolrzedneTekstur);
        }
    }
    this->wspolrzedne3dprzek = this->wspolrzedne3d;


}

void Sfera::obliczWspolrzedne2d()
{
    int d = 100;
    for(int i=0; i<this->wspolrzedne3d.size(); i++)
    {
        QVector <double> wspolrzedne2d;
        wspolrzedne2d.push_back((this->wspolrzedne3dprzek[i][0] * d)/(this->wspolrzedne3dprzek[i][2]+d) +300);  //x
        wspolrzedne2d.push_back((this->wspolrzedne3dprzek[i][1] * d)/(this->wspolrzedne3dprzek[i][2]+d) +300);  //y
        this->wspolrzedne2d.push_back(wspolrzedne2d);
    }
}

void Sfera::obliczTrojkaty3d()
{
    int punkt1, punkt2;
    QVector <double> wierzcholek;
    QVector <QVector <double> > trojkat;
    for(int i = 0; i < this->pion; i++)
    {
        punkt1 = i * (this->poziom + 1);
        punkt2 = punkt1 + this->poziom + 1;

        for(int j = 0; j < this->poziom; j++)
        {
            if(i != 0)
            {
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt1][0]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt1][1]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt1][2]);
                trojkat.push_back(wierzcholek);
                wierzcholek.clear();
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt2][0]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt2][1]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt2][2]);
                trojkat.push_back(wierzcholek);
                wierzcholek.clear();
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt1+1][0]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt1+1][1]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt1+1][2]);
                trojkat.push_back(wierzcholek);
                wierzcholek.clear();
                this->trojkaty3d.push_back(trojkat);
                trojkat.clear();

            }
            // k1+1 => k2 => k2+1
            if(i != (this->pion-1))
            {
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt1+1][0]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt1+1][1]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt1+1][2]);
                trojkat.push_back(wierzcholek);
                wierzcholek.clear();
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt2][0]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt2][1]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt2][2]);
                trojkat.push_back(wierzcholek);
                wierzcholek.clear();
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt2+1][0]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt2+1][1]);
                wierzcholek.push_back(this->wspolrzedne3dprzek[punkt2+1][2]);
                trojkat.push_back(wierzcholek);
                wierzcholek.clear();
                this->trojkaty3d.push_back(trojkat);
                trojkat.clear();
            }
            punkt1++;
            punkt2++;
        }
    }
}

void Sfera::obliczTrojkaty2dTekstury()
{
    {
        int punkt1, punkt2;
        QVector <double> wierzcholek;
        QVector <QVector <double> > trojkat;
        for(int i = 0; i < this->pion; i++)
        {
            punkt1 = i * (this->poziom + 1);
            punkt2 = punkt1 + this->poziom + 1;

            for(int j = 0; j < this->poziom; j++)
            {
                if(i != 0)
                {
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt1][0]);
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt1][1]);
                    trojkat.push_back(wierzcholek);
                    wierzcholek.clear();
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt2][0]);
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt2][1]);
                    trojkat.push_back(wierzcholek);
                    wierzcholek.clear();
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt1+1][0]);
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt1+1][1]);
                    trojkat.push_back(wierzcholek);
                    wierzcholek.clear();
                    this->trojkaty2dTekstury.push_back(trojkat);
                    trojkat.clear();

                }
                // k1+1 => k2 => k2+1
                if(i != (this->pion-1))
                {
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt1+1][0]);
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt1+1][1]);
                    trojkat.push_back(wierzcholek);
                    wierzcholek.clear();
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt2][0]);
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt2][1]);
                    trojkat.push_back(wierzcholek);
                    wierzcholek.clear();
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt2+1][0]);
                    wierzcholek.push_back(this->wspolrzedneTekstury[punkt2+1][1]);
                    trojkat.push_back(wierzcholek);
                    wierzcholek.clear();
                    this->trojkaty2dTekstury.push_back(trojkat);
                    trojkat.clear();
                }
                punkt1++;
                punkt2++;
            }
        }
    }
}

void Sfera::obliczTrojkaty2d()
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

void Sfera::obliczWektoryNormalne()
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


void Sfera::obracaj(int katObrotu)
{
    double macierzprzeksztalcen[4][4];


    double kat = (double)katObrotu * M_PI / 180.0;

    if(this->pozycja==1)
    {
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
        macierzprzeksztalcen[3][3] = 1.0;

        for(int i=0; i<this->wspolrzedne3d.size(); i++)
        {

           this->wspolrzedne3dprzek[i][0] = macierzprzeksztalcen[0][0] * this->wspolrzedne3d[i][0] + macierzprzeksztalcen[0][1] * this->wspolrzedne3d[i][1] +
                   macierzprzeksztalcen[0][2] * this->wspolrzedne3d[i][2] + macierzprzeksztalcen[0][3];

           this->wspolrzedne3dprzek[i][1] = macierzprzeksztalcen[1][0] * this->wspolrzedne3d[i][0] + macierzprzeksztalcen[1][1] * this->wspolrzedne3d[i][1] +
                   macierzprzeksztalcen[1][2] * this->wspolrzedne3d[i][2] + macierzprzeksztalcen[1][3];

           this->wspolrzedne3dprzek[i][2] = macierzprzeksztalcen[2][0] * this->wspolrzedne3d[i][0] + macierzprzeksztalcen[2][1] * this->wspolrzedne3d[i][1] +
                   macierzprzeksztalcen[2][2] * this->wspolrzedne3d[i][2] + macierzprzeksztalcen[2][3];
        }
    }
    else
    {
        double macierzpom[4][4];
        double macierzwynikowa[4][4];

//        macierzprzeksztalcen[0][0] = 1;
//        macierzprzeksztalcen[0][1] = 0;
//        macierzprzeksztalcen[0][2] = 0;
//        macierzprzeksztalcen[0][3] = 0;

//        macierzprzeksztalcen[1][0] = 0;
//        macierzprzeksztalcen[1][1] = cos(kat);
//        macierzprzeksztalcen[1][2] = -sin(kat);
//        macierzprzeksztalcen[1][3] = 0;

//        macierzprzeksztalcen[2][0] = 0;
//        macierzprzeksztalcen[2][1] = sin(kat);
//        macierzprzeksztalcen[2][2] = cos(kat);
//        macierzprzeksztalcen[2][3] = 0;

//        macierzprzeksztalcen[3][0] = 0;
//        macierzprzeksztalcen[3][1] = 0;
//        macierzprzeksztalcen[3][2] = 0;
//        macierzprzeksztalcen[3][3] = 1.0;

//        macierzpom[0][0] = 1;
//        macierzpom[0][1] = 0;
//        macierzpom[0][2] = 0;
//        if(this-> pozycja == 0)
//        {
//            macierzpom[0][3] = -100;
//        }
//        else if(this->pozycja == 2)
//        {
//            macierzpom[0][3] = 100;
//        }



//        macierzpom[1][0] = 0;
//        macierzpom[1][1] = 1;
//        macierzpom[1][2] = 0;
//        macierzpom[1][3] = 0;

//        macierzpom[2][0] = 0;
//        macierzpom[2][1] = 0;
//        macierzpom[2][2] = 1;
//        macierzpom[2][3] = 0;

//        macierzpom[3][0] = 0;
//        macierzpom[3][1] = 0;
//        macierzpom[3][2] = 0;
//        macierzpom[3][3] = 1;

                macierzprzeksztalcen[0][0] = 1;
                macierzprzeksztalcen[0][1] = 0;
                macierzprzeksztalcen[0][2] = 0;
                if(this-> pozycja == 0)
                {
                    macierzprzeksztalcen[0][3] = -100;
                }
                else if(this->pozycja == 2)
                {
                    macierzprzeksztalcen[0][3] = 100;
                }

                macierzprzeksztalcen[1][0] = 0;
                macierzprzeksztalcen[1][1] = 1;
                macierzprzeksztalcen[1][2] = 0;
                macierzprzeksztalcen[1][3] = 0;

                macierzprzeksztalcen[2][0] = 0;
                macierzprzeksztalcen[2][1] = 0;
                macierzprzeksztalcen[2][2] = 1;
                macierzprzeksztalcen[2][3] = 0;

                macierzprzeksztalcen[3][0] = 0;
                macierzprzeksztalcen[3][1] = 0;
                macierzprzeksztalcen[3][2] = 0;
                macierzprzeksztalcen[3][3] = 1.0;

                macierzpom[0][0] = 1;
                macierzpom[0][1] = 0;
                macierzpom[0][2] = 0;
                macierzpom[0][3] = 0;

                macierzpom[1][0] = 0;
                macierzpom[1][1] = cos(kat);
                macierzpom[1][2] = -sin(kat);
                macierzpom[1][3] = 0;

                macierzpom[2][0] = 0;
                macierzpom[2][1] = sin(kat);
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

        for(int i=0; i<this->wspolrzedne3d.size(); i++)
        {

           this->wspolrzedne3dprzek[i][0] = macierzwynikowa[0][0] * this->wspolrzedne3d[i][0] + macierzwynikowa[0][1] * this->wspolrzedne3d[i][1] +
                   macierzwynikowa[0][2] * this->wspolrzedne3d[i][2] + macierzwynikowa[0][3];

           this->wspolrzedne3dprzek[i][1] = macierzwynikowa[1][0] * this->wspolrzedne3d[i][0] + macierzwynikowa[1][1] * this->wspolrzedne3d[i][1] +
                   macierzwynikowa[1][2] * this->wspolrzedne3d[i][2] + macierzwynikowa[1][3];

           this->wspolrzedne3dprzek[i][2] = macierzwynikowa[2][0] * this->wspolrzedne3d[i][0] + macierzwynikowa[2][1] * this->wspolrzedne3d[i][1] +
                   macierzwynikowa[2][2] * this->wspolrzedne3d[i][2] + macierzwynikowa[2][3];
        }

    }


}

void Sfera::rysujSfere(QImage * obrazDocelowy,int szer)
{
    int wyznacznik=0;
    for(int i=0; i<this->wektoryNormalne.size(); i++)
    {
        wyznacznik = (this->trojkaty2d[i][1][0] - this->trojkaty2d[i][0][0]) * (this->trojkaty2d[i][2][1] - this->trojkaty2d[i][0][1]) -
                        (this->trojkaty2d[i][1][1] - this->trojkaty2d[i][0][1]) * (this->trojkaty2d[i][2][0] - this->trojkaty2d[i][0][0]);

        if(wyznacznik>0)
        {
            rysujScianeSfery(i, obrazDocelowy, szer);
        }
    }
}

void Sfera::rysujScianeSfery(int indeksSciany, QImage * obrazDocelowy,int szer)
{
    //obliczkolorsciany(indeksSciany);
    double mian = (this->trojkaty2d[indeksSciany][1][0] - this->trojkaty2d[indeksSciany][0][0])*(this->trojkaty2d[indeksSciany][2][1] - this->trojkaty2d[indeksSciany][0][1]) -
            (this->trojkaty2d[indeksSciany][1][1] - this->trojkaty2d[indeksSciany][0][1])*(this->trojkaty2d[indeksSciany][2][0] - this->trojkaty2d[indeksSciany][0][0]);

    double u,v,w;
    unsigned char *wyswietlany;
    wyswietlany = obrazDocelowy ->bits();

    unsigned char *zrodlo;
    zrodlo = tekstura ->bits();
    if(mian != 0)
    {
        double minx = std::min(this->trojkaty2d[indeksSciany][0][0], std::min(this->trojkaty2d[indeksSciany][1][0],this->trojkaty2d[indeksSciany][2][0]));
        double miny = std::min(this->trojkaty2d[indeksSciany][0][1], std::min(this->trojkaty2d[indeksSciany][1][1],this->trojkaty2d[indeksSciany][2][1]));

        double maxx = std::max(this->trojkaty2d[indeksSciany][0][0], std::max(this->trojkaty2d[indeksSciany][1][0],this->trojkaty2d[indeksSciany][2][0]));
        double maxy = std::max(this->trojkaty2d[indeksSciany][0][1], std::max(this->trojkaty2d[indeksSciany][1][1],this->trojkaty2d[indeksSciany][2][1]));
        for(double i=minx; i<=maxx; i++)
        {
            for(double j=miny; j<=maxy; j++)
            {
                v = ((i-this->trojkaty2d[indeksSciany][0][0])*(this->trojkaty2d[indeksSciany][2][1]-this->trojkaty2d[indeksSciany][0][1])
                        -(j-this->trojkaty2d[indeksSciany][0][1])*(this->trojkaty2d[indeksSciany][2][0]-this->trojkaty2d[indeksSciany][0][0]))/mian;

                w = ((this->trojkaty2d[indeksSciany][1][0] - this->trojkaty2d[indeksSciany][0][0])*(j-this->trojkaty2d[indeksSciany][0][1])
                        -(this->trojkaty2d[indeksSciany][1][1] - this->trojkaty2d[indeksSciany][0][1])*(i-this->trojkaty2d[indeksSciany][0][0]))/mian;

                u = 1.0-v-w;

                //if(v>0 && v<1 && u>0 && u<1 && w>0 && w<1)
                if(v>=0 && v<=1 && u>=0 && u<=1 && w>=0 && w<=1) //jest wewnatrz
                {
                        if(indeksSciany>=0 && indeksSciany<190)
                        {
                            int xt = u *this->trojkaty2dTekstury[indeksSciany][0][0] + v *this->trojkaty2dTekstury[indeksSciany][1][0] + w * this->trojkaty2dTekstury[indeksSciany][2][0];
                            int yt = u * this->trojkaty2dTekstury[indeksSciany][0][1] + v * this->trojkaty2dTekstury[indeksSciany][1][1] + w * this->trojkaty2dTekstury[indeksSciany][2][1];

                            wyswietlany[szer*4*(int)j + 4*(int)i] =  zrodlo[tekstura->width()*4*yt + 4*xt];
                            wyswietlany[szer*4*(int)j + 4*(int)i + 1] = zrodlo[tekstura->width()*4*yt + 4*xt + 1];
                            wyswietlany[szer*4*(int)j + 4*(int)i + 2] = zrodlo[tekstura->width()*4*yt + 4*xt + 2];
                        }

//                    wyswietlany[szer*4*(int)j + 4*(int)i] = 211;
//                    wyswietlany[szer*4*(int)j + 4*(int)i + 1] = 0;
//                    wyswietlany[szer*4*(int)j + 4*(int)i + 2] = 148;

//                    wyswietlany[szer*4*((int)j) + 4*((int)i+1)] = 211;
//                    wyswietlany[szer*4*((int)j) + 4*((int)i+1) + 1] = 0;
//                    wyswietlany[szer*4*((int)j) + 4*((int)i+1) + 2] = 148;

//                    wyswietlany[szer*4*((int)j+1) + 4*((int)i)] = 211;
//                    wyswietlany[szer*4*((int)j+1) + 4*((int)i) + 1] = 0;
//                    wyswietlany[szer*4*((int)j+1) + 4*((int)i) + 2] = 148;

//                    wyswietlany[szer*4*((int)j+1) + 4*((int)i+1)] = 211;
//                    wyswietlany[szer*4*((int)j+1) + 4*((int)i+1) + 1] = 0;
//                    wyswietlany[szer*4*((int)j+1) + 4*((int)i+1) + 2] = 148;
                }

            }
        }
    }
}

void Sfera::pozycjaWPrawo()
{
    if(this->pozycja<2)
    {
         this->pozycja += 1;
    }
}

void Sfera::pozycjaWLewo()
{
    if(this->pozycja>0)
    {
         this->pozycja -= 1;
    }
}

void Sfera::czysc()
{
    this->trojkaty2d.clear();
    this->trojkaty3d.clear();
    this->trojkaty2dTekstury.clear();
    this->wektoryNormalne.clear();
}

int Sfera::najwiekszeZ()
{
    int wynik = -10000;
    for (int i=0; i<this->wspolrzedne3dprzek.size(); i++)
    {
        if(wynik< this->wspolrzedne3dprzek[i][2])
        {
            wynik  = this->wspolrzedne3dprzek[i][2];
        }
    }
    return  wynik;
}
