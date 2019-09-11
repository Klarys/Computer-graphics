#ifndef WYNIK_H
#define WYNIK_H
#include <QString>

class Wynik
{
public:
    QString Gracz;
    int zebranePunkty;
    Wynik(QString gracz, int zebranepunkty);
    Wynik();
};

#endif // WYNIK_H
