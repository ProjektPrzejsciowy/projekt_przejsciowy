#ifndef _WORLD_CONTROL_HH_
#define _WORLD_CONTROL_HH_

#include <gazebo/common/Plugin.hh>
#ifndef Q_MOC_RUN
   #include <gazebo/transport/transport.hh>
   #include <gazebo/physics/physics.hh>
#endif


namespace gazebo
{
   class WorldControl: public WorldPlugin
   {
      public:
      
         void Load(physics::WorldPtr _parent, sdf::ElementPtr _sdf);
         void Received(const boost::shared_ptr<const msgs::Int> &msg);
         
         
      private:
      
         transport::NodePtr node;
         transport::SubscriberPtr subscriber;
         physics::WorldPtr world;
   };
}


#endif
