#include "MobileRobot.h"
#include "Constant.h"
#include "Parameter.h"

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
  initInterrupt();
}

void MobileRobot::initInterrupt()
{
  if(Parameter::mode == Constant::RISING_A) {
    attachInterrupt(digitalPinToInterrupt(Parameter::leftWheelEncA), leftWheelInterruptA, RISING);
    attachInterrupt(digitalPinToInterrupt(Parameter::rightWheelEncA), rightWheelInterruptA, RISING);
  }
  else if(Parameter::mode == Constant::CHANGE_A || Parameter::mode == Constant::CHANGE_AB) {
    attachInterrupt(digitalPinToInterrupt(Parameter::leftWheelEncA), leftWheelInterruptA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Parameter::rightWheelEncA), rightWheelInterruptA, CHANGE);
    if(Parameter::mode == Constant::CHANGE_AB) {
      attachInterrupt(digitalPinToInterrupt(Parameter::leftWheelEncB), leftWheelInterruptB, CHANGE);
      attachInterrupt(digitalPinToInterrupt(Parameter::rightWheelEncB), rightWheelInterruptB, CHANGE);
    }
  }
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
