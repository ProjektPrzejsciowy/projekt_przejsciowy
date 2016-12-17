#ifndef _ROBOT_MANAGEMENT_TAB_HH_
#define _ROBOT_MANAGEMENT_TAB_HH_

#include <vector>
#include <string>

#include <QDialog>
#include <QListWidget>
#include <QString>
#include <QVector>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QMetaObject>

#ifndef Q_MOC_RUN
#include <gazebo/transport/transport.hh>
#endif

class RobotManagementTab : public QWidget {
    Q_OBJECT

private:
    enum State { Start, Stop };    
    State state;

public:
    RobotManagementTab(std::string topicName);
    RobotManagementTab() = delete;
    void receivedMsg ( const boost::shared_ptr<const gazebo::msgs::Int> &msg );

private slots:
    void on_pushButtonStartStop_clicked();
    void on_pushButtonUstaw_clicked();
    void on_pushButtonReset_clicked();

private:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditX;
    QLineEdit *lineEditY;
    QLineEdit *lineEditOrient;
    QSpacerItem *verticalSpacer;
    // Ustawianie i resetowanie polozenia i orientacji
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonUstaw;
    QPushButton *pushButtonReset;
    // Nazwa topicu
    QLabel *labelTopicName;
    // Przycisk start/stop
    QPushButton *pushButtonStartStop;
    QIcon icon_green;
    QIcon icon_red;

// Transport messages
//private:
    //gazebo::transport::NodePtr node;
    //gazebo::transport::PublisherPtr publisher;
    //gazebo::transport::SubscriberPtr subscriber;

};

#endif
