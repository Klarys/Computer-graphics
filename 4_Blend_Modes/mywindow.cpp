#include "mywindow.h"
#include "ui_mywindow.h"

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{

    ui->setupUi(this);

    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();


    activeLayer = new QImage(szer,wys,QImage::Format_RGB32);
    tmp = new QImage(szer,wys,QImage::Format_RGB32);
    fill();
    //layer1 = new QImage(szer,wys,QImage::Format_RGB32);
    //layer2 = new QImage(szer,wys,QImage::Format_RGB32);
    //layer3 = new QImage(szer,wys,QImage::Format_RGB32);
    //layer4 = new QImage(szer,wys,QImage::Format_RGB32);
    //layer5 = new QImage(szer,wys,QImage::Format_RGB32);

      layers.push_back(new QImage(":/new/prefix1/bear.jpg"));
      layers.push_back(new QImage(":/new/prefix1/kitchen.jpg"));
      layers.push_back(new QImage(":/new/prefix1/tree.jpg"));
      layers.push_back(new QImage(":/new/prefix1/scoob.jpg"));
      layers.push_back(new QImage(":/new/prefix1/bee.jpg"));

      ui->horizontalSlider1->setValue(100);
      ui->horizontalSlider2->setValue(100);
      ui->horizontalSlider3->setValue(100);
      ui->horizontalSlider4->setValue(100);
      ui->horizontalSlider5->setValue(100);
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*activeLayer);
}

