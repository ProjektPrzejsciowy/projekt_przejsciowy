#include "ResultsWindow.hh"
#include <QPushButton>

using namespace std;
using namespace gazebo;

ResultsWindow::ResultsWindow() : QDialog()
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
        
	QTabWidget *table = new QTabWidget(this);
	table->setGeometry(QRect(QPoint(10, 10),QSize(650, 450)));
   
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
	plot2->addGraph();
	plot2->graph(1)->setPen(QPen(Qt::red));
	plot2->graph(2)->setPen(QPen(Qt::green));

	
	QWidget *tab3 = new QWidget();
	table->addTab(tab3, "Pionier_2 X,Y(t)");		
	plot3 = new QCustomPlot(tab3);
	plot3->setGeometry(QRect(QPoint(10, 10),QSize(600, 400)));
	plot3->xAxis->setRange(0, 12);
	plot3->yAxis->setRange(-4, 4);
	plot3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	plot3->axisRect()->setupFullAxesBox();
	plot3->rescaleAxes();
	plot3->addGraph();
	plot3->addGraph();
	plot3->addGraph();
	plot3->graph(1)->setPen(QPen(Qt::red));
	plot3->graph(2)->setPen(QPen(Qt::green));


	QWidget *tab4 = new QWidget();
	table->addTab(tab4, "Pionier_3 X,Y(t)");		
	plot4 = new QCustomPlot(tab4);
	plot4->setGeometry(QRect(QPoint(10, 10),QSize(600, 400)));
	plot4->xAxis->setRange(0, 12);
	plot4->yAxis->setRange(-4, 4);
	plot4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	plot4->axisRect()->setupFullAxesBox();
	plot4->rescaleAxes();
	plot4->addGraph();
	plot4->addGraph();
	plot4->addGraph();
	plot4->graph(1)->setPen(QPen(Qt::red));
	plot4->graph(2)->setPen(QPen(Qt::green));


	Spiral1 = new QCPCurve(this->plot->xAxis, this->plot->yAxis);
	Spiral2 = new QCPCurve(this->plot->xAxis, this->plot->yAxis);
	Spiral2->setPen(QPen(Qt::red));
	Spiral3 = new QCPCurve(this->plot->xAxis, this->plot->yAxis);
	Spiral3->setPen(QPen(Qt::green));
	connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
 	dataTimer.start(40); // Interval 0 means to refresh as fast as possible
	

	
	QPushButton *buttonSave1 = new QPushButton("Zapisz do pliku", this);
	buttonSave1->setGeometry(QRect(QPoint(200, 465),QSize(180, 30)));
	connect(buttonSave1, SIGNAL(clicked()), this, SLOT(OnButtonSave1()));

	QPushButton *buttonStop = new QPushButton("Reset danych", this);
	buttonStop->setGeometry(QRect(QPoint(390, 465),QSize(180, 30)));
	connect(buttonStop, SIGNAL(clicked()), this, SLOT(OnButtonStop()));


	this->adjustSize();

	// Potrzebne dla transportu wiadomości
	this->node = transport::NodePtr(new transport::Node());
	this->node->Init();
	this->publisher = this->node->Advertise<msgs::Int>("~/buttons");

	this->subscriberRobot1 = node->Subscribe("~/pose/info", &ResultsWindow::Received, this);

}

void ResultsWindow::Received(ConstPosesStampedPtr &msg)
{
	for ( int i = 0; i < msg->pose_size(); ++i )
	{
		const ::gazebo::msgs::Pose &pose = msg->pose(i);

		std::string name = pose.name();
		if ( name == std::string("pioneer_1") )
		{
			const ::gazebo::msgs::Vector3d &position = pose.position();
			x1.push_back(double(position.x()));
			y1.push_back(double(position.y()));

			const ::gazebo::msgs::Quaternion &orientation = pose.orientation();
			double w = orientation.w();
    		double x = orientation.x();
    		double y = orientation.y();
    		double z = orientation.z();
			w1.push_back(double( atan2(2.0 * (x*y + z*w), (x*x - y*y - z*z + w*w)) ));

      	}	
      	else if ( name == std::string("pioneer_2") )
      	{
			const ::gazebo::msgs::Vector3d &position = pose.position();
			x2.push_back(double(position.x()));
			y2.push_back(double(position.y()));

			const ::gazebo::msgs::Quaternion &orientation = pose.orientation();
			double w = orientation.w();
        	double x = orientation.x();
        	double y = orientation.y();
        	double z = orientation.z();
			w2.push_back(double( atan2(2.0 * (x*y + z*w), (x*x - y*y - z*z + w*w)) ));
    	}
      	else if ( name == std::string("pioneer_3") )
      	{
			const ::gazebo::msgs::Vector3d &position = pose.position();
			x3.push_back(double(position.x()));
			y3.push_back(double(position.y()));

			const ::gazebo::msgs::Quaternion &orientation = pose.orientation();
			double w = orientation.w();
        	double x = orientation.x();
        	double y = orientation.y();
        	double z = orientation.z();
			w3.push_back(double( atan2(2.0 * (x*y + z*w), (x*x - y*y - z*z + w*w)) ));
		}
	}
	const ::gazebo::msgs::Time &time = msg->time();
 	t.push_back(double(time.sec() + double(time.nsec())/1000000000));
}



