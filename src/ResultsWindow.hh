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
	void realtimeDataSlot();
	void OnButtonLoad();
	void OnButtonClear();
	void OnButtonAddRobot();
	void OnButtonDeleteRobot();
      
   private:
      QTimer dataTimer;
      gazebo::transport::NodePtr node;
      gazebo::transport::PublisherPtr publisher;
};

#endif
