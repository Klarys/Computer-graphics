#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include<algorithm> // for copy() and assign()
#include <QTime>

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
    obrazwyswietlany3 = new QImage(szer,wys,QImage::Format_RGB32);
    stanPoczatkowy();
    //rysujodcinek(100,100,200,300, obrazwyswietlany1); test rysowania odcinka
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

void MainWindow::stanPoczatkowy()
{
    Punktyobr1.clear();
    Punktyobr2.clear();
    AktywnepunktysiatkiL.clear();
    AktywnepunktysiatkiP.clear();
    PunktysiatkiL.clear();
    PunktysiatkiP.clear();
    Klatki.clear();
    obrazwyswietlany1 = new QImage(":/new/prefix1/face1");
    obrazwyswietlany2 = new QImage(":/new/prefix1/face2");

    unsigned char *ptr;
    ptr = obrazwyswietlany2->bits();
    generujSiatke();
    rysujSiatke();
}

void MainWindow::generujSiatke()
{
    QVector <QVector <int> > trojkat1;
    QVector <QVector <int> > trojkat2;
    QVector <int> tmp;

    for(int x=0; x<=szer-100; x=x+100)
    {
        for(int y=0; y<=wys-100; y=y+100)
        {
            tmp.push_back(x);
            if(y+100 == 400)
            {
               tmp.push_back(y+99);
            }
            else tmp.push_back(y+100);
            trojkat1.push_back(tmp);
            tmp.clear();

            tmp.push_back(x);
            tmp.push_back(y);
            trojkat1.push_back(tmp);
            tmp.clear();

            if(x+100 == 400)
            {
                tmp.push_back(x+99);
            }
            else tmp.push_back(x+100);
            tmp.push_back(y);
            trojkat1.push_back(tmp);
            tmp.clear();
            Punktyobr1.push_back(trojkat1);
            Punktyobr2.push_back(trojkat1);

            if(x+100 == 400)
            {
                tmp.push_back(x+99);
            }
            else tmp.push_back(x+100);
            tmp.push_back(y);
            trojkat2.push_back(tmp);
            tmp.clear();

            if(x+100 == 400)
            {
                tmp.push_back(x+99);
            }
            else tmp.push_back(x+100);
            if(y+100 == 400)
            {
               tmp.push_back(y+99);
            }
            else tmp.push_back(y+100);
            trojkat2.push_back(tmp);
            tmp.clear();

            tmp.push_back(x);
            if(y+100 == 400)
            {
               tmp.push_back(y+99);
            }
            else tmp.push_back(y+100);
            trojkat2.push_back(tmp);
            tmp.clear();
            Punktyobr1.push_back(trojkat2);
            Punktyobr2.push_back(trojkat2);

            trojkat1.clear();
            trojkat2.clear();

            if(x != 0 && y!=0)
            {
                tmp.push_back(x);
                tmp.push_back(y);
                AktywnepunktysiatkiL.push_back(tmp);
                PunktysiatkiL.push_back(tmp);
                tmp.clear();
            }
            else
            {
                tmp.push_back(x);
                tmp.push_back(y);
                PunktysiatkiL.push_back(tmp);
                tmp.clear();
            }
        }
    }

    //dodanie punktow krawedziowych
    tmp.push_back(399);
    tmp.push_back(0);
    PunktysiatkiL.push_back(tmp);
    tmp[1] += 100;
    PunktysiatkiL.push_back(tmp);
    tmp[1] += 100;
    PunktysiatkiL.push_back(tmp);
    tmp[1] += 100;
    PunktysiatkiL.push_back(tmp);
    tmp[1] += 99;
    PunktysiatkiL.push_back(tmp);
    tmp.clear();

    tmp.push_back(0);
    tmp.push_back(399);
    PunktysiatkiL.push_back(tmp);
    tmp[0] += 100;
    PunktysiatkiL.push_back(tmp);
    tmp[0] += 100;
    PunktysiatkiL.push_back(tmp);
    tmp[0] += 100;
    PunktysiatkiL.push_back(tmp);
    tmp[0] += 99;
    PunktysiatkiL.push_back(tmp);
    tmp.clear();

    for(int i=0; i<PunktysiatkiL.size(); i++)
    {
        PunktysiatkiP.push_back(PunktysiatkiL[i]);
    }
    for(int i=0; i<AktywnepunktysiatkiL.size(); i++)
    {
        AktywnepunktysiatkiP.push_back(AktywnepunktysiatkiL[i]);
    }

}

