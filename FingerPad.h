#include <QCursor>
#include <QApplication>
#include <iostream>
#include <sstream>
#include <QMainWindow>
#include <QPushButton>
#include <pthread.h>
#include <QHBoxLayout>
#include <QObject>
#include <QtCore/QCoreApplication>

#define UP 30
#define DOWN 31
#define RIGHT 29
#define LEFT 28

#define FACTOR 6/8.0
#define TITLE 20


namespace Ui {
    class QNew;
}

class QNew : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QNew(QWidget *parent = 0);
    
    public slots:
    void runThis();
};

