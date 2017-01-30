#!/usr/bin/env python 
# -*- coding: utf-8 -*-

## @class RosAriaDriver
#  
#  Klasa ułatwiająca połączenie z robotem Pioneer
#
#  @author   Damian Barański \n
#  @date     25/02/2015 \n
#  @license  Projekt rozwijany na licencji GNU GPL

import uuid
import roslib
import rospy
import tf
import struct
import sensor_msgs.msg
from sensor_msgs.msg import PointCloud2
from sensor_msgs.msg import LaserScan

import geometry_msgs.msg
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Vector3
from geometry_msgs.msg import Pose
import nav_msgs.msg
from nav_msgs.msg import Odometry
import std_srvs.srv
from std_srvs.srv import Empty
import math
from time import sleep

P=0.3; #Gain
MaxAngleSpeed=0.5;

class  RosAriaDriver():
    #Subscribe rosaria pose topic and return position and rotate
  def _callback_pose(self, data):
   
    self._x = data.pose.pose.position.x
    self._y = data.pose.pose.position.y

    x = data.pose.pose.orientation.x
    y = data.pose.pose.orientation.y
    z = data.pose.pose.orientation.z
    w = data.pose.pose.orientation.w

    self._z = math.atan2(2.0 * (x*y + z*w), (x*x - y*y - z*z + w*w))

    self._ready=1;


  def _callback_sonar(self, data):
    #byte to float32
    i=0;
    self._sonar=[];
    for i in range(0, data.width*12, 12):
      x=struct.unpack('f', '%c%c%c%c' % (data.data[0+i], data.data[1+i], data.data[2+i], data.data[3+i] ))[0];
      y=struct.unpack('f', '%c%c%c%c' % (data.data[4+i], data.data[5+i], data.data[6+i], data.data[7+i] ))[0];
      self._sonar.append([x, y])

    self._SonarReady=1;


  def _callback_laser(self, data):
    self._laser=data.ranges;
    self._LaserReady=1;

  def _callback_wheels(self, data):
    self._wheel_pos=data.position;
    self._wheel_vel=data.velocity;
    self._wheelsReady=1;


  ## Konstruktor.
  #  @param self Wskaźnik na obiekt.
  #  @param robot Nazwa robota.
  def __init__(self, robot):
    self._ROBOT=robot;
    self._x=0;
    self._y=0;
    self._z=0;
    self._x0=0;
    self._y0=0;
    self._z0=0;
    self._ready=0;

    self._sonar = [];
    self._SonarReady=0;
   
    rospy.init_node('drive_sim')
    
    rospy.Subscriber(self._ROBOT+"/RosAria/pose", nav_msgs.msg.Odometry, self._callback_pose)
    rospy.Subscriber(self._ROBOT+"/RosAria/sonar_pointcloud2",  sensor_msgs.msg.PointCloud2, self._callback_sonar)
    rospy.Subscriber(self._ROBOT+"/scan",  sensor_msgs.msg.LaserScan, self._callback_laser)
    rospy.Subscriber(self._ROBOT+"/RosAria/wheels",  sensor_msgs.msg.JointState, self._callback_wheels)

    self._pub = rospy.Publisher(self._ROBOT+'/RosAria/cmd_vel', geometry_msgs.msg.Twist, queue_size=10)


  #rotate robot, in global angle
  ## Powoduje obrót robota.
  #  @param self Wskaźnik na obiekt.
  #  @param angle Kąt w którym ma się znaleźć robot.
  def Rotate(self,angle):
      

      if angle < -3.14 or angle > 3.14:
	rospy.loginfo ("Angle should be in (-3.14, 3.14)")        
	return None

      rate = rospy.Rate(10.0)
      while not rospy.is_shutdown() and abs(angle - self._z)>0.01:
          if (angle - self._z)<0 :
            Dir=1;
          else:
            Dir=-1;
            
          self._pub.publish(geometry_msgs.msg.Twist(Vector3(0,0,0),Vector3(0,0,Dir*min(abs(angle-self._z)/2,MaxAngleSpeed))))
          rospy.loginfo ("Angle: %0.1f",self._z)
          rate.sleep()

      self._pub.publish(geometry_msgs.msg.Twist(Vector3(0,0,0),Vector3(0,0,0)))

  #drive robot X meter
  ## Powoduje jazdę robota.
  #  @param self Wskaźnik na obiekt.
  #  @param X Ilość metrów do przejechania.

  def GoTo(self,X):
      #uruchamiam silniki
      #self._start_motors();

      #wait for data from robot
      

      x0=self._x;
      y0=self._y;
      rospy.Subscriber(self._ROBOT+"/RosAria/pose", nav_msgs.msg.Odometry, self._callback_pose)
      rate = rospy.Rate(10.0)
      l=0;
      while not rospy.is_shutdown() and abs(abs(X)-l)>0.005:
          #if(self.pub.get_num_connections()==0):
          #    rospy.logerr("Oops!  Error connect with robot")
          #    return 

          l=math.sqrt((x0-self._x)*(x0-self._x)+(y0-self._y)*(y0-self._y));
          if (X<0):
             self._pub.publish(geometry_msgs.msg.Twist(Vector3((X+l)*P,0,0),Vector3(0,0,0)))           
          else:
             self._pub.publish(geometry_msgs.msg.Twist(Vector3((X-l)*P,0,0),Vector3(0,0,0)))

          rospy.loginfo ("Distance: %0.2f",abs(abs(X)-l))
          rate.sleep()

  #set speed X in m/s Z in rad/s
  ## Zadanie prędkości jazdy i obrotu.
  #  @param self Wskaźnik na obiekt.
  #  @param X Prędkość postępowa w [m/s].
  #  @param Z Prędkość obrotu w [rad/s].
  #  @param T Czas trwania w [s].
  def SetSpeed(self, X, Z, T):

    self._pub.publish(geometry_msgs.msg.Twist(Vector3(X,0,0),Vector3(0,0,Z)))
    while T>0:
      sleep(0.1);
      self._pub.publish(geometry_msgs.msg.Twist(Vector3(X,0,0),Vector3(0,0,Z)))
      T=T-0.1
    self._pub.publish(geometry_msgs.msg.Twist(Vector3(0,0,0),Vector3(0,0,0)))


  ## Zadanie prędkości lewego i prawego koła .
  #  @param self Wskaźnik na obiekt.
  #  @param L Prędkość lewego koła w [m/s].
  #  @param R Prędkość prawego koła w[m/s].
  #  @param T Czas trwania w [s].
  def SetSpeedLR(self, L, R, T):

    SpeedX = (L+R)/2.0
    SpeedZ = (R-L) /0.326 #polowa roztawu osi
    self._pub.publish(geometry_msgs.msg.Twist(Vector3(SpeedX,0,0),Vector3(0,0,SpeedZ)))
    while T>0:
      sleep(0.1);
      self._pub.publish(geometry_msgs.msg.Twist(Vector3(SpeedX,0,0),Vector3(0,0,SpeedZ)))
      T=T-0.1
    self._pub.publish(geometry_msgs.msg.Twist(Vector3(0,0,0),Vector3(0,0,0)))


  ## Otwarcie chwytaka.
  #  @param self Wskaźnik na obiekt.
  def GripperOpen(self):
    rospy.loginfo ("Gripper opening")


  ## Zamknięcie chwytaka.
  #  @param self Wskaźnik na obiekt.
  def GripperClose(self):
    rospy.loginfo ("Gripper closing")


  ## Podniesienie chwytaka.
  #  @param self Wskaźnik na obiekt.
  def GripperUp(self):
    rospy.loginfo ("Gripper moving up")


  ## Opuszczenie chwytaka.
  #  @param self Wskaźnik na obiekt.
  def GripperDown(self):
    rospy.loginfo ("Gripper moving down")


  ## Metoda zwracająca pozycje robota
  #  @param self Wskaźnik na obiekt.
  #  @return x[m], y[m], z[stopnie].
  
  def GetPose(self):
    while self._ready==0:
      pass
    return (self._x, self._y, self._z)

  ## Zeruje pozycję robota
  #  @param self Wskaźnik na obiekt.
  
  def ResetPose(self):
    pass

  ## Zwraca dane z sonarów
  #  @param self Wskaźnik na obiekt.
  #  @return tabicę [[x,y],[x,y],...].

  def ReadSonar(self):
    self._SonarReady=0;
    while self._SonarReady==0:
      pass
    return self._sonar;

  ## Zwraca dane z lasera
  #
  ## angle_min: -1.57 [rad] \n
  ## angle_max: 1.56 [rad] \n
  ## angle_increment: 0.006135 [rad] \n
  ## range_min: 0.0199 [m] \n
  ## range_max: 5.5999 [m]
  #  @param self Wskaźnik na obiekt.
  #  @return tabicę kolejnych odległości [m].

  def ReadLaser(self):
    self._LaserReady=0;
    while self._LaserReady==0:
      pass
    return self._laser;

  ## Zwraca dane z enkoderów
  #  @param self Wskaźnik na obiekt.
  #  @return tabicę [(posL,posR),(velL,velR)].
 
  def ReadEncoder(self):
    self._wheelsReady=0;
    while self._wheelsReady==0:
      pass
    return [self._wheel_pos, self._wheel_vel];

  ## Zatrzymuje robota poprzez użycia hamulcy
  #  @param self Wskaźnik na obiekt.
  def StopRobot(self):
      self._pub.publish(geometry_msgs.msg.Twist(Vector3(0,0,0),Vector3(0,0,0)))

  ## Informacja.
  #  @param self Wskaźnik na obiekt.
  def About(self):
    print("\n\n\n")
    print("Biblioteka do obsługi robotów pioneer w python")
    print("Autor    : Damian Barański")
    print("Data     : 25-02-2015")
    print("Licencja : GNU GPL")
    print("Kontakt  : damian.baranski@pwr.wroc.pl")
    print("\n\n\n")

  def Version(self):
    return "v1.0.4";

