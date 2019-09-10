#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    QImage *obrazwyswietlany;
    QImage *obrazzrodlowy;
    int szer;
    int wys;
    int poczX;
    int poczY;

    bool przes = 0;
    bool skal = 0;

    int przesuniecieX = 0;
    int przesuniecieY = 0;

    double skalowanieX = 1;
    double skalowanieY = 1;

    int katobrotu = 0;

    double pochylenieshX = 0; //domyslna musi byc 0
    double pochylenieshY = 0;

    double tmp[3][3];
    double macierzwynikowa[3][3];
    double macierzprzeksztalcen[3][3]; //przechowuje wartosci po konkretnych przeksztalceniach

private slots:
   void paintEvent(QPaintEvent*);
   void jednostkowa();
   void uzupelnijmprzeksztalcen();
   void przypisztmp();
   void przypiszwynikowa();
   void przesuniecie();
   void skalowanie();
   void obrot();
   void pochylenie();
   void obliczpiksele(); //oblicza wartosci dla nowego obrazka
   void zapalPiksel(double xz, double yz, int xd, int yd);
   void bialeTlo();


   void on_przesuwaniePL_sliderMoved(int position);
   void on_D_sliderMoved(int position);
   void on_SkalowaniePion_sliderMoved(int position);
   void on_SkalowaniePoziom_sliderMoved(int position);
   void on_Obracanie_sliderMoved(int position);
   void on_PochylanieX_sliderMoved(int position);
   void on_PochylanieY_sliderMoved(int position);
};

#endif // MAINWINDOW_H
