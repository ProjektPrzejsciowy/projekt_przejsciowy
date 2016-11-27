#include <string>
#include <sstream>
#include "pp_gazebo_plugin.hh"


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
   QPushButton *button1 = new QPushButton(tr("Konfiguracja swiata (dodaj kulke)"));
   QPushButton *button2 = new QPushButton(tr("Zarzadzanie robotami (usun modele)"));
   QPushButton *button3 = new QPushButton(tr("Wyniki symulacji"));

   frameLayout->addWidget(button1);
   frameLayout->addWidget(button2);
   frameLayout->addWidget(button3);

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

   // Create a node for transportation
   this->node = transport::NodePtr(new transport::Node());
   this->node->Init();

   // Connect to gazebo topics
   this->factoryPub = this->node->Advertise<msgs::Factory>("~/factory");
   this->Pub = this->node->Advertise<msgs::Int>("~/buttons");

   this->counter = 0;
}

SimulationGUI::~SimulationGUI()
{
}

void SimulationGUI::OnButton1()
{
   msgs::Model model;
   model.set_name("sphere_" + std::to_string(this->counter++));
   msgs::Set(model.mutable_pose(), ignition::math::Pose3d(0, 0, 1.5, 0, 0, 0));
   
   const double mass = 1.0;
   const double radius = 0.5;
   msgs::AddSphereLink(model, mass, radius);

   std::ostringstream newModelStr;
   newModelStr << "<sdf version='" << SDF_VERSION << "'>"
               << msgs::ModelToSDF(model)->ToString("")
               << "</sdf>";
    
   // printf("%s", newModelStr.str().c_str());

   // Send the model to the gazebo server
   msgs::Factory msg;
   msg.set_sdf(newModelStr.str());
   this->factoryPub->Publish(msg);
}

void SimulationGUI::OnButton2()
{
   msgs::Int MyMsg;
   MyMsg.set_data(this->counter);
   this->Pub->Publish(MyMsg);
   this->counter = 0;
}

void SimulationGUI::OnButton3()
{
   QDialog *dialog1 = new QDialog();
   dialog1->setWindowTitle(tr("Wyniki symulacji"));
   
   QPushButton* tmpButton = new QPushButton("Przykladowy button", dialog1);
   tmpButton->setGeometry(100, 100, 300, 100);

   dialog1->show();
}
