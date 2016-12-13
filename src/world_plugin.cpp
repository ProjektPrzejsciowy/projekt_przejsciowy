#include <gazebo/common/Plugin.hh>
#ifndef Q_MOC_RUN
   #include <gazebo/transport/transport.hh>
   #include <gazebo/physics/physics.hh>
#endif
#include <ros/ros.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace gazebo
{
class WorldPluginProject : public WorldPlugin
{
public:
  WorldPluginProject() : WorldPlugin()
  {
  }
void Received(const boost::shared_ptr<const msgs::Int> &msg)
{
   string ground("ground_plane");
	ros::master::V_TopicInfo master_topics;
	ros::master::getTopics(master_topics);

   // cout << "Msg number: " << msg->data() << endl;
   switch (msg->data())
   {
      case 0:
         world->InsertModelFile("model://kaloryfer");
         break;
      case 1:
         world->InsertModelFile("model://stol");
         break;
      case 2:
	 ROS_INFO("Hello World!");
	 for (ros::master::V_TopicInfo::iterator it = master_topics.begin() ; it != master_topics.end(); it++) {
	   const ros::master::TopicInfo& info = *it;
	   std::cout << "topic_" << it - master_topics.begin() << ": " << info.name << std::endl;
	 }
         break;
      case 98:
	 world->InsertModelFile("model://pioneer2dx_with_sensors"); // insert model from .gazebo/models
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

  void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
  {
   this->world = _world;
   
   // world->SetPaused(true);
   
   this->node = transport::NodePtr(new transport::Node());
   this->node->Init();
   this->subscriber = node->Subscribe("~/buttons", &WorldPluginProject::Received, this);
   this->publisher = this->node->Advertise<msgs::Request>("~/request");
    // Make sure the ROS node for Gazebo has already been initialized                                                                                    
    if (!ros::isInitialized())
    {
      ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
        << "Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package)");
      return;
    }
}
      private:
         transport::NodePtr node;
         transport::SubscriberPtr subscriber;
         transport::PublisherPtr publisher;
         physics::WorldPtr world;
};
GZ_REGISTER_WORLD_PLUGIN(WorldPluginProject)
}
