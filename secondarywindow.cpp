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

        int randX = qrand() % (screenWidth - 320);
        int randY = qrand() % (screenHeight - 320);
        move(randX,randY);
        poz_x=randX;
        poz_y=randY;
        ile_x=qrand() % (10)+5;
        ile_y=qrand() % (10)+5;
        qDebug()<<ile_x<<" "<<ile_y;
}

SecondaryWindow::~SecondaryWindow()
{
    delete ui;
}

void SecondaryWindow::frameReady(QPixmap pixmap)
{
    // Dzieli ci na małe kawałki
    QPixmap leftCornerPixmap = pixmap.copy();
    QSize rozmiar = pixmap.size();
    float screenWidth = QGuiApplication::primaryScreen()->geometry().width();
    float screenHeight = QGuiApplication::primaryScreen()->geometry().height();
    if(MainWindow::tryb==0){
    qDebug()<<"Klatka: "<<i<<"Rozmiar: "<<rozmiar.width()<<' '<<rozmiar.height();
    i++;
    leftCornerPixmap = pixmap.copy(numerek*(rozmiar.width()/instanceCount),0,rozmiar.width()/instanceCount,rozmiar.height());
//    qDebug()<<"Kordy x1: "<<numerek*(1280/instanceCount)<<"x2: "<<1280/instanceCount;

    ui->label->setPixmap(leftCornerPixmap);
    ui->label->setFixedSize(rozmiar.width()/instanceCount, rozmiar.height());
    resize(rozmiar.width()/instanceCount, rozmiar.height());
    move(numerek*rozmiar.width()/instanceCount,0);
    ui->label->update();
}if(MainWindow::tryb==1){

        QPoint currentPosition = pos();
        float x = currentPosition.x();
        float y = currentPosition.y();


//        qDebug()<<screenHeight/rozmiar.height()<<' '<<screenWidth/rozmiar.width();
        y /= screenHeight/rozmiar.height();
        x /= screenWidth/rozmiar.width();
        leftCornerPixmap = pixmap.copy(x,y,this->size().width(),this->size().height());
//        resize(320, 320);
        ui->label->setPixmap(leftCornerPixmap);
        ui->label->setFixedSize(this->size().width()-25,this->size().height()-25);
//        ui->label->resize(this->size().width(),this->size().height());
//        ui->label->adjustSize();
        ui->label->update();

    }
    if(MainWindow::tryb==2){

        poz_x+=ile_x;
        poz_y+=ile_y;
        if(poz_x>screenWidth-320){
            ile_x=-1*qAbs(ile_x);
        }
        if(poz_x<0){
            ile_x=qAbs(ile_x);
        }
        if(poz_y>screenHeight-320){
            ile_y=-1*qAbs(ile_y);
        }
        if(poz_y<0 ){
            ile_y=qAbs(ile_y);
        }
//        qDebug()<<"x: "<<poz_x<<" y: "<<poz_y;




        move(poz_x,poz_y);
        leftCornerPixmap = pixmap.copy((poz_x/(screenWidth/rozmiar.width())),poz_y/(screenHeight/rozmiar.height()),320,320);
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

    int randX = qrand() % (screenWidth - 320);
    int randY = qrand() % (screenHeight - 320);
    move(randX,randY);
}
