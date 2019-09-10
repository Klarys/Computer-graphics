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
    QVector <QVector <int> > Punktyobr1;
    QVector <QVector <int> > Punktyobr2;
    int szer;
    int wys;

    int indeksLewy = -1;
    int indeksPrawy = -1;

    int frameX;
    int frameY;

    int frame2X;
    int frame2Y;

    int iloscPunktow1 = 0;
    int iloscPunktow2 = 0;

private slots:

    void stanPoczatkowy(bool czyszczeniePunktow);
    void teksturowanie();
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
};

#endif // MAINWINDOW_H
