#ifndef _GUIPPPLUGIN_HH_
#define _GUIPPPLUGIN_HH_

#include <string>
#include <gazebo/common/Plugin.hh>
#include <gazebo/gui/GuiPlugin.hh>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829
# include <gazebo/transport/transport.hh>
# include <gazebo/gui/gui.hh>
#endif

namespace gazebo
{
   class GAZEBO_VISIBLE GUIPPPlugin : public GUIPlugin
   {
      Q_OBJECT
      
      public:

         // Constructor
         GUIPPPlugin();

         // Destructor
         virtual ~GUIPPPlugin();
         
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
         transport::PublisherPtr requestPub;
   };
}

#endif