void MyWindow::showactive()
{
    unsigned char *active;
    active = activeLayer->bits();

    unsigned char *current;
    for(int i=layers.size()-1; i>=0; i--)
    {
        if(isLayerActive[i] && layersMode[i]== 0) //normal
        {
            current = layers[i]->bits();
            for(int j=0; j<wys; j++)
            {
                for(int k=0; k<szer; k++)
                {
                    active[szer*4*j + 4*k] = active[szer*4*j + 4*k]* (1-layersOpacity[i]) + current[szer*4*j + 4*k] * layersOpacity[i];
                    active[szer*4*j + 4*k + 1] = active[szer*4*j + 4*k+1] * (1-layersOpacity[i]) + current[szer*4*j + 4*k+1] * layersOpacity[i];
                    active[szer*4*j + 4*k + 2] = active[szer*4*j + 4*k+2] * (1-layersOpacity[i]) + current[szer*4*j + 4*k+2] * layersOpacity[i];
                }
            }
        }
        else if(isLayerActive[i] && layersMode[i]== 1) //darken
        {
            current = layers[i]->bits();

            unsigned char *tmpbits;
            tmpbits = tmp->bits();
            for(int j=0; j<wys; j++)
            {
                for(int k=0; k<szer; k++)
                {
                    tmpbits[szer*4*j + 4*k] = darkerPiksel(active[szer*4*j + 4*k]  , current[szer*4*j + 4*k]) * layersOpacity[i] + active[szer*4*j + 4*k]* (1-layersOpacity[i]) ;// + current[szer*4*j + 4*k] * (1-layersOpacity[i]);
                    tmpbits[szer*4*j + 4*k + 1] = darkerPiksel(active[szer*4*j + 4*k+1], current[szer*4*j + 4*k+1]) * layersOpacity[i] + active[szer*4*j + 4*k]* (1-layersOpacity[i]);// + current[szer*4*j + 4*k+1] * (1-layersOpacity[i]);
                    tmpbits[szer*4*j + 4*k + 2] = darkerPiksel(active[szer*4*j + 4*k+2], current[szer*4*j + 4*k+2]) * layersOpacity[i] + active[szer*4*j + 4*k]* (1-layersOpacity[i]);// + current[szer*4*j + 4*k+2] * (1-layersOpacity[i]);
                }
            }
            *activeLayer = tmp->copy();
        }
        else if (isLayerActive[i] && layersMode[i]== 2) //lighter
        {
            current = layers[i]->bits();
            for(int j=0; j<wys; j++)
            {
                for(int k=0; k<szer; k++)
                {
                    active[szer*4*j + 4*k] = lighterPiksel(active[szer*4*j + 4*k], current[szer*4*j + 4*k] * layersOpacity[i]);// + current[szer*4*j + 4*k] * (1-layersOpacity[i]);
                    active[szer*4*j + 4*k + 1] = lighterPiksel(active[szer*4*j + 4*k+1], current[szer*4*j + 4*k+1] * layersOpacity[i]);// + current[szer*4*j + 4*k+1] * (1-layersOpacity[i]);
                    active[szer*4*j + 4*k + 2] = lighterPiksel(active[szer*4*j + 4*k+2], current[szer*4*j + 4*k+2] * layersOpacity[i]);// + current[szer*4*j + 4*k+2] * (1-layersOpacity[i]);
                }
            }
        }
        else if (isLayerActive[i] && layersMode[i]== 3) //difference
        {
            current = layers[i]->bits();
            for(int j=0; j<wys; j++)
            {
                for(int k=0; k<szer; k++)
                {
                    active[szer*4*j + 4*k] = difference(active[szer*4*j + 4*k], current[szer*4*j + 4*k] * layersOpacity[i]);// + current[szer*4*j + 4*k] * (1-layersOpacity[i]);
                    active[szer*4*j + 4*k + 1] = difference(active[szer*4*j + 4*k+1], current[szer*4*j + 4*k+1] * layersOpacity[i]);// + current[szer*4*j + 4*k+1] * (1-layersOpacity[i]);
                    active[szer*4*j + 4*k + 2] = difference(active[szer*4*j + 4*k+2], current[szer*4*j + 4*k+2] * layersOpacity[i]);// + current[szer*4*j + 4*k+2] * (1-layersOpacity[i]);
                }
            }
        }
        else if (isLayerActive[i] && layersMode[i]== 4) //negation
        {
            current = layers[i]->bits();
            for(int j=0; j<wys; j++)
            {
                for(int k=0; k<szer; k++)
                {
                    active[szer*4*j + 4*k] = XOR(active[szer*4*j + 4*k], current[szer*4*j + 4*k] * layersOpacity[i]);// + current[szer*4*j + 4*k] * (1-layersOpacity[i]);
                    active[szer*4*j + 4*k + 1] = XOR(active[szer*4*j + 4*k+1], current[szer*4*j + 4*k+1] * layersOpacity[i]);// + current[szer*4*j + 4*k+1] * (1-layersOpacity[i]);
                    active[szer*4*j + 4*k + 2] = XOR(active[szer*4*j + 4*k+2], current[szer*4*j + 4*k+2] * layersOpacity[i]);// + current[szer*4*j + 4*k+2] * (1-layersOpacity[i]);
                }
            }
        }
    }
    update();
}

void MyWindow::zapalpiksel(int x, int y)
{
    unsigned char *ptr;
    ptr = activeLayer->bits();
    ptr[szer*4*y + 4*x]=255;
    ptr[szer*4*y + 4*x + 1] = 255;
    ptr[szer*4*y + 4*x + 2] = 255;
    /*
    ptr[szer*4*(y+1) + 4*(x+1)] = 64;
    ptr[szer*4*(y+1) + 4*(x+1) + 1] = 64;
    ptr[szer*4*(y+1) + 4*(x+1) + 2] = 64;
    ptr[szer*4*(y-1) + 4*(x-1)] = 64;
    ptr[szer*4*(y-1) + 4*(x-1) + 1] = 64;
    ptr[szer*4*(y-1) + 4*(x-1) + 2] = 64;
    */
}

void MyWindow::fill()
{
    unsigned char *tmpbits;
    tmpbits = tmp->bits();
    for(int j=0; j<wys; j++)
    {
        for(int k=0; k<szer; k++)
        {
            tmpbits[szer*4*j + 4*k] = 255;
            tmpbits[szer*4*j + 4*k + 1] = 255;
            tmpbits[szer*4*j + 4*k + 2] = 255;
        }
    }
}


