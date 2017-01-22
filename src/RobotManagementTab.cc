#include "RobotManagementTab.hh"
#include <cstdlib>
#include <ros/ros.h>
#include <cmath>
#include <string>

using namespace std;

RobotManagementTab::RobotManagementTab(string topicName) :
    QWidget(),
    state(Start) {
	
    // Lewa czesc - ustawianie polozenia i orientacji
    verticalLayoutWidget = new QWidget ( this );
    verticalLayoutWidget->setObjectName ( "verticalLayoutWidget" );
    verticalLayoutWidget->setGeometry ( QRect ( QPoint(30, 10), QSize(150, 90)) );
    verticalLayout = new QVBoxLayout;
    verticalLayout->setSpacing ( 6 );
    verticalLayout->setContentsMargins ( 11, 11, 11, 11 );
    verticalLayout->setObjectName ( "verticalLayout" );
    verticalLayout->setContentsMargins ( 0, 0, 0, 0 );

    lineEditX = new QLineEdit;
    lineEditX->setObjectName ( "lineEditX" );
    lineEditX->setAlignment ( Qt::AlignCenter );
    lineEditX->setText ( QString() );
    lineEditX->setPlaceholderText ( "X" );
	lineEditX->setStyleSheet("background-color : #32CD32; color : #006400;");
    verticalLayout->addWidget ( lineEditX );

    lineEditY = new QLineEdit;
    lineEditX->setObjectName ( "lineEditY" );
    lineEditY->setAlignment ( Qt::AlignCenter );
    lineEditY->setText ( QString() );
    lineEditY->setPlaceholderText ( "Y" );
	lineEditY->setStyleSheet("background-color : #32CD32; color : #006400;");
    verticalLayout->addWidget ( lineEditY );

    lineEditOrient = new QLineEdit;
    lineEditOrient->setObjectName ( "lineEditOrient" );
    lineEditOrient->setAlignment ( Qt::AlignCenter );
    lineEditOrient->setText ( QString() );
    lineEditOrient->setPlaceholderText ( "Orientacja" );
	lineEditOrient->setStyleSheet("background-color : #32CD32; color : #006400;");
    verticalLayout->addWidget ( lineEditOrient );

    verticalSpacer = new QSpacerItem ( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    verticalLayout->addItem ( verticalSpacer );

    horizontalLayout = new QHBoxLayout;
    horizontalLayout->setSpacing ( 6 );
    horizontalLayout->setObjectName ( "horizontalLayout" );

    pushButtonUstaw = new QPushButton;
    pushButtonUstaw->setObjectName ( "pushButtonUstaw" );
    pushButtonUstaw->setText ( "Ustaw" );
    horizontalLayout->addWidget ( pushButtonUstaw );

    pushButtonReset = new QPushButton;
    pushButtonReset->setObjectName ( "pushButtonReset" );
    pushButtonReset->setText ( "Reset" );
    horizontalLayout->addWidget ( pushButtonReset );

    verticalLayout->addLayout ( horizontalLayout );

    verticalLayoutWidget->setLayout(verticalLayout);
    
     // Nazwa topicu
    labelTopicName = new QLabel ( this );
    labelTopicName->setObjectName ( "labelTopicName" );
    labelTopicName->setText ( QString::fromStdString(topicName) );
    labelTopicName->setGeometry ( QRect ( 230, 20, 120, 20 ) );

    // Sloty
    QMetaObject::connectSlotsByName ( this );

    // Transport wiadomosci
   this->node = gazebo::transport::NodePtr ( new gazebo::transport::Node() );
   this->node->Init();
   this->publisher = this->node->Advertise<gazebo::msgs::Int> ( "~/buttons" ); // Topic okreslony w WorldControl.cc
}

void RobotManagementTab::on_pushButtonUstaw_clicked() {
    bool correct;
	bool wrong = false;
	lineEditX->setStyleSheet("background-color : #32CD32; color : #006400;");
	lineEditY->setStyleSheet("background-color : #32CD32; color : #006400;");
	lineEditOrient->setStyleSheet("background-color : #32CD32; color : #006400;");

    lineEditX->text().toFloat(&correct);
    if(!correct)
    {
	ROS_INFO("Wrong X-coordinate!!");
	lineEditX->setStyleSheet("background-color : #FF6347; color : #800000;");
	wrong = true;
    }

    lineEditY->text().toFloat(&correct);
    if(!correct)
    {
	ROS_INFO("Wrong Y-coordinate!!");
	lineEditY->setStyleSheet("background-color : #FF6347; color : #800000;");
	wrong = true;
    }      

    float orient = lineEditOrient->text().toFloat(&correct);
    if(!correct)
    {
	ROS_INFO("Wrong Orientation!!");
	lineEditOrient->setStyleSheet("background-color : #FF6347; color : #800000;");
	wrong = true;
    }
	if(wrong) return;

    float w = cos(orient/2), z = sin(orient/2);
    string topicName = labelTopicName->text().toStdString();   

    string command = "rosservice call /gazebo/set_model_state '{model_state: { model_name: " + topicName + ", pose: { position: { x: " + lineEditX->text().toStdString() + ", y: " + lineEditY->text().toStdString() + ",z: 0 }, orientation: {x: 0, y: 0, z: "+ to_string(z) + ", w: " + to_string(w) +" } }, twist: { linear: {x: 0.0 , y: 0 ,z: 0 } , angular: { x: 0.0 , y: 0 , z: 0.0 } } , reference_frame: world } }'";
    system(command.c_str());
}

void RobotManagementTab::on_pushButtonReset_clicked() {
    string topicName = labelTopicName->text().toStdString();   
    string command = "rosservice call /gazebo/set_model_state '{model_state: { model_name: "+ topicName + ", pose: { position: { x: 0, y: 0 ,z: 0 }, orientation: {x: 0, y: 0, z: 0, w: 1 } }, twist: { linear: {x: 0.0 , y: 0 ,z: 0 } , angular: { x: 0.0 , y: 0 , z: 0.0 } } , reference_frame: world } }'";
    system(command.c_str());

    lineEditX->setText(QString::number(0.0, 'f', 3));
    lineEditY->setText(QString::number(0.0, 'f', 3));
    lineEditOrient->setText(QString::number(0.0, 'f', 3));
}

