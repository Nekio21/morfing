#include "ekran2.h"

#include <QPainter>
#include <thread>
#include <QMouseEvent>

using namespace std;

Ekran2::Ekran2(QWidget *parent)
    : Ekran(parent)
{
    im = QImage(1200, 1000, QImage::Format_RGB32);
    im.fill(0);
}

void Ekran2::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0,0, width(), height(), Qt::green);
    p.drawImage(0,0, im);
}

//void Ekran2::rysujTrojkat() {

//    for(int i=0;i<3;i++){
//      rysujOkrag(trojkat[0][i].x, trojkat[0][i].y, 3, &im);
//      rysujLinie(trojkat[0][i%3].x, trojkat[0][i%3].y, trojkat[0][(i+1)%3].x, trojkat[0][(i+1)%3].y, &im);
//    }

//    rysujPoligon();
//}


void Ekran2::mousePressEvent(QMouseEvent * e){

}


void Ekran2::mouseMoveEvent(QMouseEvent * e){
 }


//void Ekran2::rysujPoligon(){
//    double minY = min(trojkat[0][0].y, min(trojkat[0][1].y, trojkat[0][2].y));
//    double maxY = max(trojkat[0][0].y, max(trojkat[0][1].y, trojkat[0][2].y));

//    trojkatAbroad[0][0] = {trojkatAbroadA->x, trojkatAbroadA->y};
//    trojkatAbroad[0][1] = {trojkatAbroadB->x, trojkatAbroadB->y};
//    trojkatAbroad[0][2] = {trojkatAbroadC->x, trojkatAbroadC->y};

//    vector<int> output;

//    ve.clear();
//    ve.push_back({trojkat[0][0].x, trojkat[0][0].y});
//    ve.push_back({trojkat[0][1].x, trojkat[0][1].y});
//    ve.push_back({trojkat[0][2].x, trojkat[0][2].y});


//    for(int y=minY; y<=maxY; y++){

//        findX(output, ve, y);

//        sort(output.begin(), output.end());

//        wypelnij(output, y);
//    }




//    update();
//}

void Ekran2::rysujPoligon(Punkt A, Punkt B, Punkt C){
    double minY = min(A.y, min(B.y, C.y));
    double maxY = max(A.y, max(B.y, C.y));

    trojkatNew[0] = A;
    trojkatNew[1] = B;
    trojkatNew[2] = C;

    trojkatAbroad[0][0] = {trojkatAbroadA->x, trojkatAbroadA->y};
    trojkatAbroad[0][1] = {trojkatAbroadB->x, trojkatAbroadB->y};
    trojkatAbroad[0][2] = {trojkatAbroadC->x, trojkatAbroadC->y};

    trojkatAbroad[1][0] = {trojkatAbroadA2->x, trojkatAbroadA2->y};
    trojkatAbroad[1][1] = {trojkatAbroadB2->x, trojkatAbroadB2->y};
    trojkatAbroad[1][2] = {trojkatAbroadC2->x, trojkatAbroadC2->y};


    vector<int> output;

    ve.clear();
    ve.push_back(trojkatNew[0]);
    ve.push_back(trojkatNew[1]);
    ve.push_back(trojkatNew[2]);


    for(int y=(int)minY; y<=(int)maxY; y++){

        findX(output, ve, y);

        sort(output.begin(), output.end());

        wypelnij2(output, y);
    }

    update();
}



//void Ekran2::wypelnij(vector<int> x, int y){

//    double W = (trojkat[0][1].x - trojkat[0][0].x) * (trojkat[0][2].y - trojkat[0][0].y)
//            - (trojkat[0][1].y-trojkat[0][0].y) * (trojkat[0][2].x - trojkat[0][0].x);

//    for(int i=1; i<(int)x.size();i++){

//        if(i%2==0)continue;

//        rysujLinieTrojka(x[i-1], x[i], y, W);
//    }
//}

void Ekran2::wypelnij2(vector<int> x, int y){

    double W = (trojkatNew[1].x - trojkatNew[0].x) * (trojkatNew[2].y - trojkatNew[0].y)
            - (trojkatNew[1].y-trojkatNew[0].y) * (trojkatNew[2].x - trojkatNew[0].x);


    for(int i=1; i<(int)x.size();i++){

        if(i%2==0)continue;

        rysujLinieTrojka2(x[i-1], x[i], y, W);
    }
}

