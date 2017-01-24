#include "ResultsWindow.hh"
#include <QPushButton>

using namespace std;
using namespace gazebo;

ResultsWindow::ResultsWindow() : QDialog()
{
        this->setWindowFlags(Qt::WindowStaysOnTopHint);
        
	QTabWidget *table = new QTabWidget(this);
	table->setGeometry(QRect(QPoint(10, 10),QSize(650, 440)));
   
	QWidget *tab1 = new QWidget();
	table->addTab(tab1, "Pionier_1 X-Y");
	
	plot = new QCustomPlot(tab1);
	plot->setGeometry(QRect(QPoint(10, 10),QSize(600, 400)));
	plot->xAxis->setRange(-6, 6);
	plot->yAxis->setRange(-4, 4);
	plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	plot->axisRect()->setupFullAxesBox();
	plot->rescaleAxes();


	QWidget *tab2 = new QWidget();
	table->addTab(tab2, "Pionier_1 X,Y(t)");		
	plot2 = new QCustomPlot(tab2);
	plot2->setGeometry(QRect(QPoint(10, 10),QSize(600, 400)));
	plot2->xAxis->setRange(0, 12);
	plot2->yAxis->setRange(-4, 4);
	plot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	plot2->axisRect()->setupFullAxesBox();
	plot2->rescaleAxes();
	plot2->addGraph();
	plot2->addGraph();
	plot2->graph(1)->setPen(QPen(Qt::red));
	
	Spiral1 = new QCPCurve(this->plot->xAxis, this->plot->yAxis);
	connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
 	dataTimer.start(300); // Interval 0 means to refresh as fast as possible
	


	QPushButton *buttonPoseReg1 = new QPushButton("Rejestruj pozycje", this);
	buttonPoseReg1->setGeometry(QRect(QPoint(10, 455),QSize(180, 30)));
	connect(buttonPoseReg1, SIGNAL(clicked()), this, SLOT(OnButtonPoseReg1()));
	
	QPushButton *buttonSave1 = new QPushButton("Pauza", this);
	buttonSave1->setGeometry(QRect(QPoint(200, 455),QSize(180, 30)));
	connect(buttonSave1, SIGNAL(clicked()), this, SLOT(OnButtonSave1()));

	QPushButton *buttonStop = new QPushButton("Zapisz do pliku", this);
	buttonStop->setGeometry(QRect(QPoint(390, 455),QSize(180, 30)));
	connect(buttonStop, SIGNAL(clicked()), this, SLOT(OnButtonStop()));


	this->adjustSize();

	// Potrzebne dla transportu wiadomości
	this->node = transport::NodePtr(new transport::Node());
	this->node->Init();
	this->publisher = this->node->Advertise<msgs::Int>("~/buttons");

	this->subscriberRobot1 = node->Subscribe("~/robotPose", &ResultsWindow::Received, this);

}

void ResultsWindow::Received(const boost::shared_ptr<const msgs::Quaternion> &msg)
{
	x1.push_back(double(msg->x()));
	y1.push_back(double(msg->y()));
	t.push_back(double(msg->w()));
cout<<"R1: X: "<<msg->x()<<" T: "<<msg->w()<<endl;
	
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

void ResultsWindow::OnButtonStop()
{
	msgs::Int MyMsg;
	MyMsg.set_data(511);
	this->publisher->Publish(MyMsg);
	this->x1.clear();
	this->y1.clear();
	this->t.clear();
	this->plot2->graph(0)->setData(this->t, this->x1);
	this->plot2->graph(1)->setData(this->t, this->y1);
	this->plot2->replot();
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
	this->plot2->graph(0)->addData(this->t.last(), this->x1.last());
	this->plot2->graph(1)->addData(this->t.last(), this->y1.last());
	if(this->t.last() > 11) 
		this->plot2->xAxis->setRange(0, this->t.last()+1);
	this->plot2->replot();
  //  lastPointKey = key;
  //}

}

