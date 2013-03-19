#include <QCursor>
#include <QApplication>
#include <iostream>
#include <sstream>
#include <QMainWindow>
#include <QPushButton>
#include <pthread.h>
#include <QHBoxLayout>

#define UP 30
#define DOWN 31
#define RIGHT 29
#define LEFT 28

#define FACTOR 6/8.0
#define TITLE 20

using namespace std;

QMainWindow* ptr;
QPushButton* btnptr;
bool listen;


void move(int keycode)
{
    stringstream ss;
    
    ss << "osascript -e \"tell application \\\"System Events\\\" to keystroke (ASCII character " << keycode << ")\"";
    
    // os x
    system(ss.str().c_str());
}


void *loop ( void *)
{
    while (true)
    {
        
        if (listen)
        {
        QPoint p=QCursor::pos();
//        cout << "" << ptr->x() << ", " << ptr->y() << endl;
//        cout <<  (ptr->y()+ptr->height());
//        cout << " " << (2/3)*(ptr->y()+ptr->height());
//        cout << " " << p.y() << endl;
        
        //down
        if (p.y() < (ptr->y()+ptr->height()+TITLE) && p.y() > FACTOR*(ptr->y()+ptr->height()+TITLE) && p.x() < ptr->x()+ptr->width() && p.x() > ptr->x())
                move(DOWN);
        
        //up
        if (p.y() > ptr->y()+TITLE && p.y() < (2-FACTOR)*(ptr->y()+TITLE) && p.x() < ptr->x()+ptr->width() && p.x() > ptr->x())
            move(UP);
        
        //right
        if (p.x() < (ptr->x()+ptr->width()+TITLE) && p.x() > FACTOR*(ptr->x()+ptr->width()+TITLE) && p.y() < ptr->y()+ptr->height() && p.y() > ptr->y())
            move(RIGHT);
        
        //left
        if (p.x() > ptr->x()+TITLE && p.x() < (2-FACTOR)*(ptr->x()+TITLE) && p.y() < ptr->y()+ptr->height() && p.y() > ptr->y())
            move(LEFT);
        
        
//         if (p.y() > ptr->y() && p.y() < (4/3)*(ptr->y()))
//            cout << "Move up" << endl;
//        else if (p.x() < 200)
//            cout << "Move left" << endl;
//        else if (p.x() > 1080)
//            cout << "Move right" << endl;
        
//        cout << ptr->height() << " " << ptr->width() << endl;
        
        }
        
            //
    }
    
}


int main(int argc, char **argv)
{
	QApplication app(argc, argv);
    QHBoxLayout *layout = new QHBoxLayout;


    QMainWindow *window = new QMainWindow();
    QWidget * center = new QWidget(window);
    ptr = window;

    window->setWindowTitle(QString::fromUtf8("Fingerpad"));
    window->resize(400, 400);
    window->setWindowFlags(Qt::WindowStaysOnTopHint);
    
    QPushButton button("Enable Fingerpad");
    btnptr = &button;
    layout->addWidget(btnptr);
    button.show();
    
    center->setLayout(layout);
    window->setCentralWidget(center);
    window->show();

    
    listen = false;
    pthread_t t;
    pthread_create(&t, NULL, loop, NULL);
    

    return app.exec();
}