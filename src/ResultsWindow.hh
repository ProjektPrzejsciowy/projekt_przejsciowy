#ifndef _RESULTS_WINDOW_HH_
#define _RESULTS_WINDOW_HH_

#include <fstream>
#include <iostream>

#include <QDialog>
#include <QListWidget>
#include <QString>
#include <QVector>
#include <QTimer>
#include "qcustomplot.h"

#ifndef Q_MOC_RUN
   #include <gazebo/transport/transport.hh>
#endif

class ResultsWindow : public QDialog
{
   Q_OBJECT

   public:
      ResultsWindow();
      QCustomPlot *plot;
      QCustomPlot *plot2;
      QCustomPlot *plot3;
      QCustomPlot *plot4;
      QCPCurve *Spiral1;
      QCPCurve *Spiral2;
      QCPCurve *Spiral3;
      QListWidget *parametersList;
	QVector<double> x0, y0, w0, t0;
	QVector<double> x1, x2, x3; /**< vector przechowujący współrzędne x trasy */
	QVector<double> y1, y2, y3; /**< vector przechowujący współrzędne y trasy */
	QVector<double> w1, w2, w3; /**< vector przechowujący orientacje */
	QVector<double> t;  /**< vector przechowujący czas */

   private slots:
//	void OnButtonPoseReg1();
	void OnButtonSave1();
	void OnButtonStop();
	
	void realtimeDataSlot();
	
            
   private:
      void Received(ConstPosesStampedPtr &msg);
      void saveRawFile();
      double saveFilter(double value);
      QTimer dataTimer;
      gazebo::transport::NodePtr node;
      gazebo::transport::PublisherPtr publisher;
      
      gazebo::transport::SubscriberPtr subscriberRobot1;
      gazebo::transport::SubscriberPtr subscriberRobot2;
      gazebo::transport::SubscriberPtr subscriberRobot3;

};

#endif
