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
            wspolrzedneTekstur.push_back((int)((double)j/(double)poziom * tekstura->width()));
            wspolrzedneTekstur.push_back((int)((double)i/(double)pion * tekstura->height()));

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
            if(this-> pozycja == 0)
            {
                punkt2d.push_back((this->trojkaty3d[i][j][0] * d)/(this->trojkaty3d[i][j][2]+d) +200.0);  //x
                punkt2d.push_back((this->trojkaty3d[i][j][1] * d)/(this->trojkaty3d[i][j][2]+d) +450.0);  //y
            }
            else if(this->pozycja == 2)
            {
                punkt2d.push_back((this->trojkaty3d[i][j][0] * d)/(this->trojkaty3d[i][j][2]+d) +400.0);  //x
                punkt2d.push_back((this->trojkaty3d[i][j][1] * d)/(this->trojkaty3d[i][j][2]+d) +450.0);  //y
            }
            else
            {
                punkt2d.push_back((this->trojkaty3d[i][j][0] * d)/(this->trojkaty3d[i][j][2]+d) +300.0);  //x
                punkt2d.push_back((this->trojkaty3d[i][j][1] * d)/(this->trojkaty3d[i][j][2]+d) +450.0);  //y
            }


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
                macierzprzeksztalcen[0][3] = 0;
