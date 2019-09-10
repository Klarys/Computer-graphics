#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    szer = ui->frame->width();
    wys = ui->frame->height();

    frameX = ui->frame->x();
    frameY = ui->frame->y();

    frame2X = ui->frame2->x();
    frame2Y = ui->frame2->y();

    obrazwczytany = new QImage(":/new/prefix1/snek");
    obrazwyswietlany1 = new QImage(szer,wys,QImage::Format_RGB32);
    obrazwyswietlany2 = new QImage(szer,wys,QImage::Format_RGB32);
    stanPoczatkowy(true);
    //rysujodcinek(100,100,200,300, obrazwyswietlany1); test rysowania odcinka
    //rysujPunktZielony(100,100, obrazwyswietlany2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(frameX,frameY,*obrazwyswietlany1);
    p.drawImage(frame2X, frame2Y, *obrazwyswietlany2);
}

void MainWindow::stanPoczatkowy(bool czyszczeniePunktow)
{
    obrazwyswietlany1 = new QImage(":/new/prefix1/snek");

    unsigned char *ptr;
    ptr = obrazwyswietlany2->bits();

    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 0;
            ptr[szer*4*i + 4*j + 1] = 0;
            ptr[szer*4*i + 4*j + 2] = 0;
        }
    }
    iloscPunktow1 = 0;
    iloscPunktow2 = 0;
    if(czyszczeniePunktow)
    {
        Punktyobr1.clear();
        Punktyobr2.clear();
    }
}

void MainWindow::teksturowanie()
{
    double u,v,w;
    double mian = (Punktyobr2[1][0]-Punktyobr2[0][0])*(Punktyobr2[2][1]-Punktyobr2[0][1])-(Punktyobr2[1][1]-Punktyobr2[0][1])*(Punktyobr2[2][0]-Punktyobr2[0][0]);

    double xt, yt;
    if(mian != 0)
    {
        for(double i=0; i<wys; i++)
        {
            for(double j=0; j<szer; j++)
            {
                v = ((i-Punktyobr2[0][0])*(Punktyobr2[2][1]-Punktyobr2[0][1])-(j-Punktyobr2[0][1])*(Punktyobr2[2][0]-Punktyobr2[0][0]))/mian;
                w = ((Punktyobr2[1][0]-Punktyobr2[0][0])*(j-Punktyobr2[0][1]) - (Punktyobr2[1][1]-Punktyobr2[0][1])*(i-Punktyobr2[0][0]))/mian;
                u = 1.0-v-w;

                if(v>=0 && v<=1 && u>=0 && u<=1 && w>=0 && w<=1)
                {
                    xt = u * Punktyobr1[0][0] + v * Punktyobr1[1][0] + w * Punktyobr1[2][0];
                    yt = u * Punktyobr1[0][1] + v * Punktyobr1[1][1] + w * Punktyobr1[2][1];

                    zapalPiksel(i, j, xt, yt, obrazwyswietlany2);
                }

            }
        }
    }

}
void MainWindow::zapalPiksel(int x, int y, QImage * obrazdocelowy)
{
    unsigned char *ptr;
    ptr = obrazdocelowy->bits();
    ptr[szer*4*y + 4*x] = 0;
    ptr[szer*4*y + 4*x + 1] = 0;
    ptr[szer*4*y + 4*x + 2] = 255;
}

void MainWindow::zapalPiksel(int x, int y, double xt, double yt, QImage * obrazdocelowy)
{
    unsigned char *ptr;
    ptr = obrazwyswietlany1->bits();

    int r,g,b;

    b = ptr[szer*4*(int)yt + 4*(int)xt];
    g = ptr[szer*4*(int)yt + 4*(int)xt + 1];
    r = ptr[szer*4*(int)yt + 4*(int)xt + 2];

    ptr = obrazdocelowy->bits();
    ptr[szer*4*y + 4*x] = b;
    ptr[szer*4*y + 4*x + 1] = g;
    ptr[szer*4*y + 4*x + 2] = r;
}

