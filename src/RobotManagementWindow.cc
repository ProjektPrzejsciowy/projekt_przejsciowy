#include "RobotManagementWindow.hh"

using namespace std;

RobotManagementWindow::RobotManagementWindow() : 
    QDialog(), 
    robots_counter(0) {

    // Glowne okienko
    tabWidgetRobots = new QTabWidget ( this ); 
    tabWidgetRobots->setObjectName ( "tabWidgetRobots" );
    tabWidgetRobots->setGeometry ( QRect( QPoint(10, 10), QSize(330, 240)) );
    tabWidgetRobots->setTabShape ( QTabWidget::Triangular );
   
    // Tymczasowe przyciski -- TODO usunac
    pushButtonUsun = new QPushButton ( this );
    pushButtonUsun->setObjectName ( "pushButtonUsun" );
    pushButtonUsun->setGeometry( QRect( QPoint(30, 0), QSize(30, 10)) );

    // Ustaw rozmiar
    //this->adjustSize();
    this->setGeometry(QRect( QPoint(0, 0), QSize(350, 260)) );
    
    // Sloty
    QMetaObject::connectSlotsByName ( this );
}

void RobotManagementWindow::on_pushButtonUsun_clicked() {
    // TODO usunac przycisk
    tabRobot = tabRobots.back();
    tabRobots.pop_back();
    tabWidgetRobots->removeTab ( tabWidgetRobots->indexOf ( tabRobot ) );
    tabWidgetRobots->setCurrentIndex ( --robots_counter );
    cout << robots_counter << endl;
}

void RobotManagementWindow::addNewTab(string tab_name) {
    tabRobot = new RobotManagementTab();
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

