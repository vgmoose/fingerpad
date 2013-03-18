#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QCursor>


class myLabel: public QLabel
{
    
public:
	myLabel()
	{
        this->setAlignment(Qt::AlignCenter);
        
        //Default Label Value
        this->setText("No Value");
        
        //set MouseTracking true to capture mouse event even its key is not pressed
        this->setMouseTracking(true);
	};
	~ myLabel(){};
	
    void mousePressEvent (QMouseEvent * event)
    {
        this ->setText("pressed");
    }
    
    void mouseReleaseEvent (QMouseEvent * event)
    {
        this ->setText("released");

    }
    
	void mouseMoveEvent ( QMouseEvent * event )
	{
        //Show x and y coordinate values of mouse cursor here
//        this->setText("X:"+QString::number(event->x())+", Y:"+QString::number(event->y()));
         QPoint p=QCursor::pos();
        this->setText(""+QString::number(p.x())+", "+QString::number(p.y()));
	};
    
};

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
    
	QMainWindow *window = new QMainWindow();
    
    window->setWindowTitle(QString::fromUtf8("QT - Capture Mouse Move"));
    window->resize(600, 600);
    window->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SplashScreen);
	
    QWidget *centralWidget = new QWidget(window);
	QHBoxLayout* layout = new QHBoxLayout(centralWidget);
	
    myLabel* CoordinateLabel = new myLabel();
    QLabel* MouseDownLabel = new QLabel();
	layout->addWidget(CoordinateLabel);
    layout->addWidget(MouseDownLabel);
	
	window->setCentralWidget(centralWidget);
	
	window->show();
	return app.exec();
}