#include "WorldConfigurationWindow.hh"
#include <QPushButton>

using namespace std;
using namespace gazebo;

WorldConfigurationWindow::WorldConfigurationWindow() : QDialog()
{
   laboratoryList = new QListWidget(this);
   laboratoryList->setGeometry(QRect(QPoint(10, 10),QSize(250, 150)));
   laboratoryList->addItem("Laboratorium L1.5");
   laboratoryList->addItem("Laboratorium Inne");
    
   robotListToAdd = new QListWidget(this);
   robotListToAdd->setGeometry(QRect(QPoint(270, 10),QSize(200, 150)));
   robotListToAdd->addItem("Robot Pionier 1");
   robotListToAdd->addItem("Robot Pionier 2");
   robotListToAdd->addItem("Robot Pionier 3");

   addedRobotList = new QListWidget(this);
   addedRobotList->setGeometry(QRect(QPoint(540, 10),QSize(200, 150)));

   QPushButton *buttonLoad = new QPushButton("Wczytaj",this);
   buttonLoad->setGeometry(QRect(QPoint(10, 170),QSize(120, 30)));
   connect(buttonLoad, SIGNAL(clicked()), this, SLOT(OnButtonLoad()));
   
   QPushButton *buttonClear = new QPushButton("Wyczysc",this);
   buttonClear->setGeometry(QRect(QPoint(140, 170),QSize(120, 30)));
   connect(buttonClear, SIGNAL(clicked()), this, SLOT(OnButtonClear()));

   QPushButton *buttonAddRobot = new QPushButton("Dodaj",this);
   buttonAddRobot->setGeometry(QRect(QPoint(475, 55),QSize(60, 30)));
   connect(buttonAddRobot, SIGNAL(clicked()), this, SLOT(OnButtonAddRobot()));

   QPushButton *buttonDeleteRobot = new QPushButton("Usun",this);
   buttonDeleteRobot->setGeometry(QRect(QPoint(475, 85),QSize(60, 30)));
   connect(buttonDeleteRobot, SIGNAL(clicked()), this, SLOT(OnButtonDeleteRobot()));
   
   this->adjustSize();
   
   // Potrzebne dla transportu wiadomości
   this->node = transport::NodePtr(new transport::Node());
   this->node->Init();
   this->publisher = this->node->Advertise<msgs::Int>("~/buttons");
}

void WorldConfigurationWindow::OnButtonLoad()
{
   // Zapisywanie info o wczytanej sali i robotach (do przemyślenia)
   QString labName = laboratoryList->currentItem()->text();
   addedRobots.clear();
   for (int i = 0; i < addedRobotList->count(); ++i)
   {
      addedRobots.push_back(addedRobotList->item(i)->text());
   }
   
   // Numer w wiadomości to jej identyfikator (póki co)
   msgs::Int MyMsg;
   MyMsg.set_data(laboratoryList->currentRow());
   this->publisher->Publish(MyMsg);
}

void WorldConfigurationWindow::OnButtonClear()
{
   // Numer w wiadomości to jej identyfikator (póki co)
   msgs::Int MyMsg;
   MyMsg.set_data(99);
   this->publisher->Publish(MyMsg);
}

void WorldConfigurationWindow::OnButtonAddRobot()
{
   QListWidgetItem *item = robotListToAdd->takeItem(robotListToAdd->currentRow());
   addedRobotList->addItem(item);
}

void WorldConfigurationWindow::OnButtonDeleteRobot()
{
   QListWidgetItem *item = addedRobotList->takeItem(addedRobotList->currentRow());
   robotListToAdd->addItem(item);
}
