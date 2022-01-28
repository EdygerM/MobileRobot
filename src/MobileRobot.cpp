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

MobileRobot::MobileRobot() : 
  leftWheel(Parameter::leftWheelPin1, Parameter::leftWheelPin2, Parameter::leftWheelpinSleep, 
            Parameter::motorMode, Parameter::kp, Parameter::kd, Parameter::ki, 
            Parameter::motorSpeedMin, Parameter::motorSpeedMax),
  rightWheel(Parameter::rightWheelPin1, Parameter::rightWheelPin2, Parameter::rightWheelpinSleep,
             Parameter::motorMode, Parameter::kp, Parameter::kd, Parameter::ki, 
             Parameter::motorSpeedMin, Parameter::motorSpeedMax),
  leftEncoder(Parameter::leftWheelEncA, Parameter::leftWheelEncB, Parameter::encoderMode),
  rightEncoder(Parameter::rightWheelEncA, Parameter::rightWheelEncB, Parameter::encoderMode)
{
  pointerToRobot = this;
  initInterrupt();
}

void MobileRobot::initInterrupt()
{
  if(Parameter::encoderMode == Constant::RISING_A) {
    attachInterrupt(digitalPinToInterrupt(Parameter::leftWheelEncA), leftWheelInterruptA, RISING);
    attachInterrupt(digitalPinToInterrupt(Parameter::rightWheelEncA), rightWheelInterruptA, RISING);
  }
  else if(Parameter::encoderMode == Constant::CHANGE_A || Parameter::encoderMode == Constant::CHANGE_AB) {
    attachInterrupt(digitalPinToInterrupt(Parameter::leftWheelEncA), leftWheelInterruptA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Parameter::rightWheelEncA), rightWheelInterruptA, CHANGE);
    if(Parameter::encoderMode == Constant::CHANGE_AB) {
      attachInterrupt(digitalPinToInterrupt(Parameter::leftWheelEncB), leftWheelInterruptB, CHANGE);
      attachInterrupt(digitalPinToInterrupt(Parameter::rightWheelEncB), rightWheelInterruptB, CHANGE);
    }
  }
}

void MobileRobot::leftWheelIncrementA() 
{
  leftEncoder.incrementA();
}

void MobileRobot::rightWheelIncrementA() 
{
  rightEncoder.incrementA();
}

void MobileRobot::leftWheelIncrementB() 
{
  leftEncoder.incrementB();
}

void MobileRobot::rightWheelIncrementB() 
{
  rightEncoder.incrementB();
}

void MobileRobot::move(float linear_vel, float angular_vel) 
{
  float leftWheelSpeed = linear_vel - angular_vel;
  float rightWheelSpeed = linear_vel + angular_vel;
  leftWheel.setSpeed(leftWheelSpeed, Parameter::leftWheelTuning, leftEncoder.getData());
  rightWheel.setSpeed(rightWheelSpeed, Parameter::rightWheelTuning, rightEncoder.getData());
}

int MobileRobot::getDataLeftWheel() 
{
  return leftEncoder.getData();
}

int MobileRobot::getDataRightWheel() 
{
  return rightEncoder.getData();
}
