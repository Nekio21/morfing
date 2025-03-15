#include "ekran.h"

#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "ekran2.h"

using namespace std;

Ekran::Ekran(QWidget *parent)
    : QWidget{parent}
{
    im = QImage(1200, 1000, QImage::Format_RGB32);
    im.fill(0);

    imKelner = QImage(1200, 1000, QImage::Format_RGB32);
    imKelner.fill(0);

    imKelner.load("zdj2.png");

    imKelner2 = QImage(1200, 1000, QImage::Format_RGB32);
    imKelner2.fill(0);

    imKelner2.load("zdj.png");
}

void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0,0, width(), height(), Qt::black);
    p.drawImage(0,0, im);
}

void Ekran::drawPixel(int x, int y, int r, int g, int b, QImage* i){

    if((x<0) || (y<0) || (i->width()<=x) || (i->height()<=y)) return;

    uchar *pix = i->scanLine(y) + 4*x;
    pix[0] = b;
    pix[1] = g;
    pix[2] = r;

}

void Ekran::drawPixel(int x, int y, int r, int g, int b){
    drawPixel(x,y,r,g,b,&im);
}

void Ekran::drawPixel(int x, int y, Rgb rgb){

   drawPixel(x, y, rgb.r, rgb.g, rgb.b);

}

void Ekran::drawPixel(int x, int y, Rgb rgb, QImage* i){

   drawPixel(x, y, rgb.r, rgb.g, rgb.b, i);

}


Rgb Ekran::getColor(int x, int y, QImage* i){

    if((x<0) || (y<0) || (i->width()<=x) || (i->height()<=y)) return {-1,-1,-1};

    uchar *pix = i->scanLine(y) + 4*x;

    return {pix[2], pix[1], pix[0]};
}

Rgb Ekran::getColor(int x, int y){

    return getColor(x,y, &im);
}


void Ekran::mousePressEvent(QMouseEvent * e){
  int x = e->pos().x();
  int y = e->pos().y();

  drawMousePressEvent(x,y);
}

void Ekran::drawMousePressEvent(){
    im.fill(0);

    indexKolka = -1;
    rysujTrojkat();

    update();
}


void Ekran::drawMousePressEvent(int x, int y){

    int linia;
    int liniaMin = width();
    int firstIndex = 0;

      indexKolka = -1;

    if(first == false) firstIndex = 1;

    drawMousePressEvent();

    for(int i=0;i<3; i++){
        linia = countR(x,y, trojkat[firstIndex][i].x, trojkat[firstIndex][i].y);
          cout<<"Linia: "<<linia<<endl;
          cout<<"LiniaMIN: "<<liniaMin<<endl;
        if((linia <= 5)&&(liniaMin > linia)){
            indexKolka = i;
            liniaMin = linia;
        }
    }
}


void Ekran::mouseMoveEvent(QMouseEvent * e){

    int firstIndex = 0;

    if(first == false) firstIndex = 1;

    if((indexKolka != -1)){
        trojkat[firstIndex][indexKolka].x = e->pos().x();
        trojkat[firstIndex][indexKolka].y = e->pos().y();

        im.fill(0);

        rysujTrojkat();
        update();
    }
}

