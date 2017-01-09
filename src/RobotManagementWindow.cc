#include "RobotManagementWindow.hh"

using namespace std;

RobotManagementWindow::RobotManagementWindow() : 
    QDialog(), 
    robots_counter(0) {

    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    // Glowne okienko
    tabWidgetRobots = new QTabWidget ( this ); 
    tabWidgetRobots->setObjectName ( "tabWidgetRobots" );
    tabWidgetRobots->setGeometry ( QRect( QPoint(0, 0), QSize(300, 150)) );
    tabWidgetRobots->setTabShape ( QTabWidget::Triangular );
    
    // Dodaj zakladki
    addNewTab( "pioneer_1" );
    tabWidgetRobots->setTabEnabled(0, false);
    addNewTab( "pioneer_2" );
    tabWidgetRobots->setTabEnabled(1, false);
    addNewTab( "pioneer_3" );
    tabWidgetRobots->setTabEnabled(2, false);
    
    // Ustaw rozmiar
    //this->adjustSize();
    int width = 300;
    int height = 150;
    this->setGeometry(QRect( QPoint(0, 0), QSize(width, height)) );
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width*0.5, center.y()-height*0.5);

    this->setFixedSize(this->size());
    
    // Sloty
    QMetaObject::connectSlotsByName ( this );
}

void RobotManagementWindow::addNewTab(string tab_name) {
    tabRobot = new RobotManagementTab(tab_name);
    tabRobots.push_back ( tabRobot );
    tabWidgetRobots->addTab ( tabRobot, QString() );
    tabWidgetRobots->setTabText ( tabWidgetRobots->indexOf ( tabRobot ), tab_name.c_str() );
    tabWidgetRobots->setCurrentIndex ( tabWidgetRobots->count()-1);
}

void RobotManagementWindow::onAddNewRobot(int id) {
    tabWidgetRobots->setTabEnabled(id-1, true);
}

void RobotManagementWindow::onHideARobot(int id) {
    tabWidgetRobots->setTabEnabled(id-1, false);
    
    float orient = 0;
    float w = cos(orient/2), z = sin(orient/2);
    float y = 3.5 + id*0.5;
    float x = 4;
    
    ostringstream topicName;
    topicName << "pioneer_" << id;

    string command = "rosservice call /gazebo/set_model_state '{model_state: { model_name: " + topicName.str() + ", pose: { position: { x: " + to_string(x) + ", y: " + to_string(y) + ",z: 0 }, orientation: {x: 0, y: 0, z: "+ to_string(z) + ", w: " + to_string(w) +" } }, twist: { linear: {x: 0.0 , y: 0 ,z: 0 } , angular: { x: 0.0 , y: 0 , z: 0.0 } } , reference_frame: world } }'";
    system(command.c_str());
    unsigned int microseconds = 1000000;
    usleep(microseconds);
}
