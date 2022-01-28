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
const int interval3 = 31000;
long previousMillis3 = 0;

const int interval7 = 8000;
const int interval6 = 7000;
const int interval4 = 6000;
const int interval5 = 5000;
long previousMillis4 = 0;

// Wheel radius in meters
const double WHEEL_RADIUS = 0.040;
 
// Distance from center of the left tire to the center of the right tire in m
const double WHEEL_BASE = 0.231;

// Number of ticks per wheel revolution. We won't use this in this code.
const int TICKS_PER_REVOLUTION = 2248.86/4;

// Number of ticks a wheel makes moving a linear distance of 1 meter
// This value was measured manually. 1920/(2*pi*0.04) = 7439.43
const double TICKS_PER_METER = 8947.93/4;
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
    //robot.move(1.025*(1200.9/4.0)*linear_vel, (7.1/6.0)*(1200.9/4.0)*angular_vel/9.39);
  } 

  /*if (currentMillis > interval3) {
    robot.move(0, 0);
  }
  else
  {
    if (currentMillis - previousMillis2 > interval2) {
      previousMillis2 = currentMillis;
      robot.move(1.025*(1200.9/4.0)*linear_vel, (7.1/6.0)*(1200.9/4.0)*angular_vel/9.39);
    }  
  }*/
  /*else {
    if (currentMillis - previousMillis4 < interval5) {
      if (currentMillis - previousMillis2 > interval2) {
        previousMillis2 = currentMillis;
        robot.move((1200.9/4.0)*linear_vel, 0);
      }
    }
    else if (currentMillis - previousMillis4 < interval4) {
      robot.move(0, 0);
    }
    else if (currentMillis - previousMillis4 < interval6) {
      if (currentMillis - previousMillis2 > interval2) {
        previousMillis2 = currentMillis;
        robot.move(0, (6.35/6.0)*(1200.9/4.0)*angular_vel/9.39);
      }
    }
    else if (currentMillis - previousMillis4 < interval7) {
      robot.move(0, 0);
    }
    else {
     previousMillis4 = currentMillis; 
    }
  }*/
  //robot.move(linear_vel, angular_vel);
  
 
  // If the time interval has passed, publish the number of ticks,
  // and calculate the velocities.
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    left_wheel_tick_count.data = robot.getDataLeftWheel();
    right_wheel_tick_count.data = robot.getDataRightWheel();
    //Serial.println(left_wheel_tick_count.data);
    //Serial.println(right_wheel_tick_count.data);
    // Publish tick counts to topics
    leftPub.publish(&left_wheel_tick_count);
    rightPub.publish(&right_wheel_tick_count); 
    /*Serial.print(left_wheel_tick_count.data);
    Serial.print(" ");
    Serial.println(right_wheel_tick_count.data);*/
  }  
  nh.spinOnce();
}
