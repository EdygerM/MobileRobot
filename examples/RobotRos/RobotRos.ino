#include "MobileRobot.h"
#include "Timer.h"
#include "Parameter.h"
#include <ros.h>
#include <std_msgs/Int16.h> 
#include <geometry_msgs/Twist.h>

#define POWER_OPT A5

MobileRobot robot;
ros::NodeHandle  nh;
float angularSpeed = Parameter::angularSpeed;
float linearSpeed = Parameter::linearSpeed;

void twistToVel(const geometry_msgs::Twist& cmd_vel_msg)
{
  linearSpeed  = cmd_vel_msg.linear.x;
  angularSpeed = cmd_vel_msg.angular.z;
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &twistToVel);

//--------------------------------------------------------
// Keep track of the number of wheel ticks 
std_msgs::Int16 right_wheel_tick_count;
ros::Publisher rightPub("right_ticks", &right_wheel_tick_count);
 
std_msgs::Int16 left_wheel_tick_count;
ros::Publisher leftPub("left_ticks", &left_wheel_tick_count);

Timer timerTicks(Parameter::timerTicks);
Timer timerSpeedControl(Parameter::timerSpeed);
Timer timerPause(Parameter::timerPause);
bool speedPause = true;

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
  timerTicks.init();
  timerSpeedControl.init();
  timerPause.init();

  /*TCCR1A = 0b10100000;
  TCCR1B = 0b00010001;
  ICR1 = 400;*/
}

void loop() 
{
  if (speedPause){
    if (timerPause.isTime()){
      linearSpeed = Parameter::linearSpeed;
      speedPause = false;
    }
    else
      linearSpeed = 0;
  }
  
  if(timerSpeedControl.isTime())
    robot.move(linearSpeed, angularSpeed/9.39);

  if(timerTicks.isTime()) {
    left_wheel_tick_count.data = robot.getDataLeftWheel();
    right_wheel_tick_count.data = robot.getDataRightWheel();
    // Publish tick counts to topics
    leftPub.publish(&left_wheel_tick_count);
    rightPub.publish(&right_wheel_tick_count); 
  }

  nh.spinOnce();
}