void MainWindow::rysujSiatke()
{
    QImage * obrazdocelowy;
    for(int i=0; i<Punktyobr1.size(); i++) //punktyobr1 i 2 maja ten sam rozmiar
    {
        for(int x=0; x<Punktyobr1[i].size(); x++)
        {
            for(int y=0; y<Punktyobr1[i].size(); y++)
            {
                obrazdocelowy = obrazwyswietlany1;
                rysujodcinek(Punktyobr1[i][x][0], Punktyobr1[i][x][1], Punktyobr1[i][y][0], Punktyobr1[i][y][1], obrazdocelowy);
                rysujodcinek(Punktyobr1[i][x][0], Punktyobr1[i][x][1], Punktyobr1[i][y][0], Punktyobr1[i][y][1], obrazdocelowy);
                rysujodcinek(Punktyobr1[i][x][0], Punktyobr1[i][x][1], Punktyobr1[i][y][0], Punktyobr1[i][y][1], obrazdocelowy);

                obrazdocelowy = obrazwyswietlany2;
                rysujodcinek(Punktyobr2[i][x][0], Punktyobr2[i][x][1], Punktyobr2[i][y][0], Punktyobr2[i][y][1], obrazdocelowy);
                rysujodcinek(Punktyobr2[i][x][0], Punktyobr2[i][x][1], Punktyobr2[i][y][0], Punktyobr2[i][y][1], obrazdocelowy);
                rysujodcinek(Punktyobr2[i][x][0], Punktyobr2[i][x][1], Punktyobr2[i][y][0], Punktyobr2[i][y][1], obrazdocelowy);

            }
        }
    }
    for(int i=0; i<PunktysiatkiL.size(); i++) //punktyobr1 i 2 maja ten sam rozmiar
    {
            obrazdocelowy = obrazwyswietlany1;
            rysujPunktCzerwony(PunktysiatkiL[i][0], PunktysiatkiL[i][1], obrazdocelowy);

            obrazdocelowy = obrazwyswietlany2;
            rysujPunktCzerwony(PunktysiatkiP[i][0], PunktysiatkiP[i][1], obrazdocelowy);
    }

    update();
}