void MainWindow::rysujodcinek(int xp, int yp, int xk, int yk, QImage * obrazdocelowy)
{
    double a, b, x, y, tmp;
    a = (double)(yk-yp)/(double)(xk-xp);
    b = yk - (a*xk);

    if ((xp>=0)&&(yp>=0)&&(xp<szer)&&(yp<wys))
    {
        if ((xk>=0)&&(yk>=0)&&(xk<szer)&&(yk<wys))
        {

            if(xk != xp)
            {
                if(xk < xp)
                {
                    for(x=xp; x>xk; x--)
                    {
                        y = (a*x) + b;
                        zapalPiksel(x, y, obrazdocelowy);
                    }
                }
                else
                {
                    for(x=xp; x<xk; x++)
                    {
                        y = (a*x) + b;
                        zapalPiksel(x, y, obrazdocelowy);
                    }
                }
                if(yk < yp)
                {
                    for(y=yp; y>yk; y--)
                    {
                        x = (double)(y-b)/a;
                        zapalPiksel(x, y, obrazdocelowy);
                    }
                }
                else
                {
                    for(y=yp; y<yk; y++){
                        x = (double)(y-b)/a;
                        zapalPiksel(x, y, obrazdocelowy);
                    }
                }
            }
            else
            {
                if(yk < yp)
                {
                    tmp=yk;
                    yk=yp;
                    yp=tmp;
                }
                for(y=yp; y<yk; y++)
                {
                    zapalPiksel(xp, y, obrazdocelowy);
                }
            }
        }
    }
}

void MainWindow::rysujPunktCzerwony(int x, int y, QImage * obrazdocelowy)
{
    unsigned char *ptr;
    ptr = obrazdocelowy->bits();
    for(int i = x-5; i<=x+5; i++)
    {
        for(int j = y-5; j<=y+5; j++)
        {
            ptr[szer*4*j + 4*i]=0;
            ptr[szer*4*j + 4*i + 1] = 0;
            ptr[szer*4*j + 4*i + 2] = 255;
        }
    }
}

