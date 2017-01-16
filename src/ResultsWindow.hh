#ifndef _RESULTS_WINDOW_HH_
#define _RESULTS_WINDOW_HH_

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
      QListWidget *parametersList;


   private slots:
	void OnButtonPoseReg1();
	void OnButtonSave1();
	
            
   private:
      void Received(const boost::shared_ptr<const gazebo::msgs::Quaternion> &msg);
      QTimer dataTimer;
      gazebo::transport::NodePtr node;
      gazebo::transport::PublisherPtr publisher;
      
      gazebo::transport::SubscriberPtr subscriber;
};

#endif
