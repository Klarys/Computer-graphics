#ifndef RANKING_H
#define RANKING_H
#include <QVector>
#include <Wynik.h>
#include <QImage>

class Ranking
{
public:

    QVector <Wynik> Wyniki;

    void dodajWynik(Wynik wynik);
    void rysujRanking(QImage * obrazDocelowy);
    void sortuj();
    Ranking();
};

#endif // RANKING_H
