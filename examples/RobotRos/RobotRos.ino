#include "MobileRobot.h"
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
const int interval = 30;
long previousMillis = 0;
long currentMillis = 0;

const int interval2 = 20;
long previousMillis2 = 0;
//------------------------------------------------------------ 

void setup() 
{ 
  pinMode(POWER_OPT, OUTPUT);
  digitalWrite(POWER_OPT, HIGH);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(rightPub);
  nh.advertise(leftPub);
  Serial.begin(57600); 
  delay(1000);
}

void loop() 
{
  // Record the time
  currentMillis = millis();

  if (currentMillis - previousMillis2 > interval2) {
    previousMillis2 = currentMillis;
    robot.move(1.025*(1200.9/2.0)*linear_vel, (7.1/6.0)*(1200.9/2.0)*angular_vel/9.39);
  }  
 
  // If the time interval has passed, publish the number of ticks,
  // and calculate the velocities.
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    left_wheel_tick_count.data = robot.getDataLeftWheel();
    right_wheel_tick_count.data = robot.getDataRightWheel();
    // Publish tick counts to topics
    leftPub.publish(&left_wheel_tick_count);
    rightPub.publish(&right_wheel_tick_count); 
  }  
  nh.spinOnce();
}
