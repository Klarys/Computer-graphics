// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"

// Dolaczamy plik naglowkowy zawierajacy definicje GUI
// Plik ten jest generowany automatycznie
// z pliku XML "mywindow.ui"
#include "ui_mywindow.h"
#include <cstdlib>
#include <cmath>

// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej, nastepnie tworzymy
// obiekt klasy Ui_MyWindow reprezentujacy GUI
MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    // Wywolujemy funkcje tworzaca elementy GUI
    // Jej definicja znajduje sie w pliku "ui_mywindow.h"
    ui->setupUi(this);

    // Pobieramy wymiary i wspolrzedne lewego gornego naroznika ramki
    // i ustawiamy wartosci odpowiednich pol
    // Uwaga: ramke "rysujFrame" wykorzystujemy tylko do
    // wygodnego ustaiwenia tych wymiarow. Rysunek bedziemy wyswietlac
    // bezposrednio w glownym oknie aplikacji.
    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);

}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete ui;
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku "Wyjscie" (exitButton)
// Uwaga: polaczenie tej funkcji z sygnalem "clicked"
// emitowanym przez przycisk jest realizowane
// za pomoca funkcji QMetaObject::connectSlotsByName(MyWindow)
// znajdujacej sie w automatycznie generowanym pliku "ui_mywindow.h"
// Nie musimy wiec sami wywolywac funkcji "connect"
void MyWindow::on_exitButton_clicked()
{
    // qApp to globalny wskaznik do obiektu reprezentujacego aplikacje
    // quit() to funkcja (slot) powodujaca zakonczenie aplikacji z kodem 0 (brak bledu)
    qApp->quit();
}


// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX,poczY,*img);
}



/*
// Funkcja powoduje zamalowanie obszaru rysowania pewnym wzorem
void MyWindow::rysuj1()
{
        unsigned char *ptr;
        ptr = img->bits();
        int szer = img->width();
        int wys = img->height();

        int i,j;
        for(i=0;i<wys;i++)
        {
                for(j=0;j<szer ;j++)
                {
                        ptr[szer*4*i + 4*j]=i;
                        ptr[szer*4*i + 4*j + 1] = j;
                        ptr[szer*4*i + 4*j + 2] = i*j;
                }
        }
}
*/

void MyWindow::drawred()
{
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int wys = img->height();

    int i,j;
    for(i=0; i<wys; i++)
    {
            for(j=0; j<szer; j++)
            {
                    ptr[szer*4*i + 4*j]= i/3;
                    ptr[szer*4*i + 4*j + 1] = j/3;
                    ptr[szer*4*i + 4*j + 2] = redvalue;
            }
    }
    update();
}

void MyWindow::drawgreen()
{
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int wys = img->height();

    int i,j;
    for(i=0; i<wys; i++)
    {
            for(j=0; j<szer; j++)
            {
                    ptr[szer*4*i + 4*j]= i/3;
                    ptr[szer*4*i + 4*j + 1] = greenvalue;
                    ptr[szer*4*i + 4*j + 2] = j/3;
            }
    }
    update();
}

void MyWindow::drawblue()
{
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int wys = img->height();

    int i,j;
    for(i=0; i<wys; i++)
    {
            for(j=0; j<szer; j++)
            {
                    ptr[szer*4*i + 4*j]= bluevalue;
                    ptr[szer*4*i + 4*j + 1] = i/3;
                    ptr[szer*4*i + 4*j + 2] = j/3;
            }
    }
    update();
}

void MyWindow::drawhue()
{
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int wys = img->height();

    int i,j;
    for(i=0; i<wys; i++)
    {
            for(j=0; j<szer; j++)
            {
                    saturationvalue = ((double)i/wys);
                    valuevalue = ((double)j/szer);
                    convert();
                    ptr[szer*4*i + 4*j] = b;
                    ptr[szer*4*i + 4*j + 1] = g;
                    ptr[szer*4*i + 4*j + 2] = r;
            }
    }
    update();
}

void MyWindow::drawsaturation()
{
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int wys = img->height();

    int i,j;
    for(i=0; i<wys; i++)
    {
            for(j=0; j<szer; j++)
            {
                    huevalue = ((double)i/wys * 360.0);
                    valuevalue = ((double)j/szer);
                    convert();
                    ptr[szer*4*(765-j-1) + 4*i] = b;
                    ptr[szer*4*(765-j-1) + 4*i + 1] = g;
                    ptr[szer*4*(765-j-1) + 4*i + 2] = r;
            }
    }
    update();
}

void MyWindow::drawvalue()
{
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int wys = img->height();

    int i,j;
    for(i=0; i<wys; i++)
    {
            for(j=0; j<szer; j++)
            {
                    huevalue = ((double)i/wys * 360.0);
                    saturationvalue = ((double)j/wys);
                    convert();

                    ptr[szer*4*j + 4*i] = b;
                    ptr[szer*4*j + 4*i + 1] = g;
                    ptr[szer*4*j + 4*i + 2] = r;
            }
    }
    update();
}


void MyWindow::convert()
{
    double H = huevalue/60.0;
    double C = valuevalue * saturationvalue;
    double X = C*(1 - abs(fmod(H,2) - 1) );

    if(H<=1)
    {
        r = C;
        g = X;
        b = 0;
    }
    else if(H<=2)
    {
        r = X;
        g = C;
        b = 0;
    }
    else if(H<=3)
    {
        r = 0;
        g = C;
        b = X;
    }
    else if(H<=4)
    {
        r = 0;
        g = X;
        b = C;
    }
    else if(H<=5)
    {
        r = X;
        g = 0;
        b = C;
    }
    else if(H<=6)
    {
        r = C;
        g = 0;
        b = X;
    }
    else
    {
        r = 0;
        g = 0;
        b = 0;
    }

    double m = (valuevalue - C);
    r += m;
    g += m;
    b += m;

    r *= 255;
    g *= 255;
    b *= 255;
}

void MyWindow::on_radioButton_clicked()
{
    red = true;
    green = false;
    blue = false;
}

void MyWindow::on_radioButton_2_clicked()
{
    red = false;
    green = true;
    blue = false;
}

void MyWindow::on_radioButton_3_clicked()
{
    red = false;
    green = false;
    blue = true;
}

void MyWindow::on_verticalSlider_sliderMoved(int position)
{
    if(red)
    {
        redvalue = position;
        greenvalue = 0;
        bluevalue = 0;
        drawred();
    }
    if(green)
    {
        redvalue = 0;
        greenvalue = position;
        bluevalue = 0;
        drawgreen();
    }
    if(blue)
    {
        redvalue = 0;
        greenvalue = 0;
        bluevalue = position;
        drawblue();
    }
}


void MyWindow::on_verticalSlider_2_sliderMoved(int position)
{
    hue = true;
    saturation = false;
    value = false;
    huevalue = position;
    saturationvalue = 0;
    valuevalue = 0;
    drawhue();
}

void MyWindow::on_verticalSlider_3_sliderMoved(int position)
{
    hue = false;
    saturation = true;
    value = false;
    huevalue = 0;
    saturationvalue = position/100.0;
    valuevalue = 0;
    drawsaturation();
}

void MyWindow::on_verticalSlider_4_sliderMoved(int position)
{
    hue = false;
    saturation = false;
    value = true;
    huevalue = 0;
    saturationvalue = 0;
    valuevalue = position/100.0;
    drawvalue();
}
