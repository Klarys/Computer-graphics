#include <QImage>
#ifndef TOR_H
#define TOR_H


class Tor
{

private:
    QImage *tekstura;
public:
    int szer;
    int wys;
    QVector <QVector <QVector <double> > >trojkaty2d; //wspolrzedne wierzcholkow trojkatow po przeksztalceniu na (x,y)
    QVector <QVector <QVector <double> > >trojkaty3d; //wspolrzedne wierzcholkow trojkatow w postaci (x,y,z)
    QVector <QVector <double> > wektoryNormalne;

    Tor(int szer, int wys);
    void obliczTrojkaty3d();
    void obliczTrojkaty2d();
    void obliczWektoryNormalne();
    void rysujTor(QImage * obrazDocelowy);
    void rysujFragmentToru(int indeksSciany, QImage * obrazDocelowy);
};

#endif // TOR_H
