#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <sfera.h>
#include <Przeszkoda.h>
#include <Punkt.h>
#include <QMainWindow>
#include <QInputDialog>
#include <Wynik.h>
#include <Ranking.h>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QImage *obrazzrodlowy;
    QImage *obrazTor;
    QImage *obrazPorazka;
    QImage *obrazWygrana;
    QImage* zero = new QImage(":/tekstury/0.png");
    QImage* jeden = new QImage(":/tekstury/1.png");
    QImage* dwa = new QImage(":/tekstury/2.png");
    QImage* trzy = new QImage(":/tekstury/3.png");
    QImage* cztery = new QImage(":/tekstury/4.png");
    QImage* piec = new QImage(":/tekstury/5.png");
    QImage* szesc = new QImage(":/tekstury/6.png");
    QImage* siedem = new QImage(":/tekstury/7.png");
    QImage* osiem = new QImage(":/tekstury/8.png");
    QImage* dziewiec = new QImage(":/tekstury/9.png");
    QImage* jednostki;
    QImage* dziesiatki;
    int szer;
    int wys;
    int poczX;
    int poczY;
    Sfera * testSfera = new Sfera(25, 9, 18);
    QVector <Przeszkoda*>  Przeszkody;
    QVector <Punkt*>  Punkty;
    int iloscPrzeszkod = 20;
    int zebranePunkty = 0;
    int zycia = 3;
    Ranking ranking;
    QCursor kursorL;
    QCursor kursorP;
    bool wGrze = false;


private slots:



    void zapalPiksel(double x, double y);
    void czarneTlo();
    void wyswietlObraz(QImage * obraz);
    void generujObiekty(); //tworzy przeszkody, gwiazdki itp
    void rysujZycia();
    void rysujLicznikPunktow();


    void paintEvent(QPaintEvent*);

    void TEST();


    void on_pushButton_clicked();
    void on_PozycjaWPrawo_clicked();
    void on_PozycjaWLewo_clicked();
    void on_spinBox_valueChanged(int arg1);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
