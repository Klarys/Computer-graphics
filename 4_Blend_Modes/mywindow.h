#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QtMath>
#include <cmath>
#include <QQueue>

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

    QImage *activeLayer;
    //QImage *layer1;
  //  QImage *layer2;
   // QImage *layer3;
   // QImage *layer4;
   // QImage *layer5;
   QVector <QImage*> layers;
   QImage *tmp;

    bool isLayerActive[5] = {0,0,0,0,0};
    double layersOpacity[5] = {1,1,1,1,1};
    int layersMode[5] = {0,0,0,0,0}; //0 - normal ,1 darken, 2-lighten, 3-difference 4-XOR


    int szer;
    int wys;
    int poczX;
    int poczY;
    int x0, x1, y0, y1;

    void zapalpiksel(int x,int y);
    void rysujodcinek(int x1, int y1, int x2, int y2);

    void showactive();
    void fill();

    //modes
    //QColor darkerpiksel(QColor x, QColor y);
    int darkerPiksel(int x, int y);
    int lighterPiksel(int x, int y);
    int difference(int x, int y);
    int XOR(int x, int y);

private slots:
    void paintEvent(QPaintEvent*);

    void on_checkBox1_clicked(bool checked);
    void on_checkBox2_clicked(bool checked);
    void on_checkBox3_clicked(bool checked);
    void on_checkBox4_clicked(bool checked);
    void on_checkBox5_clicked(bool checked);
    void on_horizontalSlider1_sliderMoved(int position);
    void on_horizontalSlider2_sliderMoved(int position);
    void on_horizontalSlider3_sliderMoved(int position);
    void on_horizontalSlider4_sliderMoved(int position);
    void on_horizontalSlider5_sliderMoved(int position);
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(int index);
    void on_comboBox_3_currentIndexChanged(int index);
    void on_comboBox_4_currentIndexChanged(int index);
    void on_comboBox_5_currentIndexChanged(int index);
};

#endif // MYWINDOW_H
