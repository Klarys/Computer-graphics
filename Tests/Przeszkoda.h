#include <QVector>
#include <QImage>
#ifndef PRZESZKODA_H
#define PRZESZKODA_H


class Przeszkoda
{
public:
   // double wspolrzedne2d[8][4];
    double wspolrzedne3d[8][4] =
    {{20,-20,10,1},
    {20,-20,-10,1},
    {20,20,10,1},
    {20,20,-10,1},
    {-20,-20,10,1},
    {-20,-20,-10,1},
    {-20,20,10,1},
    {-20,20,-10,1}};
    QVector <QVector <double> > wspolrzedne3dprzek;
    QVector <QVector <QVector <double> > >trojkaty2d; //wspolrzedne wierzcholkow trojkatow po przeksztalceniu na (x,y)
    QVector <QVector <QVector <double> > >trojkaty3d; //wspolrzedne wierzcholkow trojkatow w postaci (x,y,z)
    QVector <QVector <double> > wektoryNormalne;

    int szer;
    int wys;
    int numerToru;

    Przeszkoda(int z, int szer, int wys, int tor);

    void obliczTrojkaty3d();
    void obliczTrojkaty2d();
    void obliczWektoryNormalne();
    void przesuwaj(int pikselePrzesuniecia);
    void rysujPrzeszkode(QImage * obrazDocelowy);
    void rysujScianePrzeszkody(int indeksSciany, QImage * obrazDocelowy);
    void czysc();
    int najmniejszeZ();
};


#endif // PRZESZKODA_H
