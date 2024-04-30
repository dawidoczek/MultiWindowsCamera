#include "secondarywindow.h"
#include "ui_secondarywindow.h"
#include <QDebug>
#include <mainwindow.h>
#include <QGuiApplication>
#include <QScreen>
int i =1;

int SecondaryWindow::instanceCount = 0;
SecondaryWindow::SecondaryWindow(SharedViewfinder *viewfinder, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SecondaryWindow)
    , m_viewfinder(viewfinder)
{
    ui->setupUi(this);
        numerek = instanceCount;
        instanceCount++;
        qDebug()<<"Instancja "<<instanceCount;
        int screenWidth = QGuiApplication::primaryScreen()->geometry().width();
        int screenHeight = QGuiApplication::primaryScreen()->geometry().height();

        int randX = qrand() % (screenWidth - 320); // Subtract 640 to avoid placing the window out of bounds
        int randY = qrand() % (screenHeight - 320); // Subtract 480 to avoid placing the window out of bounds
        move(randX,randY);
        poz_x=randX;
        poz_y=randY;
        ile_x=5;
        ile_y=5;
}

SecondaryWindow::~SecondaryWindow()
{
    delete ui;
}

void SecondaryWindow::frameReady(QPixmap pixmap)
{
    // Dzieli ci na małe kawałki
    QPixmap leftCornerPixmap = pixmap.copy();
    if(MainWindow::tryb==0){
//    qDebug()<<"Klatka: "<<i<<"Rozmiar: "<<pixmap.size();
    i++;

    if(numerek==0){
        leftCornerPixmap = pixmap.copy(0,0,640,720);
    }else{
        leftCornerPixmap = pixmap.copy(640,0,1280,720);
    }
    leftCornerPixmap = pixmap.copy(numerek*(1280/instanceCount),0,1280/instanceCount,720);
//    qDebug()<<"Kordy x1: "<<numerek*(1280/instanceCount)<<"x2: "<<1280/instanceCount;

    ui->label->setPixmap(leftCornerPixmap);
    ui->label->setFixedSize(1280/instanceCount, 720);
    resize(1280/instanceCount, 720);
    move(numerek*1280/instanceCount,0);
    ui->label->update();
}if(MainWindow::tryb==1){

        QPoint currentPosition = pos();
        int x = currentPosition.x();
        int y = currentPosition.y();
        x /= 1.5;
        y *=3;
        leftCornerPixmap = pixmap.copy(x,y/4,320,320);
        resize(320, 320);
        ui->label->setPixmap(leftCornerPixmap);
        ui->label->setFixedSize(320, 320);
        ui->label->update();

    }
    if(MainWindow::tryb==2){

        poz_x+=ile_x;
        poz_y+=ile_y;
        if(poz_x>1480){
            ile_x=-1*qAbs(ile_x);
        }
        if(poz_x<0){
            ile_x=qAbs(ile_x);
        }
        if(poz_y>1280-400){
            ile_y=-1*qAbs(ile_y);
        }
        if(poz_y<0 ){
            ile_y=qAbs(ile_y);
        }
//        qDebug()<<"x: "<<poz_x<<" y: "<<poz_y;




        move(poz_x,poz_y);
        leftCornerPixmap = pixmap.copy((poz_x/1.5),poz_y/2,320,320);
            resize(320, 320);
            ui->label->setPixmap(leftCornerPixmap);
            ui->label->setFixedSize(320, 320);
            ui->label->update();

        }
}


void SecondaryWindow::scatter()
{
    int screenWidth = QGuiApplication::primaryScreen()->geometry().width();
    int screenHeight = QGuiApplication::primaryScreen()->geometry().height();

    int randX = qrand() % (screenWidth - 320); // Subtract 640 to avoid placing the window out of bounds
    int randY = qrand() % (screenHeight - 320); // Subtract 480 to avoid placing the window out of bounds
    move(randX,randY);
}
