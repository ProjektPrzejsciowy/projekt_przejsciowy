#include <iostream>
#include "world_plugin.hh"


using namespace gazebo;

GZ_REGISTER_WORLD_PLUGIN(WorldControl)


void WorldControl::Load(physics::WorldPtr _parent, sdf::ElementPtr _sdf)
{
   this->world = _parent;
   
   this->node = transport::NodePtr(new transport::Node());
   this->node->Init();
   
   this->subscriber = node->Subscribe("~/buttons", &WorldControl::Received, this);
}

void WorldControl::Received(const boost::shared_ptr<const msgs::Int> &msg)
{
   std::cout << "Counter: " << msg->data() << std::endl;
   world->Clear();
}
