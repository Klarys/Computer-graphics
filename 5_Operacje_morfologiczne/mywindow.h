#ifndef MYWINDOW_H
#define MYWINDOW_H

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
    class MyWindow;
}


class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();

private:
    Ui::MyWindow *ui;

    QImage *img;
    QImage *zrodlo;
    QImage *obrazwczytany;
    QImage *wynik;
   // QQueue <QImage*> layers;


    int szer;
    int wys;
    int poczX;
    int poczY;
    int x0, x1, y0, y1;
    int bok=3;

    void odcienieszarosci();
    void czernibiel();
    void zapalpiksel(int x,int y);
    void zgaspiksel(int x, int y);

    void dylatacja();
    void erozja();

    QColor kolorpiksela(int x, int y);

private slots:
    //void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

    void on_pushButton_5_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // MYWINDOW_H