void MainWindow::rysujPunktZielony(int x, int y, QImage * obrazdocelowy)
{
    unsigned char *ptr;
    ptr = obrazdocelowy->bits();
    for(int i = x-5; i<=x+5; i++)
    {
        for(int j = y-5; j<=y+5; j++)
        {
            ptr[szer*4*j + 4*i]=0;
            ptr[szer*4*j + 4*i + 1] = 255;
            ptr[szer*4*j + 4*i + 2] = 0;
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    QVector <int> input;
    QImage * obrazdocelowy;
    bool czyIstnieje = false;

    input.push_back(event->x());
    input.push_back(event->y());

        if(input[0] >= frameX && input[0] <= frameX+szer && input[1] >= frameY && input[1] <= frameY+wys && iloscPunktow1 <= 3) //kliknieto w frame1
        {
            input[0] -= frameX;
            input[1] -= frameY;
            obrazdocelowy = obrazwyswietlany1;

            for(int i=0; i<Punktyobr1.size(); i++)
            {
                if(input[0] >= Punktyobr1[i][0]-5 && input[0] <= Punktyobr1[i][0]+5 && input[1] >= Punktyobr1[i][1]-5 && input[1] <= Punktyobr1[i][1]+5)
                {
                    rysujPunktZielony(Punktyobr1[i][0], Punktyobr1[i][1], obrazdocelowy);
                    czyIstnieje = true;
                    indeksLewy = i;
                }
            }
            if(!czyIstnieje && iloscPunktow1 < 3)
            {
                Punktyobr1.push_back(input);
                rysujPunktCzerwony(input[0], input[1], obrazdocelowy);
                iloscPunktow1++;
                if(iloscPunktow1 == 3)
                {
                    rysujodcinek(Punktyobr1[0][0], Punktyobr1[0][1], Punktyobr1[1][0], Punktyobr1[1][1], obrazdocelowy);
                    rysujodcinek(Punktyobr1[1][0], Punktyobr1[1][1], Punktyobr1[2][0], Punktyobr1[2][1], obrazdocelowy);
                    rysujodcinek(Punktyobr1[2][0], Punktyobr1[2][1], Punktyobr1[0][0], Punktyobr1[0][1], obrazdocelowy);
                }

            }
        }
        else if(input[0] >= frame2X && input[0] <= frame2X+szer && input[1] >= frame2Y && input[1] <= frame2Y+wys && iloscPunktow2 <= 3)  //kliknieto w frame2
        {
            input[0] -= frame2X;
            input[1] -= frame2Y;
            obrazdocelowy = obrazwyswietlany2;

            for(int i=0; i<Punktyobr2.size(); i++)
            {
                if(input[0] >= Punktyobr2[i][0]-5 && input[0] <= Punktyobr2[i][0]+5 && input[1] >= Punktyobr2[i][1]-5 && input[1] <= Punktyobr2[i][1]+5)
                {
                    rysujPunktZielony(Punktyobr2[i][0], Punktyobr2[i][1], obrazdocelowy);
                    czyIstnieje = true;
                    indeksPrawy = i;
                }
            }
            if(!czyIstnieje && iloscPunktow2 < 3)
            {
                Punktyobr2.push_back(input);
                rysujPunktCzerwony(input[0], input[1], obrazdocelowy);
                iloscPunktow2++;
                if(iloscPunktow2 == 3)
                {
                    rysujodcinek(Punktyobr2[0][0], Punktyobr2[0][1], Punktyobr2[1][0], Punktyobr2[1][1], obrazdocelowy);
                    rysujodcinek(Punktyobr2[1][0], Punktyobr2[1][1], Punktyobr2[2][0], Punktyobr2[2][1], obrazdocelowy);
                    rysujodcinek(Punktyobr2[2][0], Punktyobr2[2][1], Punktyobr2[0][0], Punktyobr2[0][1], obrazdocelowy);
                }
            }
        }

     update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QVector <int> input;
    QImage * obrazdocelowy;

    input.push_back(event->x());
    input.push_back(event->y());

    if(indeksLewy >= 0)
    {
        input[0] -= frameX;
        input[1] -= frameY;

        obrazwyswietlany1 = new QImage(":/new/prefix1/snek");
        obrazdocelowy = obrazwyswietlany1;

        for(int i=0; i<Punktyobr1.size(); i++)
        {
            if(i == indeksLewy)
            {
                rysujPunktZielony(input[0], input[1], obrazdocelowy);
                Punktyobr1[i][0] = input[0];
                Punktyobr1[i][1] = input[1];
            }
            else rysujPunktCzerwony(Punktyobr1[i][0], Punktyobr1[i][1], obrazdocelowy);
        }
        rysujodcinek(Punktyobr1[0][0], Punktyobr1[0][1], Punktyobr1[1][0], Punktyobr1[1][1], obrazdocelowy);
        rysujodcinek(Punktyobr1[1][0], Punktyobr1[1][1], Punktyobr1[2][0], Punktyobr1[2][1], obrazdocelowy);
        rysujodcinek(Punktyobr1[2][0], Punktyobr1[2][1], Punktyobr1[0][0], Punktyobr1[0][1], obrazdocelowy);
    }
    else if(indeksPrawy >= 0)
    {

        input[0] -= frame2X;
        input[1] -= frame2Y;
        obrazdocelowy = obrazwyswietlany2;

        unsigned char *ptr;
        ptr = obrazwyswietlany2->bits();
        for(int i=0; i<wys; i++)
        {
            for(int j=0; j<szer; j++)
            {
                ptr[szer*4*i + 4*j] = 0;
                ptr[szer*4*i + 4*j + 1] = 0;
                ptr[szer*4*i + 4*j + 2] = 0;
            }
        }
        for(int i=0; i<Punktyobr2.size(); i++)
        {
            if(i == indeksPrawy)
            {
                rysujPunktZielony(input[0], input[1], obrazdocelowy);
                Punktyobr2[i][0] = input[0];
                Punktyobr2[i][1] = input[1];
            }
            else rysujPunktCzerwony(Punktyobr2[i][0], Punktyobr2[i][1], obrazdocelowy);
        }
        rysujodcinek(Punktyobr2[0][0], Punktyobr2[0][1], Punktyobr2[1][0], Punktyobr2[1][1], obrazdocelowy);
        rysujodcinek(Punktyobr2[1][0], Punktyobr2[1][1], Punktyobr2[2][0], Punktyobr2[2][1], obrazdocelowy);
        rysujodcinek(Punktyobr2[2][0], Punktyobr2[2][1], Punktyobr2[0][0], Punktyobr2[0][1], obrazdocelowy);
    }
     update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(indeksLewy != -1)
    {
        rysujPunktCzerwony(Punktyobr1[indeksLewy][0], Punktyobr1[indeksLewy][1], obrazwyswietlany1);
        indeksLewy = -1;
    }
    if(indeksPrawy != -1)
    {
        rysujPunktCzerwony(Punktyobr2[indeksPrawy][0], Punktyobr2[indeksPrawy][1], obrazwyswietlany2);
        indeksPrawy = -1;
    }
    if(iloscPunktow1 ==3 && iloscPunktow2 ==3) teksturowanie();
    update();
}

void MainWindow::on_pushButton_2_clicked() //wyjscie
{
    qApp->quit();
}

void MainWindow::on_pushButton_clicked() //reset
{
    stanPoczatkowy(true);
    update();
}