void Ekran2::rysujLinieTrojka2(int x1, int x2, int y, double W){
    double Wv;
    double Ww;

    double v;
    double w;
    double u;

    for(int i=x1;i<=x2;i++){

     Wv = (i - trojkatNew[0].x) * (trojkatNew[2].y - trojkatNew[0].y)
            - (y - trojkatNew[0].y) * (trojkatNew[2].x - trojkatNew[0].x);

     Ww = (trojkatNew[1].x - trojkatNew[0].x) * (y - trojkatNew[0].y)
            - (trojkatNew[1].y - trojkatNew[0].y) * (i - trojkatNew[0].x);

     v = Wv/W;
     w = Ww/W;
     u = 1-v-w;

     Punkt2 punktAbroad1, punktAbroad2;
     punktAbroad1.x = u * trojkatAbroad[0][0].x + v * trojkatAbroad[0][1].x + w * trojkatAbroad[0][2].x;
     punktAbroad1.y = u * trojkatAbroad[0][0].y + v * trojkatAbroad[0][1].y + w * trojkatAbroad[0][2].y;

     punktAbroad1.x = fmod((abs(punktAbroad1.x - korektaX)),(imAbroad->width()));
     punktAbroad1.y = fmod((abs(punktAbroad1.y - korektaY)),(imAbroad->height()));

    double a = punktAbroad1.x - floor(punktAbroad1.x);
    double b = punktAbroad1.y - floor(punktAbroad1.y);

    Rgb rgbP1, rgbP2, rgbP3, rgbP4, rgb;

     Punkt P4 = {(int)floor(punktAbroad1.x), (int)floor(punktAbroad1.y)};
     Punkt P3 = {(int)floor(punktAbroad1.x)+1, (int)floor(punktAbroad1.y)};
     Punkt P2 = {(int)floor(punktAbroad1.x)+1, (int)floor(punktAbroad1.y)+1};
     Punkt P1 = {(int)floor(punktAbroad1.x), (int)floor(punktAbroad1.y)+1};

     rgbP1 = getColor(P1.x, P1.y, imAbroad);
     rgbP2 = getColor(P2.x, P2.y, imAbroad);
     rgbP3 = getColor(P3.x, P3.y, imAbroad);
     rgbP4 = getColor(P4.x, P4.y, imAbroad);

     double newR = b * ((1-a)*rgbP1.r+a*rgbP2.r) + (1-b)*((1-a)*rgbP4.r+a*rgbP3.r);
     double newG = b * ((1-a)*rgbP1.g+a*rgbP2.g) + (1-b)*((1-a)*rgbP4.g+a*rgbP3.g);
     double newB = b * ((1-a)*rgbP1.b+a*rgbP2.b) + (1-b)*((1-a)*rgbP4.b+a*rgbP3.b);

     rgb = {(int)newR, (int)newG, (int)newB};


     //2

     punktAbroad2.x = u * trojkatAbroad[1][0].x + v * trojkatAbroad[1][1].x + w * trojkatAbroad[1][2].x;
     punktAbroad2.y = u * trojkatAbroad[1][0].y + v * trojkatAbroad[1][1].y + w * trojkatAbroad[1][2].y;

     punktAbroad2.x = fmod((abs(punktAbroad2.x - korektaX2)),(imAbroad2->width()));
     punktAbroad2.y = fmod((abs(punktAbroad2.y - korektaY2)),(imAbroad2->height()));


    double a2 = punktAbroad2.x - floor(punktAbroad2.x);
    double b2 = punktAbroad2.y - floor(punktAbroad2.y);

    Rgb rgbP12, rgbP22, rgbP32, rgbP42, rgb2;

     Punkt P42 = {(int)floor(punktAbroad2.x), (int)floor(punktAbroad2.y)};
     Punkt P32 = {(int)floor(punktAbroad2.x)+1, (int)floor(punktAbroad2.y)};
     Punkt P22 = {(int)floor(punktAbroad2.x)+1, (int)floor(punktAbroad2.y)+1};
     Punkt P12 = {(int)floor(punktAbroad2.x), (int)floor(punktAbroad2.y)+1};

     rgbP12 = getColor(P12.x, P12.y, imAbroad2);
     rgbP22 = getColor(P22.x, P22.y, imAbroad2);
     rgbP32 = getColor(P32.x, P32.y, imAbroad2);
     rgbP42 = getColor(P42.x, P42.y, imAbroad2);

     double newR2 = b2 * ((1-a2)*rgbP12.r+a2*rgbP22.r) + (1-b2)*((1-a2)*rgbP42.r+a2*rgbP32.r);
     double newG2 = b2 * ((1-a2)*rgbP12.g+a2*rgbP22.g) + (1-b2)*((1-a2)*rgbP42.g+a2*rgbP32.g);
     double newB2 = b2 * ((1-a2)*rgbP12.b+a2*rgbP22.b) + (1-b2)*((1-a2)*rgbP42.b+a2*rgbP32.b);

     rgb2 = {(int)newR2, (int)newG2, (int)newB2};

     Rgb rgb3;

     rgb3.r = (1-(value/(double)100)) * rgb.r + (value/(double)100) * rgb2.r;
     rgb3.g = (1-(value/(double)100)) * rgb.g + (value/(double)100) * rgb2.g;
     rgb3.b = (1-(value/(double)100)) * rgb.b + (value/(double)100) * rgb2.b;

     drawPixel(i,y, rgb3);
    }
}


