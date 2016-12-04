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

    // Zakladki
    tabRobot = new RobotManagementTab();
    tabRobots.push_back ( tabRobot );
    tabWidgetRobots->addTab ( tabRobot, QString() );
    tabWidgetRobots->setTabText ( tabWidgetRobots->indexOf ( tabRobot ), "Robot" );
    tabWidgetRobots->setCurrentIndex ( robots_counter );
    robots_counter++;
   
    // Tymczasowe przyciski -- TODO usunac
    pushButtonDodaj = new QPushButton ( this );
    pushButtonDodaj->setObjectName ( "pushButtonDodaj" );
    pushButtonDodaj->setGeometry(QRect( QPoint(0, 0), QSize(30, 10)) );
    pushButtonUsun = new QPushButton ( this );
    pushButtonUsun->setObjectName ( "pushButtonUsun" );
    pushButtonUsun->setGeometry( QRect( QPoint(30, 0), QSize(30, 10)) );

    // Ustaw rozmiar
    //this->adjustSize();
    this->setGeometry(QRect( QPoint(0, 0), QSize(350, 260)) );
    
    // Sloty
    QMetaObject::connectSlotsByName ( this );
}

void RobotManagementWindow::on_pushButtonDodaj_clicked() {
    // TODO 
    tabRobot = new RobotManagementTab();
    tabRobots.push_back ( tabRobot );
    tabWidgetRobots->addTab ( tabRobot, QString() );
    tabWidgetRobots->setTabText ( tabWidgetRobots->indexOf ( tabRobot ), "Robot1" );
    tabWidgetRobots->setCurrentIndex ( robots_counter++ );
	cout << robots_counter << endl;
}

void RobotManagementWindow::on_pushButtonUsun_clicked() {
    // TODO 
    tabRobot = tabRobots.back();
    tabRobots.pop_back();
    tabWidgetRobots->removeTab ( tabWidgetRobots->indexOf ( tabRobot ) );
    tabWidgetRobots->setCurrentIndex ( --robots_counter );
	cout << robots_counter << endl;
}

