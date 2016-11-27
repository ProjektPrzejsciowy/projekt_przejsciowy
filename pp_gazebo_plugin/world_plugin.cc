#include "world_plugin.hh"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace gazebo;

GZ_REGISTER_WORLD_PLUGIN(WorldControl)

void WorldControl::Load(physics::WorldPtr _parent, sdf::ElementPtr _sdf)
{
   this->world = _parent;
   
   // world->SetPaused(true);
   
   this->node = transport::NodePtr(new transport::Node());
   this->node->Init();
   this->subscriber = node->Subscribe("~/buttons", &WorldControl::Received, this);
   this->publisher = this->node->Advertise<msgs::Request>("~/request");
}

void WorldControl::Received(const boost::shared_ptr<const msgs::Int> &msg)
{
   string ground("ground_plane");

   // cout << "Msg number: " << msg->data() << endl;
   switch (msg->data())
   {
      case 0:
         world->InsertModelFile("model://kaloryfer");
         break;
      case 1:
         world->InsertModelFile("model://stol");
         break;
      case 99:
         physics::Model_V modelList(world->GetModels());
         // Usuń wszystko oprócz ground_plane
         for (physics::Model_V::iterator it = modelList.begin(); it != modelList.end(); ++it)
         {
            if (ground.compare((*it)->GetName()))
            {
               msgs::Request *MyMsg = msgs::CreateRequest("entity_delete", (*it)->GetName());
               this->publisher->Publish(*MyMsg);
               //cout << (*it)->GetName() << endl;
            }
         }
         break;
   }
}
