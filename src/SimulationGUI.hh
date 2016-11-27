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
         SimulationGUI();
         virtual ~SimulationGUI();
         
      protected slots:
         void OnButton1();
         void OnButton2();
         void OnButton3();
   };
}

#endif
