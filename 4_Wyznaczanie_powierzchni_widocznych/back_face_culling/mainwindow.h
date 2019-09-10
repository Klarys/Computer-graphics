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

    int szescianpoczatkowy[8][4]=
    {
        {20,20,20,1},
        {20,20,-20,1},
        {20,-20,20,1},
        {20,-20,-20,1},
        {-20,20,20,1},
        {-20,20,-20,1},
        {-20,-20,20,1},
        {-20,-20,-20,1},
    };

    int szescianwynikowy[8][4] = //{{0,0,0,1}, {0,0,0,1}, {0,0,0,1}, {0,0,0,1}, {0,0,0,1}, {0,0,0,1}, {0,0,0,1}, {0,0,0,1}};
    {
        {20,20,20,1},
        {20,20,-20,1},
        {20,-20,20,1},
        {20,-20,-20,1},
        {-20,20,20,1},
        {-20,20,-20,1},
        {-20,-20,20,1},
        {-20,-20,-20,1},
    };

    int wspolrzedne2d[8][2];

    std::pair<int,int> trojkatyscian2d[12][3]; //przechowuje wspolrzedne 2d wierzcholkow trojkatow z ktorych skladaja sie sciany

    bool przes = 0;
    bool skal = 0;

    int przesuniecieX = 0;
    int przesuniecieY = 0;
    int przesuniecieZ = 0;

    double skalowanieX = 1;
    double skalowanieY = 1;
    double skalowanieZ = 1;

    int katobrotuOX = 0;
    int katobrotuOY = 0;
    int katobrotuOZ = 0;

    double pochylenieshX = 0; //domyslna musi byc 0 - wynika ze wzoru
    double pochylenieshY = 0;
    double pochylenieshZ = 0;

    double tmp[4][4];
    double macierzwynikowa[4][4];
    double macierzprzeksztalcen[4][4]; //przechowuje wartosci po konkretnych przeksztalceniach

    bool sciany = false;

private slots:

    void oblicztrojkaty();
    void widocznoscscian(); //sprawdza ktore sciany sa widoczne i dla widocznych uzywa rysujsciane()
    void rysujsciane(int indekssciany); //rysuje pojedyncza sciane

    void obliczwspolrzedne2d();
    void rysujszescian();
    void zapalPiksel(int x, int y);
    void rysujodcinek(int xp, int yp, int xk, int yk);
    void obliczwspolrzedne3d();

   void paintEvent(QPaintEvent*);
   void jednostkowa();
   void uzupelnijmprzeksztalcen();
   void przypisztmp();
   void przypiszwynikowa();
   void przesuniecie();
   void skalowanie();
   void obrotOX();
   void obrotOY();
   void obrotOZ();
   void pochylenieOX();
   void pochylenieOY();
   void pochylenieOZ();
   void bialeTlo();


   void on_przesuwaniePL_sliderMoved(int position);
   void on_przesuwanieGD_sliderMoved(int position);
   void on_przesuwaniePT_sliderMoved(int position);

   void on_SkalowanieY_sliderMoved(int position);
   void on_SkalowanieX_sliderMoved(int position);
   void on_SkalowanieZ_sliderMoved(int position);

   void on_ObracanieX_sliderMoved(int position);
   void on_ObracanieY_sliderMoved(int position);
   void on_ObracanieZ_sliderMoved(int position);

   void on_PochylanieX_sliderMoved(int position);
   void on_PochylanieY_sliderMoved(int position);
   void on_PochylanieZ_sliderMoved(int position);
   void on_checkBox_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
