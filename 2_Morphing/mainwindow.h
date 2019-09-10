#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QtMath>
#include <cmath>
#include <QQueue>
#include <QFileDialog>
#include <QString>
#include <QColor>
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
    QImage *obrazwczytany;
    QImage *obrazwyswietlany1;
    QImage *obrazwyswietlany2;
    QImage *obrazwyswietlany3;
    QVector <QVector <QVector <int> > >Punktyobr1; //vector przechowujacy wspolrzedne wierzcholkow wszystkich trojkatow 1 obrazu
    QVector <QVector <QVector <int> > >Punktyobr2; //vector przechowujacy wspolrzedne wierzcholkow wszystkich trojkatow 2 obrazu
    int szer;
    int wys;

    QVector <QVector <int> > PunktysiatkiL;
    QVector <QVector <int> > PunktysiatkiP;
    QVector <QVector <int> > AktywnepunktysiatkiL;
    QVector <QVector <int> > AktywnepunktysiatkiP;


    int indeksLewyx = -1;
    int indeksPrawyx = -1;
    int indeksLewyy = -1;
    int indeksPrawyy = -1;

    int frameX;
    int frameY;

    int frame2X;
    int frame2Y;

    int frame3X;
    int frame3Y;

    int iloscPunktow1 = 0;
    int iloscPunktow2 = 0;

    int liczbaKlatek = 120;
    QVector <QImage*> Klatki;

private slots:

    void stanPoczatkowy();
    void generujSiatke();
    void rysujSiatke();
    void morphing(); //generuje klatki
    void wyswietlanimacje(); //wyswietla klatki

    int pobierzR(int x, int y, QImage * obrazzrodlowy);
    int pobierzG(int x, int y, QImage * obrazzrodlowy);
    int pobierzB(int x, int y, QImage * obrazzrodlowy);
    void zapalPiksel(int x, int y, QImage * obrazdocelowy, int r, int g, int b);
    void zapalPiksel(int x, int y, QImage * obrazzrodlowy, QImage * obrazdocelowy);
    void bialeTlo();

    void zapalPiksel(int x, int y, QImage * obrazdocelowy);
    void zapalPiksel(int x, int y, double xt, double yt, QImage * obrazdocelowy);
    void rysujodcinek(int xp, int yp, int xk, int yk, QImage * obrazdocelowy);
    void rysujPunktZielony(int x, int y, QImage * obrazdocelowy);
    void rysujPunktCzerwony(int x, int y, QImage * obrazdocelowy);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

};

#endif // MAINWINDOW_H
