#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QColorDialog>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget_2->imAbroad = &ui->widget->imKelner;
    ui->widget_2->imAbroad2 = &ui->widget->imKelner2;

    ui->widget_2->korektaX = ui->widget->width()/2 - ui->widget->imKelner.width()/2;
    ui->widget_2->korektaY = ui->widget->height()/2 - ui->widget->imKelner.height()/2;

    ui->widget_2->korektaX2 = ui->widget->width()/2 - ui->widget->imKelner2.width()/2;
    ui->widget_2->korektaY2 = ui->widget->height()/2 - ui->widget->imKelner2.height()/2;

    ui->widget_2->trojkatAbroadA = &ui->widget->trojkat[0][0];
    ui->widget_2->trojkatAbroadB = &ui->widget->trojkat[0][1];
    ui->widget_2->trojkatAbroadC = &ui->widget->trojkat[0][2];

    ui->widget_2->trojkatAbroadA2 = &ui->widget->trojkat[1][0];
    ui->widget_2->trojkatAbroadB2 = &ui->widget->trojkat[1][1];
    ui->widget_2->trojkatAbroadC2 = &ui->widget->trojkat[1][2];
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    if(value == 0){
        ui->widget->first = true;
    }else{
        ui->widget->first = false;
    }

    ui->widget->drawMousePressEvent();
    ui->widget->update();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->widget_2->value = value;
    ui->widget_2->posredniTrojkat();
}

