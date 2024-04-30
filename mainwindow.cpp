#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCamera>
#include <QCameraInfo>
SharedViewfinder* sharedViewfinder = new SharedViewfinder();
QCamera *camera= new QCamera(QCameraInfo::defaultCamera());
int MainWindow::tryb = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnOpenWindow, &QPushButton::clicked, this, &MainWindow::openSecondaryWindow);

    camera->setViewfinder(sharedViewfinder);
    camera->start();
    qDebug()<<camera->ActiveState;
    tryb = ui->tabWidget->currentIndex();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSecondaryWindow()
{
    start();
}
void MainWindow::start(){
    SecondaryWindow *abc = new SecondaryWindow(sharedViewfinder);
    connect(sharedViewfinder, &SharedViewfinder::frameReady, abc, &SecondaryWindow::frameReady);
    connect(this, &MainWindow::scatter, abc, &SecondaryWindow::scatter);
    abc->show();
}

bool flipflop = false;
void MainWindow::on_pushButton_Stop_clicked()
{
    flip();
}

void MainWindow::flip(){
    if(!flipflop){
    camera->stop();
    }else{
        camera->start();
    }
    flipflop=!flipflop;
}
void MainWindow::on_tabWidget_currentChanged(int index)
{
    tryb = index;
}


void MainWindow::on_btnOpenWindow_2_clicked()
{
    start();
}


void MainWindow::on_pushButton_Stop_2_clicked()
{
    flip();
}


void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"ping";
    emit scatter();
}


void MainWindow::on_btnOpenWindow_3_clicked()
{
    start();
}

