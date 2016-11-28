#ifndef _ROBOT_MANAGEMENT_WINDOW_HH_
#define _ROBOT_MANAGEMENT_WINDOW_HH_

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

class RobotManagementWindow : public QDialog
{
	Q_OBJECT

   public:
      RobotManagementWindow();
      //~RobotManagementWindow(); // Nie moze byc destruktora, inaczej nie dziala!

   private slots:
		void on_pushButtonStartStop_clicked();
      
   private:
		QTabWidget *tabWidgetRobots;
		QWidget *tabRobot1;
		QWidget *tabRobot2;
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

};

#endif
