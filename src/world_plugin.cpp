#include <gazebo/common/Plugin.hh>
#ifndef Q_MOC_RUN
   #include <gazebo/transport/transport.hh>
   #include <gazebo/physics/physics.hh>
#endif
#include <ros/ros.h>
#include <iostream>
#include <string>
#include <sstream>
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
      case 101:case 102:case 103:case 104:case 105:case 106:case 107: // up to 7 robots
      {
        int robot_id = msg->data() % 100;
        ostringstream robot_name;
        robot_name << "pioneer_" << robot_id;
        bool already = false;
        // find if robot is already in the world
        physics::Model_V modelList(world->GetModels());
        for (physics::Model_V::iterator it = modelList.begin(); it != modelList.end(); ++it) {
            if (robot_name.str().compare((*it)->GetName()) == 0) {
               already = true;
               break;
            }
        } 
        // if there is no sucha a robot, add it
        if (!already) {
            sdf::SDF mySDF;
            sdf::ElementPtr model;
            string sdf_string;
            ostringstream robot_name;
            ifstream file;
            // Open sdf file and assign its content to a string
            file.open("/root/.gazebo/models/pioneer2dx_with_sensors/model.sdf");
            file.seekg(0, ios::end); 
            sdf_string.reserve(file.tellg());
            file.seekg(0, ios::beg);
            sdf_string.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            // Get model and change its name    
            mySDF.SetFromString(sdf_string);
            model = mySDF.Root()->GetElement( "model" );
            robot_name << "pioneer_" << robot_id;
            model->GetAttribute( "name" )->SetFromString ( robot_name.str() );
            // Add robot with a new name to the world at a given pose
            math::Pose pose(0, 0, 0, 0, 0, 0);
            model->AddElement("pose")->Set(pose);
            world->InsertModelSDF(mySDF);
            //world->InsertModelFile("model://pioneer2dx_with_sensors"); // insert model from .gazebo/models
        }   
        break;
      }
      case 201:
      {
          // TODO
         /* Wyrzuca blad i przerywa symulacjae :(
          * terminate called after throwing an instance of 
          * 'boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::lock_error> >' 
          * what():  boost: mutex lock failed in pthread_mutex_lock: Invalid argument
          * Aborted (core dumped)
         physics::Model_V modelList(world->GetModels());
         for (physics::Model_V::iterator it = modelList.begin(); it != modelList.end(); ++it)
         {
            if ((*it)->GetName() == "pioneer_1")
            {
               cout << (*it)->GetName() << endl;
               msgs::Request *MyMsg = msgs::CreateRequest("entity_delete", (*it)->GetName());
               this->publisher->Publish(*MyMsg);
            }
         }
         */
         break;
      }
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