//                if(this-> pozycja == 0)
//                {
//                    macierzprzeksztalcen[0][3] = -100;
//                }
//                else if(this->pozycja == 2)
//                {
//                    macierzprzeksztalcen[0][3] = 100;
//                }

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
    double wyznacznik=0;
    for(int i=0; i<this->wektoryNormalne.size(); i++)
    {
        wyznacznik = (this->trojkaty2d[i][1][0] - this->trojkaty2d[i][0][0]) * (this->trojkaty2d[i][2][1] - this->trojkaty2d[i][0][1]) -
                        (this->trojkaty2d[i][1][1] - this->trojkaty2d[i][0][1]) * (this->trojkaty2d[i][2][0] - this->trojkaty2d[i][0][0]);

        if(wyznacznik>=0)
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
                if(v>=-0.1 && v<=1.1 && u>=-0.1 && u<=1.1 && w>=-0.1 && w<=1.1) //jest wewnatrz
                {
                    int xt = u * this->trojkaty2dTekstury[indeksSciany][0][0] + v * this->trojkaty2dTekstury[indeksSciany][1][0] + w * this->trojkaty2dTekstury[indeksSciany][2][0];
                    int yt = u * this->trojkaty2dTekstury[indeksSciany][0][1] + v * this->trojkaty2dTekstury[indeksSciany][1][1] + w * this->trojkaty2dTekstury[indeksSciany][2][1];

                    if(xt == 803) xt--;
                    if(yt == 402) yt--;

                    wyswietlany[szer*4*(int)j + 4*(int)i] =  zrodlo[tekstura->width()*4*yt + 4*xt] * wspolczynnikSwiatlaBezVectorow(indeksSciany);
                    wyswietlany[szer*4*(int)j + 4*(int)i + 1] = zrodlo[tekstura->width()*4*yt + 4*xt + 1] * wspolczynnikSwiatlaBezVectorow(indeksSciany);
                    wyswietlany[szer*4*(int)j + 4*(int)i + 2] = zrodlo[tekstura->width()*4*yt + 4*xt + 2] * wspolczynnikSwiatlaBezVectorow(indeksSciany);
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

double Sfera::wspolczynnikSwiatla(int indeksSciany)
{
    QVector <double> wektorNormalnySciany;
    QVector <double> a;
    QVector <double> b;

    for(int j=0; j<3; j++)
    {
        a.push_back(trojkaty3d[indeksSciany][1][j] - trojkaty3d[indeksSciany][0][j]);
        b.push_back(trojkaty3d[indeksSciany][2][j] - trojkaty3d[indeksSciany][0][j]);
    }
    //axb
    wektorNormalnySciany.push_back(a[1] * b[2] - a[2] * b[1]);
    wektorNormalnySciany.push_back(a[2] * b[0] - a[0] * b[2]);
    wektorNormalnySciany.push_back(a[0] * b[1] - a[1] * b[0]);

    //normalizacja
    double dlugosc = sqrt(wektorNormalnySciany[0] * wektorNormalnySciany[0]  + wektorNormalnySciany[1] * wektorNormalnySciany[1]
                      + wektorNormalnySciany[2] * wektorNormalnySciany[2]);

    for(int i=0; i<wektorNormalnySciany.size(); i++)
    {
        wektorNormalnySciany[i] /= dlugosc;
    }

    //zrodlo swiatla
    QVector <double> swiatlo;

    if(this->pozycja == 1) //srodek
    {
        swiatlo.push_back((trojkaty3d[indeksSciany][0][0] + trojkaty3d[indeksSciany][1][0] + trojkaty3d[indeksSciany][2][0])/3.0);
        swiatlo.push_back((trojkaty3d[indeksSciany][0][1] + trojkaty3d[indeksSciany][1][1] + trojkaty3d[indeksSciany][2][1])/3.0 + 40);
        swiatlo.push_back((trojkaty3d[indeksSciany][0][2] + trojkaty3d[indeksSciany][1][2] + trojkaty3d[indeksSciany][2][2])/3.0 - 40);
    }
    else if(this->pozycja == 0)
    {
        swiatlo.push_back((trojkaty3d[indeksSciany][0][0] + trojkaty3d[indeksSciany][1][0] + trojkaty3d[indeksSciany][2][0])/3.0 - 40);
        swiatlo.push_back((trojkaty3d[indeksSciany][0][1] + trojkaty3d[indeksSciany][1][1] + trojkaty3d[indeksSciany][2][1])/3.0 + 40);
        swiatlo.push_back((trojkaty3d[indeksSciany][0][2] + trojkaty3d[indeksSciany][1][2] + trojkaty3d[indeksSciany][2][2])/3.0 - 40);
    }
    else if(this->pozycja == 2)
    {
        swiatlo.push_back((trojkaty3d[indeksSciany][0][0] + trojkaty3d[indeksSciany][1][0] + trojkaty3d[indeksSciany][2][0])/3.0 + 40);
        swiatlo.push_back((trojkaty3d[indeksSciany][0][1] + trojkaty3d[indeksSciany][1][1] + trojkaty3d[indeksSciany][2][1])/3.0 + 40);
        swiatlo.push_back((trojkaty3d[indeksSciany][0][2] + trojkaty3d[indeksSciany][1][2] + trojkaty3d[indeksSciany][2][2])/3.0 - 40);
    }

    double dlugosc2 = sqrt(swiatlo[0] * swiatlo[0]  + swiatlo[1] * swiatlo[1]
                      + swiatlo[2] * swiatlo[2]);

    for(int i=0; i<swiatlo.size(); i++)
    {
        swiatlo[i] /= dlugosc2;
    }

    double wynik = wektorNormalnySciany[0] * swiatlo[0] + wektorNormalnySciany[1] * swiatlo[1] + wektorNormalnySciany[2]*swiatlo[2];

    if(wynik >=0 )
    {
        wynik = 0;
    }
    else
    {
        wynik*= (-1);
    }

    if(wynik < 0.2)
    {
        wynik = 0.2;
    }

    return wynik;

}

double Sfera::wspolczynnikSwiatlaBezVectorow(int indeksSciany)
{

    double Ax = this->trojkaty3d[indeksSciany][0][0];
    double Ay = this->trojkaty3d[indeksSciany][0][1];
    double Az = this->trojkaty3d[indeksSciany][0][2];

    double Bx = this->trojkaty3d[indeksSciany][1][0];
    double By = this->trojkaty3d[indeksSciany][1][1];
    double Bz = this->trojkaty3d[indeksSciany][1][2];

    double Cx = this->trojkaty3d[indeksSciany][2][0];
    double Cy = this->trojkaty3d[indeksSciany][2][1];
    double Cz = this->trojkaty3d[indeksSciany][2][2];

    //PxR
    double  Px = Bx-Ax;
    double  Py = By-Ay;
    double  Pz = Bz-Az;

    double  Rx = Cx-Ax;
    double  Ry = Cy-Ay;
    double  Rz = Cz-Az;

    double  wektorNormalnyx = Py*Rz-Pz*Ry;
    double  wektorNormalnyy = Pz*Rx-Px*Rz;
    double  wektorNormalnyz = Px*Ry-Py*Rx;

    double dlugosc = sqrt(wektorNormalnyx*wektorNormalnyx+wektorNormalnyy*wektorNormalnyy+wektorNormalnyz*wektorNormalnyz);

    wektorNormalnyx/=dlugosc;
    wektorNormalnyz/=dlugosc;
    wektorNormalnyy/=dlugosc;

    double swiatlox, swiatloy, swiatloz;

    if(pozycja == 1)
    {
       swiatlox = (Ax+Bx+Cx)/3;
       swiatloy = (Ay+By+Cy)/3;
       swiatloz = (Az+Bz+Cz)/3-150;
    }
    else if(pozycja == 0)
    {
        swiatlox = (Ax+Bx+Cx)/3-40;
        swiatloy = (Ay+By+Cy)/3;
        swiatloz = (Az+Bz+Cz)/3-150;
    }
    else if(pozycja == 2)
    {
       swiatlox = (Ax+Bx+Cx)/3+40;
       swiatloy = (Ay+By+Cy)/3;
       swiatloz = (Az+Bz+Cz)/3-150;
    }


    double dlugosc2 = sqrt(swiatlox*swiatlox+swiatloy*swiatloy+swiatloz*swiatloz);

    swiatlox/=dlugosc2;
    swiatloy/=dlugosc2;
    swiatloz/=dlugosc2;

    double wynik = wektorNormalnyx*swiatlox + wektorNormalnyy*swiatloy + wektorNormalnyz*swiatloz;

    if(wynik >= 0)
    {
       wynik = 0;
    }
    else
    {
       wynik*=(-1);
    }

    wynik = std::max(wynik, 0.2);

    return wynik;
}
