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
#include "FingerPad.h"
#include <QShortcut>

#ifdef _WIN32
// not sure how to do this on windows
#elif __APPLE__
#define MOVE(a) \
ss << "osascript -e \"tell application \\\"System Events\\\" to key "; \
if (a<5){ ss <<"up"; justmoved[a-1] = false; a+=27; } else {ss << "down"; justmoved[a-28] = true;} \
ss << " (ASCII character " << a << ")\""; 
#elif __linux
#define MOVE(a) \
ss << "xdotool key"; \
 \
switch (keycode) \
{ \
    case UP: ss << "down Up"; break; \
    case DOWN: ss << "down Down"; break; \
    case LEFT: ss << "down Left"; break; \
    case RIGHT: ss <<"down Right"; break; \
    case 4: ss <<"up Down"; break; \
    case 3: ss <<"up Up"; break; \
    case 2: ss <<"up Right"; break;\
    case 1: ss << "up Left"; break; \
    default: \
        system("xdotool keyup Up;xdotool keyup Left;xdotool keyup Right;xdotool keyup Down"); \
        return; \
}
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

QMainWindow* ptr;  // pointer to the window
QPushButton* btnptr;  // pointer to the button
bool listen;  // true when "enable fingerpad" is true
bool justmoved[4] = {true, true, true, true}; // true just after moving

void QNew::runThis()
{
//    std::cout << "hihihi" << std::endl;
    if (!listen)
    {
        btnptr->setText("Disable\nFingerpad");
        ptr->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
        ptr->show();
    }
    else
    {
        btnptr->setText("Enable\nFingerpad");
        ptr->setWindowFlags(Qt::Dialog);
        ptr->show();
    }
    
    listen = !listen;
}


void move(int keycode)
{
    std::stringstream ss;
   
//
//    ss << "osascript -e \"tell application \\\"System Events\\\" to keystroke (ASCII character " << keycode << ")\"";
//    ss << keycode;
    
    if ( keycode>5 || justmoved[keycode-1])
    {
    MOVE(keycode);
    
    system(ss.str().c_str());
    }
//    btnptr->setText(ss.str().c_str());
    
}


void *loop ( void *)
{
    while (true)
    {
        
        if (listen)
        {
//            std::cout << "listening...." << std::endl;
            QPoint p=QCursor::pos();
            //        cout << "" << ptr->x() << ", " << ptr->y() << endl;
            //        cout <<  (ptr->y()+ptr->height());
            //        cout << " " << (2/3)*(ptr->y()+ptr->height());
            //        cout << " " << p.y() << endl;
            
            int top_outer = ptr->y() + TITLE;
            int top_inner = top_outer + (1-FACTOR) * ptr->height();
            
            int bot_outer = top_outer + ptr->height();
            int bot_inner = top_outer + (FACTOR) * ptr->height();
            
            int left_outer = ptr->x();
            int left_inner = left_outer + (1-FACTOR) * ptr->width();
            
            int righ_outer = left_outer + ptr->width();
            int righ_inner = left_outer + (FACTOR) * ptr->width();
            

            
            move(1);
            
            //left
            if (p.x() > left_outer && p.x() < left_inner && p.y() < ptr->y()+ptr->height() && p.y() > ptr->y())
                move(LEFT);
            
            move(2);
            
            //right
            if (p.x() < righ_outer && p.x() > righ_inner && p.y() < ptr->y()+ptr->height() && p.y() > ptr->y())
                move(RIGHT);
            
            move(3);

            //up
            if (p.y() > top_outer && p.y() < top_inner && p.x() < ptr->x()+ptr->width() && p.x() > ptr->x())
                move(UP);
            
            move(4);

            //down
            if (p.y() < bot_outer && p.y() > bot_inner && p.x() < ptr->x()+ptr->width() && p.x() > ptr->x())
                move(DOWN);
            
 
            
            
            //         if (p.y() > ptr->y() && p.y() < (4/3)*(ptr->y()))
            //            cout << "Move up" << endl;
            //        else if (p.x() < 200)
            //            cout << "Move left" << endl;
            //        else if (p.x() > 1080)
            //            cout << "Move right" << endl;
            
            //        cout << ptr->height() << " " << ptr->width() << endl;
            
        }
        else
        {
            std::cout << "";
//            move(0);
        }

        
        //
    }
    
}

QNew::QNew(QWidget *parent)
: QMainWindow(parent)
{
    // Connect button signal to appropriate slot
}



int main(int argc, char **argv)
{
	QApplication app(argc, argv);
    QHBoxLayout *layout = new QHBoxLayout;
    QNew w;
    
    
    QMainWindow *window = new QMainWindow();
    QWidget * center = new QWidget(window);
    ptr = window;
    
    new QShortcut(QKeySequence(" "), window, SLOT(showMinimized()));
    new QShortcut(QKeySequence("Ctrl+M"), window, SLOT(showMinimized()));

    
    window->setWindowTitle(QString::fromUtf8("Fingerpad"));
    window->resize(400, 400);
//    window->setWindowFlags(Qt::WindowStaysOnTopHint);
    
    QPushButton button("Enable\nFingerpad");
    btnptr = &button;
    button.setFixedSize(100,100);
    layout->addWidget(btnptr);
    button.show();
    
    QObject::connect(btnptr,SIGNAL(clicked()), &w, SLOT(runThis()));

//    QObject::connect(btnptr, SIGNAL(clicked()), &w, SLOT(runThis()));
    
    center->setLayout(layout);
    window->setCentralWidget(center);
    window->show();
    
    
    listen = false;
    pthread_t t;
    pthread_create(&t, NULL, loop, NULL);
    
    
    return app.exec();
}