void Ekran::rysujTrojkat(){


    cout<<"IMKLELNER: "<<imKelner.width()<<endl;
    cout<<"R"<<getColor(20,20, &imKelner).r<<endl;

    int moveX;
    int moveY;
    int firstIndex = 0;

    if(first == true){
        moveX = width()/2 - imKelner.width()/2;
        moveY = height()/2 - imKelner.height()/2;
    }else{
        moveX = width()/2 - imKelner2.width()/2;
        moveY = height()/2 - imKelner2.height()/2;
        firstIndex = 1;
    }

    Rgb color;

    for(int i=0;i<im.height();i++){
        for(int j=0;j<im.width();j++){

            if(first == true){
                color = getColor(j,i, &imKelner);
            }else{
                color = getColor(j,i, &imKelner2);
            }
           // cout<<"R: "<<color.r<<", G: "<<color.g<<", B: "<<color.b<<endl;

            if(color.b == -1){
                drawPixel(j+moveX,i+moveY, {0,0,0}, &im);
            }else{
                drawPixel(j+moveX,i+moveY, color, &im);
            }
        }
    }

    for(int i=0;i<3;i++){
      rysujOkrag(trojkat[firstIndex][i].x, trojkat[firstIndex][i].y, 3, &im);
      rysujLinie(trojkat[firstIndex][i%3].x, trojkat[firstIndex][i%3].y, trojkat[firstIndex][(i+1)%3].x, trojkat[firstIndex][(i+1)%3].y, &im);
    }
}

void Ekran::wybierzPunkt(int x, int y){
    int linia;
    int liniaMin = width();

    for(int i=0;i<ve.size(); i++){
        linia = countR(x,y, ve[i].x, ve[i].y);

        if((linia <= 5)&&(liniaMin > linia)){
            indexOptionD = i;
            liniaMin = linia;
            cout<<"wybrano index: "<<indexOptionD<<endl;
        }
    }
}

void Ekran::krzywaBezieraZaladuj(){
    im.fill(0);

    int ilosc = ve.size()-1;

    bool pokazKropki;

    if(option!='c'){
        pokazKropki = true;
    }

    for(int i=0;i<(ilosc/3);i++){
        rysujKrzywaBeziera(ve[i*3], ve[i*3+1], ve[i*3+2], ve[i*3+3],50, pokazKropki);
    }

    update();
}

void Ekran::bsplineZaladuj(){
    im.fill(0);

    int ilosc = ve.size()-1;

    bool pokazKropki;

    if(option!='c'){
        pokazKropki = true;
    }


    if(ilosc >= 3){
        for(int i=0;i<ilosc-2;i++){
            rysujBspline(ve[i], ve[i+1], ve[i+2], ve[i+3],50, pokazKropki);
        }
    }

    update();
}

int Ekran::zwrocY(int x, int x1, int y1, int x2, int y2){
    int y;

    y = y1 + (x-x1)*(double)(((y2-y1)/(double)(x2-x1))) + 0.5;

    return y;
}

int Ekran::zwrocX(int y, int x1, int y1, int x2, int y2){
    int x;

    x = ( (double)(y-y1) / ((double)(y2-y1)/(x2-x1)) ) + x1 + 0.5;



    return x;
}


int Ekran::countR(int x1, int y1, int x2, int y2){
   int value1 = (x2-x1) * (x2-x1);
   int value2 = (y2-y1) * (y2-y1);

   int suma = value1 + value2;

   int R = sqrt(suma);

   cout<<"R:"<<R<<endl;

   return R;
}

void Ekran::rysujOkrag(int x0, int y0, int R){

    rysujOkrag(x0, y0, R, &im);

}

void Ekran::rysujOkrag(int x0, int y0, int R, QImage* i){

    for(int x=0;;x++){

        int y = sqrt(R*R-x*x)+0.5;
        if(x>y)break;


        drawPixel(x+x0,y+y0,134,144,22, i);
        drawPixel(y+x0,x+y0,134,144,22, i);
        drawPixel(-x+x0,-y+y0,134,144,22, i);
        drawPixel(-y+x0,-x+y0,134,144,22, i);

        drawPixel(-x+x0,y+y0,134,144,22, i);
        drawPixel(-y+x0,x+y0,134,144,22, i);
        drawPixel(x+x0,-y+y0,134,144,22, i);
        drawPixel(y+x0,-x+y0,134,144,22, i);
    }

}


