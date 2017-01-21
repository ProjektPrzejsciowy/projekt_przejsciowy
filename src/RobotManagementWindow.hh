#ifndef _ROBOT_MANAGEMENT_WINDOW_HH_
#define _ROBOT_MANAGEMENT_WINDOW_HH_

#include "RobotManagementTab.hh"

#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>

#include <QDialog>
#include <QListWidget>
#include <QString>
#include <QVector>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QMetaObject>
#include <QDesktopWidget>

#ifndef Q_MOC_RUN
#include <gazebo/transport/transport.hh>
#include "gazebo/msgs/msgs.hh"
#endif

using namespace gazebo;

class RobotManagementWindow : public QDialog {
    Q_OBJECT

public:
    RobotManagementWindow();
    //~RobotManagementWindow(); // Nie moze byc destruktora, inaczej nie dziala!
    void addNewTab(std::string tab_name);
    void OnPoseMsg(ConstPosesStampedPtr &msg);
    double pioneer_1_X;
    double pioneer_1_Y;
    double pioneer_1_YAW;
    double pioneer_2_X;
    double pioneer_2_Y;
    double pioneer_2_YAW;
    double pioneer_3_X;
    double pioneer_3_Y;
    double pioneer_3_YAW;

private:
    QTabWidget *tabWidgetRobots;
    std::vector < QWidget * > tabRobots;
    QWidget *tabRobot;
    transport::NodePtr node;
    transport::SubscriberPtr sub;

public slots:
    void onAddNewRobot(int id);
    void onHideARobot(int id);
    void tabSelected(int value);

public:
    int robots_counter;

private:
    
};

#endif