void MainWindow::morphing()
{
     QImage* pom1 = new QImage(szer,wys,QImage::Format_RGB32);
      QImage* pom2 = new QImage(szer,wys,QImage::Format_RGB32);
    for(double n=0; n<liczbaKlatek; n++) //dla kazdej klatki
    {
        QImage* klatka = new QImage(szer,wys,QImage::Format_RGB32);
        for(int i=Punktyobr1.size()-1; i>=0; i--) //dla wszystkich trojkatow Punktyobr1 i 2
         {

            //tworzenie trojkata An Bn Cn
            double Ax = (1.0-(double)n/(double)liczbaKlatek)*(double)Punktyobr1[i][0][0] + (double)n/(double)liczbaKlatek*(double)Punktyobr2[i][0][0];
            double Ay = (1.0-(double)n/(double)liczbaKlatek)*(double)Punktyobr1[i][0][1] + (double)n/(double)liczbaKlatek*(double)Punktyobr2[i][0][1];

            double Bx = (1.0-(double)n/(double)liczbaKlatek)*(double)Punktyobr1[i][1][0] + (double)n/(double)liczbaKlatek*(double)Punktyobr2[i][1][0];
            double By = (1.0-(double)n/(double)liczbaKlatek)*(double)Punktyobr1[i][1][1] + (double)n/(double)liczbaKlatek*(double)Punktyobr2[i][1][1];

            double Cx = (1.0-(double)n/(double)liczbaKlatek)*(double)Punktyobr1[i][2][0] + (double)n/(double)liczbaKlatek*(double)Punktyobr2[i][2][0];
            double Cy = (1.0-(double)n/(double)liczbaKlatek)*(double)Punktyobr1[i][2][1] + (double)n/(double)liczbaKlatek*(double)Punktyobr2[i][2][1];

            //tworzenie trojkata PQR i PQR2
            double Px = Ax;
            double P2x = Ax;
            double Py = Ay;
            double P2y = Ay;

            double Qx = Bx;
            double Q2x = Bx;
            double Qy = By;
            double Q2y = By;

            double Rx = Cx;
            double R2x = Cx;
            double Ry = Cy;
            double R2y = Cy;

            //nakladamy teksture na PQR
                double u,v,w;
                double mian = (Q2x-P2x)*(R2y-P2y)-(Q2y-P2y)*(R2x-P2x);


                int r,g,b;
                int r2,g2,b2;
                int rdocelowe, gdocelowe, bdocelowe;

                double xt, yt;
                double xt2, yt2;


                if(mian != 0)
                {
                    for(double x=0; x<szer; x++)
                    {
                        for(double y=0; y<wys; y++)
                        {

                            v = (double)((x-Px)*(Ry-Py)-(y-Py)*(Rx-Px))/(double)mian;
                            w = (double)((Qx-Px)*(y-Py) - (Qy-Py)*(x-Px))/(double)mian;
                            u = (double)1.0-v-w;



                            if(v>=0 && v<=1 && u>=0 && u<=1 && w>=0 && w<=1)
                            {
                                xt = u * Punktyobr1[i][0][0] + v * Punktyobr1[i][1][0] + w * Punktyobr1[i][2][0];
                                yt = u * Punktyobr1[i][0][1] + v * Punktyobr1[i][1][1] + w * Punktyobr1[i][2][1];

                                xt2 = u * Punktyobr2[i][0][0] + v * Punktyobr2[i][1][0] + w * Punktyobr2[i][2][0];
                                yt2 = u * Punktyobr2[i][0][1] + v * Punktyobr2[i][1][1] + w * Punktyobr2[i][2][1];

                                r = pobierzR(xt, yt, obrazwyswietlany1);
                                g = pobierzG(xt, yt, obrazwyswietlany1);
                                b = pobierzB(xt, yt, obrazwyswietlany1);

                                zapalPiksel(x, y, pom1, r, g, b);

                                r2 = pobierzR(xt2, yt2, obrazwyswietlany2);
                                g2 = pobierzG(xt2, yt2, obrazwyswietlany2);
                                b2 = pobierzB(xt2, yt2, obrazwyswietlany2);

                                zapalPiksel(x, y, pom2, r2, g2, b2);

                                rdocelowe = (1-((double)n/liczbaKlatek))*r + ((double)n/liczbaKlatek)*r2;
                                gdocelowe = (1-((double)n/liczbaKlatek))*g + ((double)n/liczbaKlatek)*g2;
                                bdocelowe = (1-((double)n/liczbaKlatek))*b + ((double)n/liczbaKlatek)*b2;

                                zapalPiksel(x, y, klatka, rdocelowe, gdocelowe, bdocelowe);
                            }

                        }
                    }
                }
        }
    Klatki.push_back(klatka);
    }
}

int MainWindow::pobierzR(int xt, int yt, QImage * obrazzrodlowy)
{
    unsigned char *ptr;
    ptr = obrazzrodlowy->bits();
    return ptr[szer*4*(int)yt + 4*(int)xt + 2];
}

int MainWindow::pobierzG(int xt, int yt, QImage * obrazzrodlowy)
{
    unsigned char *ptr;
    ptr = obrazzrodlowy->bits();
    return ptr[szer*4*(int)yt + 4*(int)xt + 1];
}

int MainWindow::pobierzB(int xt, int yt, QImage * obrazzrodlowy)
{
    unsigned char *ptr;
    ptr = obrazzrodlowy->bits();
    return ptr[szer*4*(int)yt + 4*(int)xt];
}

void MainWindow::zapalPiksel(int x, int y, QImage * obrazdocelowy, int r, int g, int b)
{
    unsigned char *ptr;
    ptr = obrazdocelowy->bits();
        ptr[szer*4*y + 4*x] = b;
        ptr[szer*4*y + 4*x + 1] = g;
        ptr[szer*4*y + 4*x + 2] = r;
}

