#include <QCursor>
#include <QApplication>
#include <iostream>
#include <QMainWindow>
#include <pthread.h>

void *loop ( void *)
{
    while (true)
    {
        QPoint p=QCursor::pos();
        std::cout << "" << p.x() << ", " << p.y() << std::endl;
    }
    
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

    QMainWindow *window = new QMainWindow();
    window->setWindowTitle(QString::fromUtf8("Joypad"));
    window->resize(600, 600);
    window->setWindowFlags(Qt::WindowStaysOnTopHint);
    window->show();
    
    pthread_t t;
    pthread_create(&t, NULL, loop, NULL);
    

    return app.exec();
}