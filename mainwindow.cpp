#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCamera>
#include <QComboBox>
#include <QCameraInfo>
Q_DECLARE_METATYPE(QCameraInfo)
SharedViewfinder* sharedViewfinder = new SharedViewfinder();
QCamera *camera= new QCamera(QCameraInfo::defaultCamera());
int MainWindow::tryb = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnOpenWindow, &QPushButton::clicked, this, &MainWindow::openSecondaryWindow);
    QComboBox *comboBoxCameraFeed = new QComboBox();
    QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    if (!availableCameras.isEmpty()) {
            QCameraInfo defaultCamera = availableCameras.first();
            camera->setViewfinder(sharedViewfinder);
            camera->start();
        }
    foreach(const QCameraInfo &cameraInfo , availableCameras) {
            comboBoxCameraFeed->addItem(cameraInfo.description(), QVariant::fromValue(cameraInfo));
        }
    tryb = ui->tabWidget->currentIndex();
    ui->toolBar->addWidget(comboBoxCameraFeed);
     connect(comboBoxCameraFeed, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::changeCamera);
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
void MainWindow::changeCamera(int index) {
    QComboBox *comboBox = qobject_cast<QComboBox*>(sender());
    if (comboBox) {
        QCameraInfo cameraInfo = comboBox->itemData(index).value<QCameraInfo>();
        camera->stop();
        camera = new QCamera(cameraInfo);
        camera->setViewfinder(sharedViewfinder);
        camera->start();
    }
}