void MainWindow::wyswietlanimacje()
{
    for(int n=0; n<liczbaKlatek; n++)
    {
        for(double i=0; i<wys; i++)
        {
            for(double j=0; j<szer; j++)
            {
                zapalPiksel(i, j, Klatki[n], obrazwyswietlany1);
            }
        }
        update();
        QTime pause = QTime::currentTime().addMSecs(50);
                    while(QTime::currentTime() < pause){
                        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                    }
    }
}

void MainWindow::zapalPiksel(int x, int y, QImage * obrazzrodlowy, QImage * obrazdocelowy)
{
    unsigned char *ptr;
    ptr = obrazzrodlowy->bits();

    int r,g,b;

    b = ptr[szer*4*(int)y + 4*(int)x];
    g = ptr[szer*4*(int)y + 4*(int)x + 1];
    r = ptr[szer*4*(int)y + 4*(int)x + 2];

    ptr = obrazdocelowy->bits();
    ptr[szer*4*y + 4*x] = b;
    ptr[szer*4*y + 4*x + 1] = g;
    ptr[szer*4*y + 4*x + 2] = r;
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

void MainWindow::rysujPunktCzerwony(int x, int y, QImage * obrazdocelowy)
{
    unsigned char *ptr;
    ptr = obrazdocelowy->bits();
    for(int i = x-5; i<=x+5; i++)
    {
        for(int j = y-5; j<=y+5; j++)
        {
            if(i>0 && i<szer && j>0 && j<wys)
            {
                ptr[szer*4*j + 4*i]=0;
                ptr[szer*4*j + 4*i + 1] = 0;
                ptr[szer*4*j + 4*i + 2] = 255;
            }

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
            if(i>0 && i<szer && j>0 && j<wys)
            {
                ptr[szer*4*j + 4*i]=0;
                ptr[szer*4*j + 4*i + 1] = 255;
                ptr[szer*4*j + 4*i + 2] = 0;
            }
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    QVector <int> input;
    QImage * obrazdocelowy;

    input.push_back(event->x());
    input.push_back(event->y());

        if(input[0] >= frameX && input[0] <= frameX+szer && input[1] >= frameY && input[1] <= frameY+wys) //kliknieto w frame1
        {
            input[0] -= frameX;
            input[1] -= frameY;
            obrazdocelowy = obrazwyswietlany1;

            for(int i=0; i<AktywnepunktysiatkiL.size(); i++)
            {
                if(input[0] >= AktywnepunktysiatkiL[i][0]-5 && input[0] <= AktywnepunktysiatkiL[i][0]+5 && input[1] >= AktywnepunktysiatkiL[i][1]-5 && input[1] <= AktywnepunktysiatkiL[i][1]+5) //kliknieto w punkt na siatce
                {
                    rysujPunktZielony(AktywnepunktysiatkiL[i][0], AktywnepunktysiatkiL[i][1], obrazdocelowy);
                    indeksLewyx = AktywnepunktysiatkiL[i][0];
                    indeksLewyy = AktywnepunktysiatkiL[i][1];
                }
            }
        }
        else if(input[0] >= frame2X && input[0] <= frame2X+szer && input[1] >= frame2Y && input[1] <= frame2Y+wys)  //kliknieto w frame2
        {
            input[0] -= frame2X;
            input[1] -= frame2Y;
            obrazdocelowy = obrazwyswietlany2;

            for(int i=0; i<AktywnepunktysiatkiP.size(); i++)
            {
                if(input[0] >= AktywnepunktysiatkiP[i][0]-5 && input[0] <= AktywnepunktysiatkiP[i][0]+5 && input[1] >= AktywnepunktysiatkiP[i][1]-5 && input[1] <= AktywnepunktysiatkiP[i][1]+5) //kliknieto w punkt na siatce
                {
                    rysujPunktZielony(AktywnepunktysiatkiP[i][0], AktywnepunktysiatkiP[i][1], obrazdocelowy);
                    indeksPrawyx = AktywnepunktysiatkiP[i][0];
                    indeksPrawyy = AktywnepunktysiatkiP[i][1];
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

    if(indeksLewyx >= 0)
    {
        input[0] -= frameX;
        input[1] -= frameY;

        obrazwyswietlany1 = new QImage(":/new/prefix1/face1");
        obrazdocelowy = obrazwyswietlany1;
        rysujPunktZielony(input[0], input[1], obrazdocelowy);

    }
    else if(indeksPrawyx >= 0)
    {

        input[0] -= frame2X;
        input[1] -= frame2Y;
        obrazwyswietlany2 = new QImage(":/new/prefix1/face2");
        obrazdocelowy = obrazwyswietlany2;
        rysujPunktZielony(input[0], input[1], obrazdocelowy);
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QVector <int> input;

    input.push_back(event->x());
    input.push_back(event->y());

    if(indeksLewyx != -1)
    {
        input[0] -= frameX;
        input[1] -= frameY;
        for(int i=0; i<PunktysiatkiL.size(); i++)
        {
            if(PunktysiatkiL[i][0] == indeksLewyx && PunktysiatkiL[i][1] == indeksLewyy)
            {
                PunktysiatkiL[i][0] = input[0];
                PunktysiatkiL[i][1] = input[1];
            }
        }
        for(int i=0; i<AktywnepunktysiatkiL.size(); i++)
        {
            if(AktywnepunktysiatkiL[i][0] == indeksLewyx && AktywnepunktysiatkiL[i][1] == indeksLewyy)
            {
                AktywnepunktysiatkiL[i][0] = input[0];
                AktywnepunktysiatkiL[i][1] = input[1];
            }
        }
        for(int i=0; i<Punktyobr1.size(); i++)
        {
            for(int j=0; j<Punktyobr1[i].size(); j++)
            {
                if(Punktyobr1[i][j][0] == indeksLewyx && Punktyobr1[i][j][1] == indeksLewyy)
                {
                    Punktyobr1[i][j][0] = input[0];
                    Punktyobr1[i][j][1] = input[1];
                }
            }
        }

        indeksLewyx = -1;
        indeksLewyy = -1;
        rysujSiatke();
        update();
    }
    if(indeksPrawyx != -1)
    {
        input[0] -= frame2X;
        input[1] -= frame2Y;
        for(int i=0; i<PunktysiatkiP.size(); i++)
        {
            if(PunktysiatkiP[i][0] == indeksPrawyx && PunktysiatkiP[i][1] == indeksPrawyy)
            {
                PunktysiatkiP[i][0] = input[0];
                PunktysiatkiP[i][1] = input[1];
            }
        }
        for(int i=0; i<AktywnepunktysiatkiP.size(); i++)
        {
            if(AktywnepunktysiatkiP[i][0] == indeksPrawyx && AktywnepunktysiatkiP[i][1] == indeksPrawyy)
            {
                AktywnepunktysiatkiP[i][0] = input[0];
                AktywnepunktysiatkiP[i][1] = input[1];
            }
        }
        for(int i=0; i<Punktyobr2.size(); i++)
        {
            for(int j=0; j<Punktyobr2[i].size(); j++)
            {
                if(Punktyobr2[i][j][0] == indeksPrawyx && Punktyobr2[i][j][1] == indeksPrawyy)
                {
                    Punktyobr2[i][j][0] = input[0];
                    Punktyobr2[i][j][1] = input[1];
                }
            }
        }
        indeksPrawyx = -1;
        indeksPrawyy = -1;
        rysujSiatke();
        update();
    }

}

void MainWindow::on_pushButton_2_clicked() //wyjscie
{
    qApp->quit();
}

void MainWindow::on_pushButton_clicked() //reset
{
    stanPoczatkowy();
    update();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    liczbaKlatek = arg1;
}

void MainWindow::on_pushButton_3_clicked()
{
    obrazwyswietlany1 = new QImage(":/new/prefix1/face1");
    obrazwyswietlany2 = new QImage(":/new/prefix1/face2");
    update();
    morphing();
}

void MainWindow::on_pushButton_4_clicked()
{
    obrazwyswietlany1 = new QImage(szer,wys,QImage::Format_RGB32);
    bialeTlo();
    wyswietlanimacje();
}


void MainWindow::bialeTlo()
{
    unsigned char *ptr;
    ptr = obrazwyswietlany1->bits();
    for(int i=0; i<szer; i++)
    {
        for(int j=0; j<szer; j++)
        {
            ptr[szer*4*j + 4*i] = 255;
            ptr[szer*4*j + 4*i + 1] = 255;
            ptr[szer*4*j + 4*i + 2] = 255;
        }

    }
    update();
}

