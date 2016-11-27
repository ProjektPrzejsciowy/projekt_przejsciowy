#ifndef _SIMULATION_GUI_HH_
#define _SIMULATION_GUI_HH_

#include <gazebo/gui/GuiPlugin.hh>
#ifndef Q_MOC_RUN
   #include <gazebo/transport/transport.hh>
   #include <gazebo/gui/gui.hh>
#endif


namespace gazebo
{
   class GAZEBO_VISIBLE SimulationGUI : public GUIPlugin
   {
      Q_OBJECT
      
      public:

         // Constructor
         SimulationGUI();

         // Destructor
         virtual ~SimulationGUI();
         
      protected slots:

         // Slots for button clicks
         void OnButton1();
         void OnButton2();
         void OnButton3();

      private:
      
         // Counter used to create unique model names
         unsigned int counter;

         // Node used to establish communication with gzserver
         transport::NodePtr node;

         // Publisher of factory messages
         transport::PublisherPtr factoryPub;
      
         // Publisher of request messages
         transport::PublisherPtr Pub;
   };
}


#endif
