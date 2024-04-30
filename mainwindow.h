#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sharedviewfinder.h"
#include "secondarywindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static int tryb;
signals:
    void scatter();
private slots:
    void openSecondaryWindow();

    void on_pushButton_Stop_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_btnOpenWindow_2_clicked();

    void on_pushButton_Stop_2_clicked();

    void on_pushButton_clicked();

    void on_btnOpenWindow_3_clicked();

private:
    void start();
    void flip();

    Ui::MainWindow *ui;
    SharedViewfinder viewfinder;

};

#endif
