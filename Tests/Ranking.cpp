#include "Ranking.h"
#include <QPainter>

Ranking::Ranking()
{

}

void Ranking::dodajWynik(Wynik wynik)
{
    bool znaleziono = false;
    if(this->Wyniki.empty())
    {
        this->Wyniki.push_back(wynik);
    }
    else
    {
        int indeks=0;
        for(int i=0; i<this->Wyniki.size(); i++)
        {
            if(this->Wyniki[i].zebranePunkty < wynik.zebranePunkty)
            {
                indeks = i;
                znaleziono = true;
                break;
            }
        }
        if(znaleziono)
        {
            this->Wyniki.insert(indeks, wynik);
        }
        else
        {
           this->Wyniki.push_back(wynik);
        }
    }
    if(this->Wyniki.size()>10)
    {
        this->Wyniki.pop_back();
    }
}
void Ranking::rysujRanking(QImage * obrazDocelowy)
{
    QPainter p(obrazDocelowy);
    p.setPen(Qt::white);
    p.setFont(QFont("Open Sans", 30));
    p.drawText(150,150,150,150,0, "Ranking: ");

    int x = 190;
    int y = 190;

    p.setFont(QFont("Open Sans", 20));
    for(int i=0; i<this->Wyniki.size(); i++)
    {
        const QString wiersz = QString::number(i+1) + ". " + this->Wyniki[i].Gracz + " : " + QString::number(this->Wyniki[i].zebranePunkty);
        p.drawText(x, y, 200, 30, 0, wiersz);

        y += 30;
    }
}

