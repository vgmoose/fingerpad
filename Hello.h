
class MainWindow : public QWidget
{
  Q_OBJECT
      
      signals:
          // define mouseClick signal
	      void mouseClickEvent();
	          
		  public:
		      MainWindow(){};
		          
			  protected:
			      // re-implement processing of mouse events
			          void mouseReleaseEvent ( QMouseEvent * e );
				      void mousePressEvent ( QMouseEvent * e );

				      private:
				          // member variable to store click position
					      QPoint m_lastPoint;
					          // member variable - flag of click beginning
						      bool m_mouseClick;
						          
							  };

