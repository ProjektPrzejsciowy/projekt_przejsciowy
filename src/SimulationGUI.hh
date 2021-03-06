#ifndef _SIMULATION_GUI_HH_
#define _SIMULATION_GUI_HH_

#include <gazebo/gui/GuiPlugin.hh>
#ifndef Q_MOC_RUN
   #include <gazebo/transport/transport.hh>
   #include <gazebo/gui/gui.hh>
#endif

#include "WorldConfigurationWindow.hh"
#include "RobotManagementWindow.hh"
#include "ResultsWindow.hh"

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
      
      private:
         WorldConfigurationWindow *dialog1;
         RobotManagementWindow *dialog2;
         ResultsWindow *dialog3;
   };
}

#endif
