#include "MobileRobot.h"

MobileRobot *pointerToRobot;

static void leftWheelInterruptA() 
{ 
  pointerToRobot->leftWheelIncrementA(); 
}

static void rightWheelInterruptA() 
{ 
  pointerToRobot->rightWheelIncrementA(); 
}

static void leftWheelInterruptB() 
{ 
  pointerToRobot->leftWheelIncrementB(); 
}

static void rightWheelInterruptB() 
{ 
  pointerToRobot->rightWheelIncrementB(); 
}

MobileRobot::MobileRobot() : leftWheel(Parameter::leftWheelPin1, Parameter::leftWheelPin2, Parameter::leftWheelpinSleep, 
                           Parameter::leftWheelEncA, Parameter::leftWheelEncB, Parameter::mode, 
                           Parameter::kp, Parameter::kd, Parameter::ki),
  rightWheel(Parameter::rightWheelPin1, Parameter::rightWheelPin2, Parameter::rightWheelpinSleep,
             Parameter::rightWheelEncA, Parameter::rightWheelEncB, Parameter::mode,
             Parameter::kp, Parameter::kd, Parameter::ki)
{
  pointerToRobot = this;
  attachInterrupt(digitalPinToInterrupt(Parameter::leftWheelEncA), leftWheelInterruptA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Parameter::rightWheelEncA), rightWheelInterruptA, CHANGE);
}

void MobileRobot::leftWheelIncrementA() 
{
  leftWheel.incrementA();
}

void MobileRobot::rightWheelIncrementA() 
{
  rightWheel.incrementA();
}

void MobileRobot::leftWheelIncrementB() 
{
  leftWheel.incrementB();
}

void MobileRobot::rightWheelIncrementB() 
{
  rightWheel.incrementB();
}

void MobileRobot::move(float linear_vel, float angular_vel) 
{
  float leftWheelSpeed = linear_vel - angular_vel;
  float rightWheelSpeed = linear_vel + angular_vel;
  leftWheel.setSpeed(leftWheelSpeed, Parameter::leftWheelTuning);
  rightWheel.setSpeed(rightWheelSpeed, Parameter::rightWheelTuning);
}

int MobileRobot::getDataLeftWheel() 
{
  return leftWheel.getData();
}

int MobileRobot::getDataRightWheel() 
{
  return rightWheel.getData();
}
