#include <sstream>
#include <gazebo/physics/physics.hh>
#include <gazebo/transport/transport.hh>
#include "world_plugin.hh"

using namespace gazebo;

GZ_REGISTER_WORLD_PLUGIN(NowySwiat)

void NowySwiat::Load(physics::WorldPtr _parent, sdf::ElementPtr _sdf)
{
   this->parent = _parent;
   
   this->parent->GetName();
   
   // Create a new transport node
   transport::NodePtr node(new transport::Node());

   // Initialize the node with the world name
   node->Init(_parent->GetName());

   // Create a publisher on the ~/physics topic
   transport::PublisherPtr physicsPub =
     node->Advertise<msgs::Physics>("~/physics");

   msgs::Physics physicsMsg;
   physicsMsg.set_type(msgs::Physics::ODE);

   // Set the step time
   physicsMsg.set_max_step_size(0.01);

   // Change gravity
   msgs::Set(physicsMsg.mutable_gravity(),
       ignition::math::Vector3d(0.03, 0, -0.1));
   physicsPub->Publish(physicsMsg);
}
