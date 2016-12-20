#include "SimulationGUI.hh"
#include <string>

using namespace gazebo;

// Register this plugin with the simulator
GZ_REGISTER_GUI_PLUGIN(SimulationGUI)

SimulationGUI::SimulationGUI() : GUIPlugin()
{
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

   // Set the frame background and foreground colors
   this->setStyleSheet(
      "QFrame { background-color : rgba(100, 100, 100, 255); color : white; }");

   // Create the main layout
   QHBoxLayout *mainLayout = new QHBoxLayout;

   // Create the frame to hold all the widgets
   QFrame *mainFrame = new QFrame();

   // Create the layout that sits inside the frame
   QHBoxLayout *frameLayout = new QHBoxLayout();

   // Add buttons
   QPushButton *button1 = new QPushButton(tr("Konfiguracja swiata"));
   QPushButton *button2 = new QPushButton(tr("Zarzadzanie robotami"));
   QPushButton *button3 = new QPushButton(tr("Wyniki symulacji"));

   frameLayout->addWidget(button1);
   frameLayout->addWidget(button2);
   frameLayout->addWidget(button3);
   
   // Connecting
   connect(button1, SIGNAL(clicked()), this, SLOT(OnButton1()));
   connect(button2, SIGNAL(clicked()), this, SLOT(OnButton2()));
   connect(button3, SIGNAL(clicked()), this, SLOT(OnButton3()));

   // Add frameLayout to the frame
   mainFrame->setLayout(frameLayout);

   // Add the frame to the main layout
   mainLayout->addWidget(mainFrame);

   // Remove margins to reduce space
   frameLayout->setContentsMargins(4, 4, 4, 4);
   mainLayout->setContentsMargins(0, 0, 0, 0);

   this->setLayout(mainLayout);

   // Position and resize this widget
   this->move(0, 0);
   this->resize(800, 40);

   // Create windows
   dialog1 = new WorldConfigurationWindow();
   dialog1->setWindowTitle(tr("Konfiguracja swiata"));
   dialog2 = new RobotManagementWindow();
   dialog2->setWindowTitle(tr("Zarzadzanie robotami"));
   dialog3 = new ResultsWindow();
   dialog3->setWindowTitle(tr("Wyniki symulacji"));

   // Connect
   connect(dialog1, SIGNAL(addNewRobot(int)), 
           dialog2, SLOT(onAddNewRobot(int)));
}

SimulationGUI::~SimulationGUI()
{

}

void SimulationGUI::OnButton1()
{
   dialog1->show();
}

void SimulationGUI::OnButton2()
{
   dialog2->show();
}

void SimulationGUI::OnButton3()
{
   dialog3->show();
}
