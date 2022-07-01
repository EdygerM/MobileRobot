#include "MobileRobot.h"
#include "Timer.h"
#include <ros.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>

#define POWER_OPT A5

MobileRobot robot;
ros::NodeHandle  nh;
float angular_vel = 0;
float linear_vel = -0.2;

void twistToVel(const geometry_msgs::Twist& cmd_vel_msg)
{
  linear_vel  = cmd_vel_msg.linear.x;
  angular_vel = cmd_vel_msg.angular.z;
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &twistToVel);

//--------------------------------------------------------
// Keep track of the number of wheel ticks 
std_msgs::Int16 right_wheel_tick_count;
ros::Publisher rightPub("right_ticks", &right_wheel_tick_count);
 
std_msgs::Int16 left_wheel_tick_count;
ros::Publisher leftPub("left_ticks", &left_wheel_tick_count);

Timer timerTicks(30);
Timer timerSpeedControl(1);

//------------------------------------------------------------ 

void setup() 
{ 
  pinMode(POWER_OPT, OUTPUT);
  digitalWrite(POWER_OPT, HIGH);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(rightPub);
  nh.advertise(leftPub);
  Serial.begin(115200); 
  delay(1000);
}

void loop() 
{
  if(timerSpeedControl.isTime())
    robot.move(linear_vel, angular_vel/9.39);

  if(timerTicks.isTime()) {
    left_wheel_tick_count.data = robot.getDataLeftWheel();
    right_wheel_tick_count.data = robot.getDataRightWheel();
    // Publish tick counts to topics
    leftPub.publish(&left_wheel_tick_count);
    rightPub.publish(&right_wheel_tick_count); 
  }

  nh.spinOnce();
}
