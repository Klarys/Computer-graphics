#include <QVector>
#include <QImage>
#ifndef SFERA_H
#define SFERA_H
#

class Sfera
{
private:

public:
    double r; //promien
    int pion; //liczba obszarow w pionie
    int poziom; //liczba obszarow w poziomie
    int pozycja = 1; //0 - po lewej, 1 - środek 2 - po prawej, domyślnie na środku
    QVector <QVector <double> > wspolrzedne2d;
    QVector <QVector <double> > wspolrzedne3d;
    QVector <QVector <double> > wspolrzedne3dprzek;
    QVector <QVector <QVector <double> > >trojkaty2d; //wspolrzedne wierzcholkow trojkatow po przeksztalceniu na (x,y)
    QVector <QVector <QVector <double> > >trojkaty3d; //wspolrzedne wierzcholkow trojkatow w postaci (x,y,z)
    QVector <QVector <double> > wektoryNormalne;
    QVector <QVector <double> > wspolrzedneTekstury; //wspolrzedne wierzcholkow przeniesionych na teksture
    QVector <QVector <QVector <double> > >trojkaty2dTekstury; //wspolrzedne wierzcholkow trojkatow w postaci (x,y,z)

    double macierzPrzesuniecia[4][4];

    QImage* tekstura;


    Sfera();
    Sfera(double r, int pion, int poziom);
    void obliczWspolrzedne2d();
    void obliczTrojkaty3d();
    void obliczTrojkaty2d();
    void obliczWektoryNormalne();
    void obracaj(int katObrotu);
    void rysujSfere(QImage * obrazDocelowy, int szer);
    void rysujScianeSfery(int indeksSciany, QImage * obrazDocelowy,int szer);
    void pozycjaWPrawo();
    void pozycjaWLewo();
    void czysc();
    int najwiekszeZ();
    void obliczTrojkaty2dTekstury();
    double wspolczynnikSwiatlaBezVectorow(int indeksSciany);
    double wspolczynnikSwiatla(int indeksSciany);

};

#endif // SFERA_H
