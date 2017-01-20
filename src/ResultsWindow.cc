#include "ResultsWindow.hh"
#include <QPushButton>

using namespace std;
using namespace gazebo;

ResultsWindow::ResultsWindow() : QDialog()
{

	QTabWidget *table = new QTabWidget(this);
	table->setGeometry(QRect(QPoint(10, 10),QSize(650, 480)));
   
	QWidget *tab1 = new QWidget();
	table->addTab(tab1, "Pionier_1");
	

	plot = new QCustomPlot(tab1);
	plot->setGeometry(QRect(QPoint(10, 10),QSize(600, 400)));
	
	//plot->addGraph();	
	//plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
	plot->xAxis->setRange(-6, 6);
	plot->yAxis->setRange(-4, 4);
	plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	plot->axisRect()->setupFullAxesBox();
	plot->rescaleAxes();

	Spiral1 = new QCPCurve(this->plot->xAxis, this->plot->yAxis);
	connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
 	dataTimer.start(500); // Interval 0 means to refresh as fast as possible
	


	QPushButton *buttonPoseReg1 = new QPushButton("Rejestruj pozycje", tab1);
	buttonPoseReg1->setGeometry(QRect(QPoint(10, 420),QSize(180, 30)));
	connect(buttonPoseReg1, SIGNAL(clicked()), this, SLOT(OnButtonPoseReg1()));
	
	QPushButton *buttonSave1 = new QPushButton("Pauza", tab1);
	buttonSave1->setGeometry(QRect(QPoint(200, 420),QSize(180, 30)));
	connect(buttonSave1, SIGNAL(clicked()), this, SLOT(OnButtonSave1()));

	QPushButton *buttonStop = new QPushButton("Stop", tab1);
	buttonStop->setGeometry(QRect(QPoint(400, 420),QSize(100, 30)));
	connect(buttonStop, SIGNAL(clicked()), this, SLOT(OnButtonStop()));


	this->adjustSize();

	// Potrzebne dla transportu wiadomości
	this->node = transport::NodePtr(new transport::Node());
	this->node->Init();
	this->publisher = this->node->Advertise<msgs::Int>("~/buttons");

	this->subscriberRobot1 = node->Subscribe("~/robotPose", &ResultsWindow::Received, this);
	this->subscriberRobot2 = node->Subscribe("~/robot2Pose", &ResultsWindow::Received2, this);
	this->subscriberRobot3 = node->Subscribe("~/robot3Pose", &ResultsWindow::Received3, this);
	
	

}

void ResultsWindow::Received(const boost::shared_ptr<const msgs::Quaternion> &msg)
{
	x1.push_back(double(msg->x()));
	y1.push_back(double(msg->y()));
cout<<"R1: X: "<<msg->x()<<" Y: "<<msg->y()<<endl;
	
}

void ResultsWindow::Received2(const boost::shared_ptr<const msgs::Quaternion> &msg)
{
//	x1.push_back(double(msg->x()));
//	y1.push_back(double(msg->y()));
cout<<"R2: X: "<<msg->x()<<" Y: "<<msg->y()<<endl;
	
}

void ResultsWindow::Received3(const boost::shared_ptr<const msgs::Quaternion> &msg)
{
//	x1.push_back(double(msg->x()));
//	y1.push_back(double(msg->y()));
cout<<"R3: X: "<<msg->x()<<" Y: "<<msg->y()<<endl;
	
}


void ResultsWindow::OnButtonPoseReg1()
{
	msgs::Int MyMsg;
	MyMsg.set_data(501);
	this->publisher->Publish(MyMsg);
	MyMsg.set_data(502);
	this->publisher->Publish(MyMsg);
	MyMsg.set_data(503);
	this->publisher->Publish(MyMsg);
}

void ResultsWindow::OnButtonSave1()
{
	msgs::Int MyMsg;
	MyMsg.set_data(511);
	this->publisher->Publish(MyMsg);
}

void ResultsWindow::OnButtonStop()
{
	msgs::Int MyMsg;
	MyMsg.set_data(511);
	this->publisher->Publish(MyMsg);
	this->x1.clear();
	this->y1.clear();
}


void ResultsWindow::realtimeDataSlot()
{
  //static QTime time(QTime::currentTime());
  //double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  //static double lastPointKey = 0;
  //if (key-lastPointKey > 0.002) // at most add point every 2 ms
  //{
   	this->Spiral1->setData(this->x1, this->y1);
	this->plot->replot();
  //  lastPointKey = key;
  //}

}

