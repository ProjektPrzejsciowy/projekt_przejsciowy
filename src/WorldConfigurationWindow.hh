#ifndef _WORLD_CONFIGURATION_WINDOW_HH_
#define _WORLD_CONFIGURATION_WINDOW_HH_

#include <QDialog>
#include <QWidget>
#include <QLine>
#include <QRect>
#include <QListWidget>
#include <QString>
#include <QVector>
#include <cstdlib>

#ifndef Q_MOC_RUN
   #include <gazebo/transport/transport.hh>
#endif

class WorldConfigurationWindow : public QDialog
{
   Q_OBJECT

   public:
      WorldConfigurationWindow();
      QListWidget *laboratoryList;
      QListWidget *robotListToAdd;
      QListWidget *addedRobotList;
      QString labName;
      QVector<QString> addedRobots;
      QListWidget *line; 

      QPushButton *pushButtonZatwierdz;
   
   private slots:
      void OnButtonLoad();
      void OnButtonClear();
      void OnButtonAddRobot();
      void OnButtonDeleteRobot();
      void OnPushButtonZatwierdz();
      
   signals:
      void addNewRobot(int id);

   private:
      gazebo::transport::NodePtr node;
      gazebo::transport::PublisherPtr publisher;
};

#endif