void MyWindow::rysujodcinek(int x0, int y0, int x1, int y1)
{
    double a, b, x, y;
    a = (double)(y1-y0)/(double)(x1-x0);
    b = y1 - (a*x1);

    if(x0 == x1)
    {
        for(int i=y0; i<y1; i++)
        {
            x = (double)(i-b)/a;
            zapalpiksel(x, i);
        }
    }
    else if(y0 == y1)
    {
        for(int i=x0; i<x1; i++)
        {
            zapalpiksel(i, y1);
        }
    }
    else
    {
        for(int i=y0; i<y1; i++)
        {
            x = (double)(i-b)/a;
            zapalpiksel(x, i);
        }
        if(x1<x0)
        {
            int tmp = x1;
            x1 = x0;
            x0 = tmp;

            tmp = y1;
            y1 = y0;
            y0 = tmp;
        }
        for(int i=x0; i<x1; i++)
        {
            y = a*i + b;
            zapalpiksel(i, qRound(y));
        }
    }
}

/*
QColor MyWindow::darkerpiksel(QColor x, QColor y)
{
    int r1,r2,g1,g2,b1,b2;
    x.getRgb(&r1,&g1,&b1);
    y.getRgb(&r2,&g2,&b2);

    if(r2<r1)
    {
        r1=r2;
    }
    if(g2<g1)
    {
        g1=g2;
    }
    if(b2<b1)
    {
        b1=b2;
    }
    return QColor(r1,g1,b1);
}
*/

int MyWindow::darkerPiksel(int x, int y)
{
    if(x<y) return x;
    else return y;
}

int MyWindow::lighterPiksel(int x, int y)
{
    if(x>y) return x;
    else return y;
}

int MyWindow::difference(int x, int y)
{
    return abs(x-y);
}

int MyWindow::XOR(int x, int y)
{
    return x^y;
}

void MyWindow::on_checkBox1_clicked(bool checked)
{
    isLayerActive[0] = checked;
    showactive();
}


void MyWindow::on_checkBox2_clicked(bool checked)
{
    isLayerActive[1] = checked;
    showactive();
}

void MyWindow::on_checkBox3_clicked(bool checked)
{
    isLayerActive[2] = checked;
    showactive();
}

void MyWindow::on_checkBox4_clicked(bool checked)
{
    isLayerActive[3] = checked;
    showactive();
}

void MyWindow::on_checkBox5_clicked(bool checked)
{
    isLayerActive[4] = checked;
    showactive();
}

void MyWindow::on_horizontalSlider1_sliderMoved(int position)
{
    layersOpacity[0] = (double)(position/100.0);
    showactive();
}


void MyWindow::on_horizontalSlider2_sliderMoved(int position)
{
    layersOpacity[1] = (double)(position/100.0);
    showactive();
}

void MyWindow::on_horizontalSlider3_sliderMoved(int position)
{
    layersOpacity[2] = (double)(position/100.0);
    showactive();
}

void MyWindow::on_horizontalSlider4_sliderMoved(int position)
{
    layersOpacity[3] = (double)(position/100.0);
    showactive();
}

void MyWindow::on_horizontalSlider5_sliderMoved(int position)
{
    layersOpacity[4] = (double)(position/100.0);
    showactive();
}

void MyWindow::on_comboBox_currentIndexChanged(int index)
{
    layersMode[0] = index;
    showactive();
}

void MyWindow::on_comboBox_2_currentIndexChanged(int index)
{
    layersMode[1] = index;
    showactive();
}

void MyWindow::on_comboBox_3_currentIndexChanged(int index)
{
    layersMode[2] = index;
    showactive();
}

void MyWindow::on_comboBox_4_currentIndexChanged(int index)
{
    layersMode[3] = index;
    showactive();
}


void MyWindow::on_comboBox_5_currentIndexChanged(int index)
{
    layersMode[4] = index;
    showactive();
}
