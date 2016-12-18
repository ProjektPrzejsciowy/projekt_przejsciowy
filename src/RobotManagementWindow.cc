#include "RobotManagementWindow.hh"

using namespace std;

RobotManagementWindow::RobotManagementWindow() : 
    QDialog(), 
    robots_counter(0) {

    // Glowne okienko
    tabWidgetRobots = new QTabWidget ( this ); 
    tabWidgetRobots->setObjectName ( "tabWidgetRobots" );
    tabWidgetRobots->setGeometry ( QRect( QPoint(0, 0), QSize(300, 180)) );
    tabWidgetRobots->setTabShape ( QTabWidget::Triangular );

    // Ustaw rozmiar
    //this->adjustSize();
    int width = 300;
    int height = 150;
    this->setGeometry(QRect( QPoint(0, 0), QSize(width, height)) );
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width*0.5, center.y()-height*0.5);
    
    // Sloty
    QMetaObject::connectSlotsByName ( this );
}

// TODO Zostawione tylko jako wzor do implementacji usuwania zakladki, do usuniecia w przyszlosci.
/*
void RobotManagementWindow::on_pushButtonUsun_clicked() {
    tabRobot = tabRobots.back();
    tabRobots.pop_back();
    tabWidgetRobots->removeTab ( tabWidgetRobots->indexOf ( tabRobot ) );
    tabWidgetRobots->setCurrentIndex ( --robots_counter );
    cout << robots_counter << endl;
}
*/

void RobotManagementWindow::addNewTab(string tab_name) {
    tabRobot = new RobotManagementTab(tab_name);
    tabRobots.push_back ( tabRobot );
    tabWidgetRobots->addTab ( tabRobot, QString() );
    tabWidgetRobots->setTabText ( tabWidgetRobots->indexOf ( tabRobot ), tab_name.c_str() );
    tabWidgetRobots->setCurrentIndex ( tabWidgetRobots->count()-1);
}

void RobotManagementWindow::onAddNewRobot(int id) {
    ostringstream robot_name;
    robot_name << "pioneer_" << id;
    // Check if robot is already there
    bool already = false;
    for (int index=0; index<tabWidgetRobots->count(); ++index) {
        if (robot_name.str().compare( tabWidgetRobots->tabText(index).toStdString() ) == 0) {
            already = true;
            break;
        }
    }
    // Create a new tab with the appropriate name
    if (!already) {
        addNewTab( robot_name.str() );
    }
}

