#ifndef SECONDARYWINDOW_H
#define SECONDARYWINDOW_H

#include <QMainWindow>
#include "sharedviewfinder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SecondaryWindow; }
QT_END_NAMESPACE

class SecondaryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondaryWindow(SharedViewfinder *viewfinder, QWidget *parent = nullptr);
    ~SecondaryWindow();
    static int instanceCount;
public slots:
    void frameReady(QPixmap pixmap);
    void scatter();

private:
    Ui::SecondaryWindow *ui;
    SharedViewfinder *m_viewfinder;
    int numerek;
    int poz_x;
    int poz_y;
    int ile_x;
    int ile_y;

};

#endif