void Ekran::rysujElipse(int x0,int  y0,int R1,int R2,int N){

    int x, xOld;
    int y, yOld;

    xOld = R1 * cos(0);
    yOld = R2 * sin(0);


    for(int i=1;i<=N;++i){
        double alfa = (2*M_PI*i)/(double)N;

        x = R1 * cos(alfa);
        y = R2 * sin(alfa);


        rysujLinie(x+x0, y+y0, xOld+x0, yOld+y0);

        xOld = x;
        yOld = y;
    }
}



void Ekran::rysujKrzywaBeziera(Punkt p1, Punkt p2, Punkt p3, Punkt p4, int iloscLini, bool show){

    int xOld = p1.x;
    int yOld = p1.y;

    if(show){
        rysujOkrag(p1.x, p1.y,4);
        rysujOkrag(p2.x, p2.y,4);
        rysujOkrag(p3.x, p3.y,4);
        rysujOkrag(p4.x, p4.y,4);
    }


    for(int k=1;k<=iloscLini;k++){

        int x = krzywaBeziera(p1.x, p2.x, p3.x, p4.x, k/(float)iloscLini);
        int y = krzywaBeziera(p1.y, p2.y, p3.y, p4.y, k/(float)iloscLini);

        rysujLinie(xOld, yOld, x, y);

        xOld = x;
        yOld = y;
    }
}


void Ekran::rysujBspline(Punkt p1, Punkt p2, Punkt p3, Punkt p4, int iloscLini, bool show){

    int xOld = krzywaBspline(p1.x, p2.x, p3.x, p4.x, 0);
    int yOld = krzywaBspline(p1.y, p2.y, p3.y, p4.y, 0);


    if(show){
        rysujOkrag(p1.x, p1.y,4);
        rysujOkrag(p2.x, p2.y,4);
        rysujOkrag(p3.x, p3.y,4);
        rysujOkrag(p4.x, p4.y,4);
    }

    for(int k=1;k<=iloscLini;k++){

        int x = krzywaBspline(p1.x, p2.x, p3.x, p4.x, k/(float)iloscLini);
        int y = krzywaBspline(p1.y, p2.y, p3.y, p4.y, k/(float)iloscLini);

        rysujLinie(xOld, yOld, x, y);

        xOld = x;
        yOld = y;
    }

}


//jesli chcesz wynik krzywej dla y wpisz y, a jesli dla x wpisz x;
//czym jest t??? T jest jakby ulamkniem
//jesli chcemy znac paremetry punktu w 1/2 w krzywej to t=0.5
//jesli na koncu to t = 1
//jesli na poczatku to t= 0
int Ekran::krzywaBeziera(int p1,int p2, int p3, int p4, double t){
    int wynik = 0;

    double wynikPart1 = (1-t)*(1-t)*(1-t) * p1;
    double wynikPart2 = 3 * (1-t)*(1-t)*t * p2;
    double wynikPart3 = 3 * (1-t)*t*t * p3;
    double wynikPart4 = t*t*t * p4;

    wynik = wynikPart1 + wynikPart2 + wynikPart3 + wynikPart4;

    return wynik;
}


int Ekran::krzywaBspline(int p1,int p2, int p3, int p4, double t){
    int wynik = 0;

    double wynikPart1 = (-t*t*t + 3*t*t -3*t + 1)/(double)6 * p4;
    double wynikPart2 = (3*t*t*t-6*t*t+4)/(double)6 * p3;
    double wynikPart3 = (-3*t*t*t+3*t*t+3*t+1)/(double)6 * p2;
    double wynikPart4 = t*t*t/(double)6 * p1;

    wynik = wynikPart1 + wynikPart2 + wynikPart3 + wynikPart4;

    return wynik;
}

