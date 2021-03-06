#include "MobileRobot.h"
#include "Parameter.h"
#include "Timer.h"
#include <Arduino.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>

#define POWER_OPT A5

MobileRobot robot;

float angular_vel = 0;
float linear_vel = 0;

ros::NodeHandle  nh;

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

// Time interval for measurements in milliseconds
Timer timerRos(30), timerControl(20);

//------------------------------------------------------------ 

void setup() 
{ 
  TCCR1A = 0b10100000;
  TCCR1B = 0b00010001;
  ICR1 = 400;
  pinMode(POWER_OPT, OUTPUT);
  digitalWrite(POWER_OPT, HIGH);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(rightPub);
  nh.advertise(leftPub);
  if(Parameter::leftWheelTuning || Parameter::rightWheelTuning)
    Serial.begin(115200);
  delay(50);
  /*pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(4, OUTPUT);
  analogWrite(10, 150);
  digitalWrite(8, HIGH);
  digitalWrite(4, HIGH);*/
}

void loop() 
{
  if(timerControl.isTime())
    robot.move(linear_vel, angular_vel/9.52); 
 
  // If the time interval has passed, publish the number of ticks,
  // and calculate the velocities.
  if(timerRos.isTime()) {
    left_wheel_tick_count.data = robot.getDataLeftWheel();
    right_wheel_tick_count.data = robot.getDataRightWheel();
    
    leftPub.publish(&left_wheel_tick_count);
    rightPub.publish(&right_wheel_tick_count); 
  }  
  nh.spinOnce();
}