void ResultsWindow::OnButtonSave1()
{
	this->plot->savePdf("/root/robot_trace.pdf");
	this->plot2->savePdf("/root/robot_pose_1.pdf");
	this->plot3->savePdf("/root/robot_pose_2.pdf");
	this->plot4->savePdf("/root/robot_pose_3.pdf");
	saveRawFile();
}

void ResultsWindow::OnButtonStop()
{
	this->x1.clear();
	this->y1.clear();
	this->w1.clear();
	this->x2.clear();
	this->y2.clear();
	this->w2.clear();
	this->x3.clear();
	this->y3.clear();
	this->w3.clear();
	this->t.clear();

	this->plot2->graph(0)->setData(this->t0, this->x0);
	this->plot2->graph(1)->setData(this->t0, this->y0);
	this->plot2->graph(2)->setData(this->t0, this->w0);
	this->plot2->replot();
	
	this->plot3->graph(0)->setData(this->t0, this->x0);
	this->plot3->graph(1)->setData(this->t0, this->y0);
	this->plot3->graph(2)->setData(this->t0, this->w0);
	this->plot3->replot();

	this->plot4->graph(0)->setData(this->t0, this->x0);
	this->plot4->graph(1)->setData(this->t0, this->y0);
	this->plot4->graph(2)->setData(this->t0, this->w0);
	this->plot4->replot();
}


void ResultsWindow::realtimeDataSlot()
{

   	this->Spiral1->setData(this->x1, this->y1);
	this->Spiral2->setData(this->x2, this->y2);
	this->Spiral3->setData(this->x3, this->y3);
	this->plot->replot();

	this->plot2->graph(0)->addData(this->t.last(), this->x1.last());
	this->plot2->graph(1)->addData(this->t.last(), this->y1.last());
	this->plot2->graph(2)->addData(this->t.last(), this->w1.last());
	if(this->t.last() > 11) 
		this->plot2->xAxis->setRange(0, this->t.last()+1);
	this->plot2->replot();

	this->plot3->graph(0)->addData(this->t.last(), this->x2.last());
	this->plot3->graph(1)->addData(this->t.last(), this->y2.last());
	this->plot3->graph(2)->addData(this->t.last(), this->w2.last());
	if(this->t.last() > 11) 
		this->plot3->xAxis->setRange(0, this->t.last()+1);
	this->plot3->replot();

	this->plot4->graph(0)->addData(this->t.last(), this->x3.last());
	this->plot4->graph(1)->addData(this->t.last(), this->y3.last());
	this->plot4->graph(2)->addData(this->t.last(), this->w3.last());
	if(this->t.last() > 11) 
		this->plot4->xAxis->setRange(0, this->t.last()+1);
	this->plot4->replot();

}


void ResultsWindow::saveRawFile()
{
	ofstream file("/root/robot_pose.csv");
	if(file.good())
	{
		file<<"#Pionier1 X,Pionier1 Y,Pionier1 W,Pionier2 X,Pionier2 Y,Pionier2 W,Pionier3 X,Pionier3 Y,Pionier3 W,time"<<endl;
		for(int i = 0; i < this->t.size(); ++i)
		{
			file << setprecision(5) << saveFilter(x1[i]) << "," 
			<< setprecision(5) << saveFilter(y1[i]) << "," 
			<< setprecision(5) << saveFilter(w1[i]) << "," 
			<< setprecision(5) << saveFilter(x2[i]) << "," 
			<< setprecision(5) << saveFilter(y2[i]) << "," 
			<< setprecision(5) << saveFilter(w2[i]) << "," 
			<< setprecision(5) << saveFilter(x3[i]) << "," 
			<< setprecision(5) << saveFilter(y3[i]) << "," 
			<< setprecision(5) << saveFilter(w3[i]) << "," << t[i] << endl;
		}
		file.close();
		cout << "Zapisano plik!" << endl;
	}
	else
	{
		cout << "Błąd zapisu pliku!" << endl;
	}

}

double ResultsWindow::saveFilter(double value){
	if (value < 1.0e-10 && value > -1.0e-10)
		return 0;
	else if (value < -1.0e+10 || value > 1.0e+10)
		return 0;
	return value;
}


