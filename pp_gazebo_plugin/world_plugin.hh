#ifndef _WORLD_PLUGIN_HH_
#define _WORLD_PLUGIN_HH_

#include <gazebo/common/Plugin.hh>

namespace gazebo
{
   class NowySwiat: public WorldPlugin
   {
      public:
      
         void Load(physics::WorldPtr _parent, sdf::ElementPtr _sdf);
         
      private:
      
         physics::WorldPtr parent;
   };
}

#endif
