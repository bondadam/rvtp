#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createCube(){
    /*RVTexCube *texCube = new RVTexCube();
    texCube->setPosition(QVector3D(ui->x->value(), ui->y->value(), ui->z->value()));
    texCube->setOrientation(ui->roulis->value(), ui->tangage->value(), ui->lacet->value());
    texCube->setTexture(":/textures/container.jpg", false);
    texCube->setScale(2);*/
    RVDice *dice = new RVDice();
    dice->setPosition(QVector3D(ui->x->value(), ui->y->value(), ui->z->value()));
    dice->setOrientation(ui->roulis->value(), ui->tangage->value(), ui->lacet->value());
    dice->setTexture(":/textures/dice_texture.jpg", false);
    dice->setScale(2);
    ui->widgetRV->addBody(dice);

}
