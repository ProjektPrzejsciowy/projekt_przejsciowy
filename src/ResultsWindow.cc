#include "ResultsWindow.hh"
#include <QPushButton>

using namespace std;
using namespace gazebo;

ResultsWindow::ResultsWindow() : QDialog()
{

	QTabWidget *table = new QTabWidget(this);
	table->setGeometry(QRect(QPoint(250, 10),QSize(650, 480)));
   
	QWidget *tab1 = new QWidget();
	QWidget *tab2 = new QWidget();
	table->addTab(tab1, "pozycja X");
	table->addTab(tab2, "pozycja Y");
	plot = new QCustomPlot(tab1);
	plot->setGeometry(QRect(QPoint(10, 10),QSize(600, 400)));
	QPushButton *buttonSaveFile = new QPushButton("Zapisz do pliku...",tab1);
	buttonSaveFile->setGeometry(QRect(QPoint(10, 420),QSize(120, 30)));
	
	plot->addGraph(); // blue line
	plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));

	QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
	timeTicker->setTimeFormat("%h:%m:%s");
	plot->xAxis->setTicker(timeTicker);
	plot->axisRect()->setupFullAxesBox();
	plot->yAxis->setRange(-1.2, 1.2);

	// make left and bottom axes transfer their ranges to right and top axes:
	connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
	connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

	// setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
	connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
	dataTimer.start(0); // Interval 0 means to refresh as fast as possible


	parametersList = new QListWidget(this);
	parametersList->setGeometry(QRect(QPoint(10, 10),QSize(200, 180)));
	parametersList->addItem("Pozycja x");
	parametersList->addItem("Pozycja y");	

	QPushButton *buttonAdd = new QPushButton("Dodaj parametr", this);
	buttonAdd->setGeometry(QRect(QPoint(10, 200),QSize(120, 30)));


	this->adjustSize();

	// Potrzebne dla transportu wiadomości
	this->node = transport::NodePtr(new transport::Node());
	this->node->Init();
	this->publisher = this->node->Advertise<msgs::Int>("~/buttons");
}

void ResultsWindow::realtimeDataSlot()
{
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
    this->plot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
    // rescale value (vertical) axis to fit the current data:
    //ui->customPlot->graph(0)->rescaleValueAxis();
    //ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  this->plot->xAxis->setRange(key, 8, Qt::AlignRight);
  this->plot->replot();
  
  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
//    ui->statusBar->showMessage(
//          QString("%1 FPS, Total Data points: %2")
//          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
//          .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
//          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}



