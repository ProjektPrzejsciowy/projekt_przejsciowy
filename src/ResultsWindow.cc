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
	plot->xAxis->setRange(-5, 5);
	plot->yAxis->setRange(-5, 5);
	plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	plot->axisRect()->setupFullAxesBox();
	plot->rescaleAxes();

	Spiral1 = new QCPCurve(this->plot->xAxis, this->plot->yAxis);
	connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
 	dataTimer.start(0); // Interval 0 means to refresh as fast as possible
	


	QPushButton *buttonPoseReg1 = new QPushButton("Rejestruj pozycje", tab1);
	buttonPoseReg1->setGeometry(QRect(QPoint(20, 420),QSize(200, 30)));
	connect(buttonPoseReg1, SIGNAL(clicked()), this, SLOT(OnButtonPoseReg1()));
	
	QPushButton *buttonSave1 = new QPushButton("Zapisz do pliku", tab1);
	buttonSave1->setGeometry(QRect(QPoint(300, 420),QSize(200, 30)));
	connect(buttonSave1, SIGNAL(clicked()), this, SLOT(OnButtonSave1()));


	this->adjustSize();

	// Potrzebne dla transportu wiadomości
	this->node = transport::NodePtr(new transport::Node());
	this->node->Init();
	this->publisher = this->node->Advertise<msgs::Int>("~/buttons");

	this->subscriber = node->Subscribe("~/robotPose", &ResultsWindow::Received, this);
	
	

}

void ResultsWindow::Received(const boost::shared_ptr<const msgs::Quaternion> &msg)
{
	cout<<"X: "<< double(msg->x()) <<" Y: "<< double(msg->y()) <<endl;
	//this->plot->graph(0)->addData(double(msg->x()), double(msg->y()));
	//this->plot->replot();
	x1.push_back(double(msg->x()));
	y1.push_back(double(msg->y()));
	
}
void ResultsWindow::OnButtonPoseReg1()
{
	msgs::Int MyMsg;
	MyMsg.set_data(501);
	this->publisher->Publish(MyMsg);
}

void ResultsWindow::OnButtonSave1()
{
	msgs::Int MyMsg;
	MyMsg.set_data(511);
	this->publisher->Publish(MyMsg);
}


void ResultsWindow::realtimeDataSlot()
{
  static QTime time(QTime::currentTime());
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
   	this->Spiral1->setData(this->x1, this->y1);
	this->plot->replot();
    lastPointKey = key;
  }

}

