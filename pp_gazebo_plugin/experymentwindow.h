#ifndef EXPERYMENTWINDOW_H
#define EXPERYMENTWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QListWidget>
#include <vector>

using namespace std;

class ExperymentWindow :public QDialog
{
    Q_OBJECT

public:
    ExperymentWindow();

    QListWidget *laboratoryList;
    QListWidget *robotListToAdd;
    QListWidget *addedRobotList;
    void addLaboratoryList();
    void addButton();
    void addRobotsLists();
    QString actualLaboratory;
    vector<QString> addedRobots;

private slots:
    void on_clicked_LoadSetting();
    void on_clicked_AddRobot();
    void on_clicked_DeleteRobot();

};

#endif // EXPERYMENTWINDOW_H

