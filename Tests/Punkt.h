#ifndef PUNKT_H
#define PUNKT_H
#include <QVector>
#include <QImage>


class Punkt
{
public:
    //double wspolrzedne2d[4][4];
    double wspolrzedne3d[4][4] =
    {{-5,0,5,1},
    {5,0,5,1},
    {0,0,-4,1},
    {0,-10,0,1}};
//{{-5,0,5,1},
//{5,0,5,1},
//{0,0,-5,1},
//{0,-5,0,1}};

    QVector <QVector <double> > wspolrzedne3dprzek;
    QVector <QVector <QVector <double> > >trojkaty2d; //wspolrzedne wierzcholkow trojkatow po przeksztalceniu na (x,y)
    QVector <QVector <QVector <double> > >trojkaty3d; //wspolrzedne wierzcholkow trojkatow w postaci (x,y,z)
    QVector <QVector <double> > wektoryNormalne;

    int szer;
    int wys;
    int numerToru;

    Punkt(int z, int szer, int wys, int tor);

    void obliczTrojkaty3d();
    void obliczTrojkaty2d();
    void obliczWektoryNormalne();
    void przesuwaj(int pikselePrzesuniecia, int katObrotu);
    void rysujPunkt(QImage * obrazDocelowy);
    void rysujScianePunktu(int indeksSciany, QImage * obrazDocelowy);
    void czysc();
    int najmniejszeZ();
};

#endif // PUNKT_H
