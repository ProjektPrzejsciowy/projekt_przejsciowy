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
#endif

class RobotManagementWindow : public QDialog {
    Q_OBJECT

public:
    RobotManagementWindow();
    //~RobotManagementWindow(); // Nie moze byc destruktora, inaczej nie dziala!
    void addNewTab(std::string tab_name);

private:
    QTabWidget *tabWidgetRobots;
    std::vector < QWidget * > tabRobots;
    QWidget *tabRobot;    

public slots:
    void onAddNewRobot(int id);
    void onHideARobot(int id);

public:
    int robots_counter;

private:
    
};

#endif