//void Ekran2::rysujLinieTrojka(int x1, int x2, int y, double W){
//    double Wv;
//    double Ww;

//    double v;
//    double w;
//    double u;

//    for(int i=x1;i<=x2;i++){

//     Wv = (i - trojkat[0][0].x) * (trojkat[0][2].y - trojkat[0][0].y)
//            - (y - trojkat[0][0].y) * (trojkat[0][2].x - trojkat[0][0].x);

//     Ww = (trojkat[0][1].x - trojkat[0][0].x) * (y - trojkat[0][0].y)
//            - (trojkat[0][1].y - trojkat[0][0].y) * (i - trojkat[0][0].x);

//     v = Wv/W;
//     w = Ww/W;
//     u = 1-v-w;

//     Punkt punktAbroad;
//     punktAbroad.x = u * trojkatAbroad[0][0].x + v * trojkatAbroad[0][1].x + w * trojkatAbroad[0][2].x;
//     punktAbroad.y = u * trojkatAbroad[0][0].y + v * trojkatAbroad[0][1].y + w * trojkatAbroad[0][2].y;

//     punktAbroad.x = fmod((abs(punktAbroad.x - korektaX)),(imAbroad->width()));
//     punktAbroad.y = fmod((abs(punktAbroad.y - korektaY)),(imAbroad->height()));

//     Rgb pixel = getColor(punktAbroad.x, punktAbroad.y, imAbroad);


//    double a = punktAbroad.x - floor(punktAbroad.x);
//    double b = punktAbroad.y - floor(punktAbroad.y);

//    Rgb rgbP1, rgbP2, rgbP3, rgbP4, rgb;

//     Punkt P4 = {(double)floor(punktAbroad.x), (double)floor(punktAbroad.y)};
//     Punkt P3 = {(double)floor(punktAbroad.x)+1, (double)floor(punktAbroad.y)};
//     Punkt P2 = {(double)floor(punktAbroad.x)+1, (double)floor(punktAbroad.y)+1};
//     Punkt P1 = {(double)floor(punktAbroad.x), (double)floor(punktAbroad.y)+1};

//     rgbP1 = getColor(P1.x, P1.y, imAbroad);
//     rgbP2 = getColor(P2.x, P2.y, imAbroad);
//     rgbP3 = getColor(P3.x, P3.y, imAbroad);
//     rgbP4 = getColor(P4.x, P4.y, imAbroad);

//     double newR = b * ((1-a)*rgbP1.r+a*rgbP2.r) + (1-b)*((1-a)*rgbP4.r+a*rgbP3.r);
//     double newG = b * ((1-a)*rgbP1.g+a*rgbP2.g) + (1-b)*((1-a)*rgbP4.g+a*rgbP3.g);
//     double newB = b * ((1-a)*rgbP1.b+a*rgbP2.b) + (1-b)*((1-a)*rgbP4.b+a*rgbP3.b);

//     rgb = {(int)newR, (int)newG, (int)newB};



//     drawPixel(i,y, rgb);
//    }
//}


void Ekran2::posredniTrojkat(){
    Punkt ANew = {
        (int)((1-(value/(double)100))*trojkatAbroadA->x + ((value/(double)100)*trojkatAbroadA2->x)),
        (int)((1-(value/(double)100))*trojkatAbroadA->y + ((value/(double)100)*trojkatAbroadA2->y))
    };
    Punkt BNew = {
        (int)((1-(value/(double)100))*trojkatAbroadB->x + ((value/(double)100)*trojkatAbroadB2->x)),
        (int)((1-(value/(double)100))*trojkatAbroadB->y + ((value/(double)100)*trojkatAbroadB2->y))
    };
    Punkt CNew = {
        (int)((1-(value/(double)100))*trojkatAbroadC->x + ((value/(double)100)*trojkatAbroadC2->x)),
        (int)((1-(value/(double)100))*trojkatAbroadC->y + ((value/(double)100)*trojkatAbroadC2->y))
    };

    im.fill(0);

    rysujPoligon(ANew, BNew, CNew);
}

