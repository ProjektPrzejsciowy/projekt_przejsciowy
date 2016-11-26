#include "experymentwindow.h"
#include <QPushButton>

ExperymentWindow::ExperymentWindow()
{
    addLaboratoryList();
    addRobotsLists();

    addButton();
}


void ExperymentWindow::addLaboratoryList()
{
    laboratoryList = new QListWidget(this);
    laboratoryList->setGeometry(QRect(QPoint(10, 10),QSize(250,150)));
    laboratoryList->addItem("Laboratorium L1.5");

}


void ExperymentWindow::addRobotsLists(){
    robotListToAdd = new QListWidget(this);
    robotListToAdd->setGeometry(QRect(QPoint(280, 10),QSize(200,150)));
    robotListToAdd->addItem("Robot Pionier 1");
    robotListToAdd->addItem("Robot Pionier 2");
    robotListToAdd->addItem("Robot Pionier 3");

    addedRobotList = new QListWidget(this);
    addedRobotList->setGeometry(QRect(QPoint(550, 10),QSize(200,150)));
}

void ExperymentWindow::addButton()
{
     QPushButton *buttonLoadSetting = new QPushButton("Wczytaj",this);
     buttonLoadSetting->setGeometry(QRect(QPoint(0,180),QSize(100,50)));
     connect(buttonLoadSetting, SIGNAL(clicked()), this, SLOT(on_clicked_LoadSetting()));

     QPushButton *buttonAddRobot = new QPushButton("dodaj",this);
     buttonAddRobot->setGeometry(QRect(QPoint(485,50),QSize(60,30)));
     connect(buttonAddRobot, SIGNAL(clicked()), this, SLOT(on_clicked_AddRobot()));

     QPushButton *buttonDeleteRobot = new QPushButton("usun",this);
     buttonDeleteRobot->setGeometry(QRect(QPoint(485,80),QSize(60,30)));
     connect(buttonDeleteRobot, SIGNAL(clicked()), this, SLOT(on_clicked_DeleteRobot()));



}

void ExperymentWindow::on_clicked_LoadSetting()
{

    actualLaboratory = laboratoryList->currentItem()->text();
    for(int i = 0; i < addedRobotList->count(); ++i)
    {
        addedRobots.push_back(addedRobotList->item(i)->text());
    }
    addedRobots;
}

void ExperymentWindow::on_clicked_AddRobot()
{
    QListWidgetItem *item = robotListToAdd->takeItem(robotListToAdd->currentRow());

    addedRobotList->addItem(item);


}

void ExperymentWindow::on_clicked_DeleteRobot()
{
    QListWidgetItem *item = addedRobotList->takeItem(addedRobotList->currentRow());

    robotListToAdd->addItem(item);
}

