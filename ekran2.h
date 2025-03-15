#ifndef EKRAN2_H
#define EKRAN2_H

#include <QWidget>
#include <QImage>
#include <QMouseEvent>
#include "ekran.h"

class Ekran2 : public virtual Ekran
{
    Q_OBJECT

public:
    explicit Ekran2(QWidget *parent = nullptr);
    QImage* imAbroad;
    QImage* imAbroad2;

    Punkt* trojkatAbroadA;
    Punkt* trojkatAbroadB;
    Punkt* trojkatAbroadC;

    Punkt* trojkatAbroadA2;
    Punkt* trojkatAbroadB2;
    Punkt* trojkatAbroadC2;

    Punkt trojkatAbroad[2][3];
    Punkt trojkatNew[3];
    void rysujPoligon();
    void rysujPoligon(Punkt, Punkt, Punkt);
    void posredniTrojkat();

    double korektaX;
    double korektaY;

    double korektaX2;
    double korektaY2;
    int value = 0;
protected:
    void paintEvent(QPaintEvent *);
    void rysujTrojkat();
    void wypelnij2(vector<int> x, int y);
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void rysujWnetrzeTrojkata();
    void wypelnij(vector<int> x, int y);
    void rysujLinieTrojka2(int x1, int x2, int y, double W);


    void rysujLinieTrojka(int x1, int x2, int y, double W);
private:

};

#endif // EKRAN2_H
