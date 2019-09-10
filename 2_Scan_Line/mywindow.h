#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QColorDialog>
#include <QStack>
#include <QPair>
#include <QtMath>
#include <cmath>
#include <QVector>

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
    QImage *cpy;

    int szer;
    int wys;
    int poczX;
    int poczY;
    int x0, x1, y0, y1;
    int wielokatx0, wielokaty0, wielokatx1, wielokaty1;

    bool okrag = false;
    //bool elipsa = false;
    //bool wielokat = false;
    bool wielokat2 = false;
    bool kolorowanie = false;
    bool pointExists=false;
    int katy=0;
    QColor kolorPobrany = QColor(255, 255, 255);
    QColor kolorZrodla;
    QColor kolorDomyslny = QColor(0, 0, 0); //czarny
    QVector <QVector <int> > points;

    void czysc();
    void zapalpiksel(int x,int y);
    void rysujokrag();
    //void rysujelipse();
   // void rysujwielokat();
    void rysujodcinek(int xp, int yp, int xk, int yk);
    void scanline();
    bool czykrawedz(int x, int y);


private slots:
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    //void on_checkBox_3_stateChanged(int arg1);
    //void on_spinBox_valueChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif
