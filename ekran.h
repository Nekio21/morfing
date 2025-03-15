#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <vector>
#include <iostream>

using namespace std;

struct Punkt{
    int x;
    int y;
};

struct Punkt2{
    double x;
    double y;
};

struct Rgb{
    int r;
    int g;
    int b;
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent = nullptr);
    void krzywaBezieraZaladuj();
    void bsplineZaladuj();
    void drawMousePressEvent();
    void drawMousePressEvent(int x, int y);

    char option = 'p';
    Rgb chooseRgb = {124,54,23};
    Punkt trojkat[2][3] = {{{30,30},{70,40}, {300,30}},{{30,30},{70,40}, {300,30}}};
    int indexKolka = -1;
    QImage im;
    QImage imKelner;
    QImage imKelner2;

    bool first = true;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

    vector<Punkt> ve;
    vector<Punkt> zamalujPunkty;
    vector<Punkt> polygonPoints;
    int indexOptionD;
    void drawPixel(int x, int y, int r, int g, int b, QImage* i);
    void mouseMoveEvent(QMouseEvent * e);
    void rysujTrojkat();
    void rysujLinie(int x1, int y1, int x2, int y2, QImage* i);
    void rysujOkrag(int x0, int y0, int R, QImage* i);
    void drawPixel(int x, int y, Rgb rgb, QImage* i);
    void drawPixel(int x, int y, int r, int g, int b);
    void drawPixel(int x, int y, Rgb rgb);
    Rgb getColor(int x, int y);
    int zwrocY(int x, int x1, int y1, int x2, int y2);
    int zwrocX(int y, int x1, int y1, int x2, int y2);
    void zamaluj(Rgb, Rgb);
    void rysujOkrag(int,int,int);
    void rysujElipse(int x0, int y0, int R1, int R2, int N);
    void rysujLinie(int x1, int y1, int x2, int y2);
    void rysujKrzywaBeziera(Punkt,Punkt,Punkt, Punkt, int, bool);
    void rysujBspline(Punkt,Punkt,Punkt, Punkt, int, bool);
    Rgb getColor(int x, int y, QImage* i);
    int krzywaBeziera(int,int,int,int, double);
    int krzywaBspline(int,int,int,int, double);
    void rysujPoligon(vector<Punkt>);
    void findX(vector<int>&, vector<Punkt>, int y);
    int findXDeep(Punkt, Punkt, int y);
    void wybierzPunkt(int, int);
    int countR(int,int,int,int);
    void wypelnij(vector<int> x, int y);
private:

    int x1;
    int y1;
    int x2;
    int y2;
    int xOldLinia = -1;
    int yOldLinia = -1;
    bool second = false;
signals:

};

#endif // EKRAN_H