void Ekran::rysujLinie(int x1, int y1, int x2, int y2, QImage* i){
    if(abs(y2-y1) <= abs(x2-x1)){

        if(x2 > x1){
         for(int x = x1;x<x2;x++){
             int y = zwrocY(x, x1, y1, x2, y2);
             drawPixel(x+0.5,y+0.5, chooseRgb,i);
         }
        }else{
            for(int x = x1;x>x2;x--){
                int y = zwrocY(x, x1, y1, x2, y2) ;
                drawPixel(x+0.5,y, chooseRgb,i);
            }
        }
     }else{
        if(y2 > y1){
            for(int y = y1;y<y2;y++){
                int x = zwrocX(y, x1, y1, x2, y2);
                drawPixel(x+0.5,y+0.5, chooseRgb,i);
            }
        }else{
            for(int y = y1;y>y2;y--){
                int x = zwrocX(y, x1, y1, x2, y2);
                drawPixel(x+0.5,y+0.5, chooseRgb,i);
            }
        }

    }
}

void Ekran::rysujLinie(int x1, int y1, int x2, int y2){
    rysujLinie(x1,y1,x2,y2,&im);
}

//zamaluj bierze z zamalujPunkty(taki vector) pukty do obrowbki
//wiec nalezy przed wywolaniem metody wywolac push back zamalujPunkty :)
void Ekran::zamaluj(Rgb color, Rgb background){

    if((color.r == background.r) &&
            (color.g == background.g) &&
            (color.b == background.b)){

        zamalujPunkty.pop_back();
        return;
    }

    while(!zamalujPunkty.empty()){
        Punkt punkt = zamalujPunkty.back();
        zamalujPunkty.pop_back();

        if((getColor(punkt.x,punkt.y).r == background.r) &&
            (getColor(punkt.x,punkt.y).g == background.g) &&
            (getColor(punkt.x,punkt.y).b == background.b)){

            drawPixel(punkt.x, punkt.y, chooseRgb);

            zamalujPunkty.push_back({punkt.x+1,punkt.y});
            zamalujPunkty.push_back({punkt.x-1,punkt.y});
            zamalujPunkty.push_back({punkt.x,punkt.y+1});
            zamalujPunkty.push_back({punkt.x,punkt.y-1});
        }
    }

    update();
}


void Ekran::rysujPoligon(vector<Punkt> ve){
    int minY = (*min_element(ve.begin(), ve.end(),[](Punkt a,Punkt b){return a.y<b.y;})).y;
    int maxY = (*max_element(ve.begin(), ve.end(),[](Punkt a,Punkt b){return a.y<b.y;})).y;

    vector<int> output;

    cout<<minY<<", "<<maxY<<endl;

    for(int y=minY; y<=maxY; y++){

        cout<<"siema"<<endl;
        findX(output, ve, y);

        sort(output.begin(), output.end());

        for(int i=0;i<(int)output.size();i++){
            cout<<"Pozycja nr "<<i<<": "<<output[i]<<endl;
        }

        wypelnij(output, y);
    }
}


void Ekran::wypelnij(vector<int> x, int y){

    for(int i=1; i<x.size();i++){

        if(i%2==0)continue;

        rysujLinie(x[i-1], y, x[i], y);
    }
}

void Ekran::findX(vector<int>& output, vector<Punkt> ve, int y){
    int k=0;

    output.clear();

    for(int i=0; i<(int)ve.size(); i++){
        int y1 = ve[i].y;
        int y2 = ve[(i+1)%ve.size()].y;

        if((y1>=y && y2<y) || (y2>=y && y1<y)){
            int x = findXDeep(ve[i],ve[(i+1)%ve.size()], y);

            output.push_back(x);
        }
    }
}

int Ekran::findXDeep(Punkt p1, Punkt p2, int y){
   int returnValue;
   int returnValuePart1;
   int returnValuePart2;
   int returnValuePart3;

   //if(p1.y == p2.y) return

   returnValuePart1 = p1.x;
   returnValuePart2 = (p2.x - p1.x) * (y-p1.y);
   returnValuePart3 = p2.y-p1.y;

   returnValue = returnValuePart1 + returnValuePart2/(double)returnValuePart3;

   return returnValue;
}
