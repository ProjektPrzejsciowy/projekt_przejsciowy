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

	QPushButton *buttonPoseReg1 = new QPushButton("Rejestruj pozycje", tab1);
	buttonPoseReg1->setGeometry(QRect(QPoint(20, 20),QSize(200, 30)));
	connect(buttonPoseReg1, SIGNAL(clicked()), this, SLOT(OnButtonPoseReg1()));
	
	QPushButton *buttonSave1 = new QPushButton("Zapisz do pliku", tab1);
	buttonSave1->setGeometry(QRect(QPoint(20, 80),QSize(200, 30)));
	connect(buttonSave1, SIGNAL(clicked()), this, SLOT(OnButtonSave1()));


	this->adjustSize();

	// Potrzebne dla transportu wiadomości
	this->node = transport::NodePtr(new transport::Node());
	this->node->Init();
	this->publisher = this->node->Advertise<msgs::Int>("~/buttons");
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


