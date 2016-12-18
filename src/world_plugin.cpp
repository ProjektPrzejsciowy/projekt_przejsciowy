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
         model_counter = 0;
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
         if ( !ros::isInitialized() )
         {
            ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
               << "Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package)");
            return;
         }
      }

      void Received(const boost::shared_ptr<const msgs::Int> &msg)
      {
         string sdf_string;
         ifstream file;
         ifstream room;
         string name;
         double x, y, z, roll, pitch, yaw;
         math::Pose model_pos;

         string ground("ground_plane");
         ros::master::V_TopicInfo master_topics;
         ros::master::getTopics(master_topics);

         // cout << "Msg number: " << msg->data() << endl;
         switch (msg->data())
         {
            case 0:
            {
               physics::Model_V modelList(world->GetModels());
               // Usuń wszystko oprócz ground_plane
               for (physics::Model_V::iterator it = modelList.begin(); it != modelList.end(); ++it)
               {
                  if (ground.compare((*it)->GetName()))
                  {
                     msgs::Request *MyMsg = msgs::CreateRequest("entity_delete", (*it)->GetName());
                     this->publisher->Publish(*MyMsg);
                  }
               }
               room.open("/root/catkin_ws/src/projekt_przejsciowy/worlds/salaL15.txt");
               while ( room >> name >> x >> y >> z >> roll >> pitch >> yaw )
               {
                  ostringstream model_name, model_dir;
                  sdf::SDF mySDF2;
                  sdf::ElementPtr model2;
                  model_dir.str("");
                  model_dir << "/root/.gazebo/models/" << name << "/model.sdf";
                  file.open( model_dir.str() );
                  sdf_string.clear();
                  file.seekg(0, ios::beg);
                  sdf_string.assign( ( istreambuf_iterator<char>(file) ), ( istreambuf_iterator<char>() ) );
                  mySDF2.SetFromString(sdf_string);
                  model_name.str("");
                  model_name << name << "_" << model_counter;
                  ++model_counter;
                  model2 = mySDF2.Root()->GetElement("model");
                  model2->GetAttribute("name")->SetFromString( model_name.str() );
                  model_pos.Set(x, y, z, roll, pitch, yaw);
                  model2->AddElement("pose")->Set(model_pos);
                  world->InsertModelSDF(mySDF2);
                  file.close();
               }
               room.close();
               break;
            }
            case 1:
            {
               physics::Model_V modelList(world->GetModels());
               // Usuń wszystko oprócz ground_plane
               for (physics::Model_V::iterator it = modelList.begin(); it != modelList.end(); ++it)
               {
                  if (ground.compare((*it)->GetName()))
                  {
                     msgs::Request *MyMsg = msgs::CreateRequest("entity_delete", (*it)->GetName());
                     this->publisher->Publish(*MyMsg);
                  }
               }
               room.open("/root/catkin_ws/src/projekt_przejsciowy/worlds/salaInna.txt");
               while ( room >> name >> x >> y >> z >> roll >> pitch >> yaw )
               {
                  ostringstream model_name, model_dir;
                  sdf::SDF mySDF2;
                  sdf::ElementPtr model2;
                  model_dir.str("");
                  model_dir << "/root/.gazebo/models/" << name << "/model.sdf";
                  file.open( model_dir.str() );
                  sdf_string.clear();
                  file.seekg(0, ios::beg);
                  sdf_string.assign( ( istreambuf_iterator<char>(file) ), ( istreambuf_iterator<char>() ) );
                  mySDF2.SetFromString(sdf_string);
                  model_name.str("");
                  model_name << name << "_" << model_counter;
                  ++model_counter;
                  model2 = mySDF2.Root()->GetElement("model");
                  model2->GetAttribute("name")->SetFromString( model_name.str() );
                  model_pos.Set(x, y, z, roll, pitch, yaw);
                  model2->AddElement("pose")->Set(model_pos);
                  world->InsertModelSDF(mySDF2);
                  file.close();
               }
               room.close();
               break;
            }
            case 2:
               ROS_INFO("Hello World!");
               for ( ros::master::V_TopicInfo::iterator it = master_topics.begin(); it != master_topics.end(); it++ )
               {
                  const ros::master::TopicInfo& info = *it;
                  cout << "topic_" << it - master_topics.begin() << ": " << info.name << endl;
               }
               break;
            case 99:
            {
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
            case 101:case 102:case 103:case 104:case 105:case 106:case 107: // up to 7 robots
            {
               int robot_id = msg->data() % 100;
               ostringstream robot_name;
               robot_name << "pioneer_" << robot_id;
               bool already = false;
               // find if robot is already in the world
               physics::Model_V modelList(world->GetModels());
               for ( physics::Model_V::iterator it = modelList.begin(); it != modelList.end(); ++it )
               {
                  if ( robot_name.str().compare((*it)->GetName()) == 0 )
                  {
                     already = true;
                     break;
                  }
               } 
               // if there is no sucha a robot, add it
               if ( !already )
               {
                  sdf::SDF mySDF;
                  sdf::ElementPtr model;
                  // Open sdf file and assign its content to a string
                  file.open("/root/.gazebo/models/pioneer2dx_with_sensors/model.sdf");
                  file.seekg(0, ios::end); 
                  sdf_string.reserve(file.tellg());
                  file.seekg(0, ios::beg);
                  sdf_string.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                  // Get model and change its name    
                  mySDF.SetFromString(sdf_string);
                  model = mySDF.Root()->GetElement( "model" );
                  robot_name.str("");
                  robot_name << "pioneer_" << robot_id;
                  model->GetAttribute( "name" )->SetFromString ( robot_name.str() );
                  // Add robot with a new name to the world at a given pose
                  math::Pose pose(0, 0, 0, 0, 0, 0);
                  model->AddElement("pose")->Set(pose);
                  world->InsertModelSDF(mySDF);
                  file.close();
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
         }
      }

   private:

      transport::NodePtr node;
      transport::SubscriberPtr subscriber;
      transport::PublisherPtr publisher;
      physics::WorldPtr world;
      int model_counter;

   };

GZ_REGISTER_WORLD_PLUGIN(WorldPluginProject)
}

