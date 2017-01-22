#include "RobotManagementWindow.hh"

using namespace std;

RobotManagementWindow::RobotManagementWindow() : 
    QDialog(), 
    robots_counter(0) {

    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    // Glowne okienko
    tabWidgetRobots = new QTabWidget ( this ); 
    tabWidgetRobots->setObjectName ( "tabWidgetRobots" );
    tabWidgetRobots->setGeometry ( QRect( QPoint(0, 0), QSize(220, 140)) );
    tabWidgetRobots->setTabShape ( QTabWidget::Triangular );
    
    // Dodaj zakladki
    addNewTab( "pioneer_1" );
    tabWidgetRobots->setTabEnabled(0, false);
    tabWidgetRobots->setTabText(0, QString(""));
    addNewTab( "pioneer_2" );
    tabWidgetRobots->setTabEnabled(1, false);
    tabWidgetRobots->setTabText(1, QString(""));
    addNewTab( "pioneer_3" );
    tabWidgetRobots->setTabEnabled(2, false);
    tabWidgetRobots->setTabText(2, QString(""));
    tabWidgetRobots->setCurrentIndex ( 0 );
    
    // Ustaw rozmiar
    //this->adjustSize();
    int width = 220;
    int height = 140;
    this->setGeometry(QRect( QPoint(0, 0), QSize(width, height)) );
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width*0.5, center.y()-height*0.5);

    this->setFixedSize(this->size());
    
    // Sloty
    QMetaObject::connectSlotsByName ( this );

    QObject::connect(tabWidgetRobots, SIGNAL(currentChanged(int)),
                     this, SLOT(tabSelected(int)));

    pioneer_1_X = -2.0;
    pioneer_1_Y = 0.0;
    pioneer_1_YAW = 0.0;
    pioneer_2_X = -1.0;
    pioneer_2_Y = 0.0;
    pioneer_2_YAW = 0.0;
    pioneer_3_X = 0.0;
    pioneer_3_Y = 0.0;
    pioneer_3_YAW = 0.0;

    this->node = transport::NodePtr(new transport::Node());
    this->node->Init();
    this->sub = node->Subscribe("~/pose/info", &RobotManagementWindow::OnPoseMsg, this);
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
    string robot = "pioneer_";
    robot += to_string(id);
    tabWidgetRobots->setTabText(id-1, QString(robot.c_str()));

   if ( id == 1 )
   {
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(0)))->lineEditX->setText(QString::number(pioneer_1_X, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(0)))->lineEditY->setText(QString::number(pioneer_1_Y, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(0)))->lineEditOrient->setText(QString::number(pioneer_1_YAW, 'f', 3));
   }
   else if ( id == 2 )
   {
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(1)))->lineEditX->setText(QString::number(pioneer_2_X, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(1)))->lineEditY->setText(QString::number(pioneer_2_Y, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(1)))->lineEditOrient->setText(QString::number(pioneer_2_YAW, 'f', 3));
   }
   else if ( id == 3 )
   {
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(2)))->lineEditX->setText(QString::number(pioneer_3_X, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(2)))->lineEditY->setText(QString::number(pioneer_3_Y, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(2)))->lineEditOrient->setText(QString::number(pioneer_3_YAW, 'f', 3));
   }  
}

void RobotManagementWindow::onHideARobot(int id) {
    tabWidgetRobots->setTabEnabled(id-1, false);
    tabWidgetRobots->setTabText(id-1, QString(""));
}

void RobotManagementWindow::tabSelected(int value) {
   if ( value == 0 )
   {
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(0)))->lineEditX->setText(QString::number(pioneer_1_X, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(0)))->lineEditY->setText(QString::number(pioneer_1_Y, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(0)))->lineEditOrient->setText(QString::number(pioneer_1_YAW, 'f', 3));
   }
   else if ( value == 1 )
   {
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(1)))->lineEditX->setText(QString::number(pioneer_2_X, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(1)))->lineEditY->setText(QString::number(pioneer_2_Y, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(1)))->lineEditOrient->setText(QString::number(pioneer_2_YAW, 'f', 3));
   }
   else if ( value == 2 )
   {
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(2)))->lineEditX->setText(QString::number(pioneer_3_X, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(2)))->lineEditY->setText(QString::number(pioneer_3_Y, 'f', 3));
      (qobject_cast<RobotManagementTab *>(tabWidgetRobots->widget(2)))->lineEditOrient->setText(QString::number(pioneer_3_YAW, 'f', 3));
   }  
}

void RobotManagementWindow::OnPoseMsg(ConstPosesStampedPtr &msg)
{
   for ( int i = 0; i < msg->pose_size(); ++i )
   {
      const ::gazebo::msgs::Pose &pose = msg->pose(i);
      std::string name = pose.name();
      if ( name == std::string("pioneer_1") )
      {
         const ::gazebo::msgs::Vector3d &position = pose.position();
         pioneer_1_X = position.x();
         pioneer_1_Y = position.y();

         const ::gazebo::msgs::Quaternion &orientation = pose.orientation();
         double w = orientation.w();
         double x = orientation.x();
         double y = orientation.y();
         double z = orientation.z();
         pioneer_1_YAW = atan2(2.0 * (x*y + z*w), (x*x - y*y - z*z + w*w));
      }
      else if ( name == std::string("pioneer_2") )
      {
         const ::gazebo::msgs::Vector3d &position = pose.position();
         pioneer_2_X = position.x();
         pioneer_2_Y = position.y();

         const ::gazebo::msgs::Quaternion &orientation = pose.orientation();
         double w = orientation.w();
         double x = orientation.x();
         double y = orientation.y();
         double z = orientation.z();
         pioneer_2_YAW = atan2(2.0 * (x*y + z*w), (x*x - y*y - z*z + w*w));
      }
      else if ( name == std::string("pioneer_3") )
      {
         const ::gazebo::msgs::Vector3d &position = pose.position();
         pioneer_3_X = position.x();
         pioneer_3_Y = position.y();

         const ::gazebo::msgs::Quaternion &orientation = pose.orientation();
         double w = orientation.w();
         double x = orientation.x();
         double y = orientation.y();
         double z = orientation.z();
         pioneer_3_YAW = atan2(2.0 * (x*y + z*w), (x*x - y*y - z*z + w*w));
      }
   }
}
