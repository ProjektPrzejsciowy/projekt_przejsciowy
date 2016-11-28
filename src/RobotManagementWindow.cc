#include "RobotManagementWindow.hh"

using namespace std;

RobotManagementWindow::RobotManagementWindow() : QDialog()
{
	//this->setGeometry(QRect(80, 70, 341, 251)); // adjustSize()
	tabWidgetRobots = new QTabWidget(this); // QDialog -> QTabWidget tylko po to, zeby ladniej wygladalo
	
	// Glowne okienko
	tabWidgetRobots->setObjectName("tabWidgetRobots");
    tabWidgetRobots->setGeometry(QRect(80, 70, 341, 251)); // adjustSize()
    tabWidgetRobots->setTabShape(QTabWidget::Triangular); 
	
	// Zakladki
	tabRobot1 = new QWidget();
	tabRobot1->setObjectName("tabRobot1");	
	tabWidgetRobots->addTab(tabRobot1, QString());
	tabWidgetRobots->setTabText(tabWidgetRobots->indexOf(tabRobot1), "Robot1");

	tabRobot2 = new QWidget();
	tabRobot2->setObjectName("tabRobot2");	
	tabWidgetRobots->addTab(tabRobot2, QString());
	tabWidgetRobots->setTabText(tabWidgetRobots->indexOf(tabRobot2), "Robot2");
	
	tabWidgetRobots->setCurrentIndex(0);
	
	// Lewa czesc - ustawianie polozenia i orientacji 
    verticalLayoutWidget = new QWidget(tabRobot1);
    verticalLayoutWidget->setObjectName("verticalLayoutWidget");
    verticalLayoutWidget->setGeometry(QRect(20, 50, 171, 141));
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName("verticalLayout");
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    
    lineEditX = new QLineEdit(verticalLayoutWidget);
	lineEditX->setObjectName("lineEditX");
    lineEditX->setAlignment(Qt::AlignCenter);
	lineEditX->setText(QString());
    lineEditX->setPlaceholderText("X");
    verticalLayout->addWidget(lineEditX);
	
	lineEditY = new QLineEdit(verticalLayoutWidget);
	lineEditX->setObjectName("lineEditY");
    lineEditY->setAlignment(Qt::AlignCenter);
	lineEditY->setText(QString());
    lineEditY->setPlaceholderText("Y");
    verticalLayout->addWidget(lineEditY);
    
    lineEditOrient = new QLineEdit(verticalLayoutWidget);
    lineEditOrient->setObjectName("lineEditOrient");
    lineEditOrient->setAlignment(Qt::AlignCenter);
	lineEditOrient->setText(QString());
    lineEditOrient->setPlaceholderText("Orientacja");
    verticalLayout->addWidget(lineEditOrient);
    
    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacer);
    
    horizontalLayout = new QHBoxLayout(verticalLayoutWidget);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName("horizontalLayout");

	pushButtonUstaw = new QPushButton(verticalLayoutWidget);
	pushButtonUstaw->setObjectName("pushButtonUstaw"); 
	pushButtonUstaw->setText("Ustaw");
    horizontalLayout->addWidget(pushButtonUstaw);
    
    pushButtonReset = new QPushButton(verticalLayoutWidget);
	pushButtonReset->setObjectName("pushButtonReset"); 
	pushButtonReset->setText("Reset");    
	horizontalLayout->addWidget(pushButtonReset);
    
    verticalLayout->addLayout(horizontalLayout);

	// Nazwa topicu
    labelTopicName = new QLabel(tabRobot1);
    labelTopicName->setObjectName("labelTopicName");
	labelTopicName->setText("Nazwa topicu");
    labelTopicName->setGeometry(QRect(210, 50, 121, 21));
   	
	// Przycisk start/stop
    pushButtonStartStop = new QPushButton(tabRobot1);
	pushButtonStartStop->setObjectName("pushButtonStartStop");	
	pushButtonStartStop->setText(QString());
    pushButtonStartStop->setGeometry(QRect(220, 140, 81, 51));
    icon_green.addFile("../../res/glossy-green-button.png", QSize(), QIcon::Normal, QIcon::Off);
    icon_red.addFile("../../res/glossy-red-button.png", QSize(), QIcon::Normal, QIcon::Off);
    pushButtonStartStop->setIcon(icon_green);
    pushButtonStartStop->setIconSize(QSize(60, 60));
	
	// Ustaw rozmiar
   	//this->adjustSize();
    
    // Sloty
    QMetaObject::connectSlotsByName(this); // TODO
}

void RobotManagementWindow::on_pushButtonStartStop_clicked() {	
	pushButtonStartStop->setIcon(icon_red);
}










