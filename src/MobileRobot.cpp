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
  leftController(Parameter::kp, Parameter::kd, Parameter::ki, Parameter::maxIntegral),
  rightController(Parameter::kp, Parameter::kd, Parameter::ki, Parameter::maxIntegral),
  leftWheel(Parameter::leftWheelPin1, Parameter::leftWheelPin2, Parameter::leftWheelpinSleep, 
            Parameter::motorMode, leftController, 
            Parameter::motorSpeedMin, Parameter::motorSpeedMax),
  rightWheel(Parameter::rightWheelPin1, Parameter::rightWheelPin2, Parameter::rightWheelpinSleep,
             Parameter::motorMode, rightController, 
             Parameter::motorSpeedMin, Parameter::motorSpeedMax),
  leftEncoder(Parameter::leftWheelEncA, Parameter::leftWheelEncB, Parameter::encoderMode,
              Parameter::minRawSpeed, Parameter::maxRawSpeed),
  rightEncoder(Parameter::rightWheelEncA, Parameter::rightWheelEncB, Parameter::encoderMode,
               Parameter::minRawSpeed, Parameter::maxRawSpeed),
  previousLinearSpeed(0),
  previousAngularSpeed(0)  
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

void MobileRobot::move(float linearSpeed, float angularSpeed) 
{
  linearSpeed = setSpeed(linearSpeed, previousLinearSpeed, Parameter::maxDeltaSpeed);
  angularSpeed = setSpeed(angularSpeed, previousAngularSpeed, Parameter::maxDeltaSpeed);

  previousLinearSpeed = linearSpeed;
  previousAngularSpeed = angularSpeed;

  float leftWheelSpeed = (linearSpeed - angularSpeed)*Parameter::ticksPerMeter;
  float rightWheelSpeed = (linearSpeed + angularSpeed)*Parameter::ticksPerMeter;
  if(angularSpeed > 0)
    rightWheelSpeed = (linearSpeed + angularSpeed*Parameter::wheelCorrection)*Parameter::ticksPerMeter;
  leftWheel.setSpeed(leftWheelSpeed, Parameter::leftWheelTuning, leftEncoder.getSpeed(), Parameter::maxDeltaSpeed);
  rightWheel.setSpeed(rightWheelSpeed, Parameter::rightWheelTuning, rightEncoder.getSpeed(), Parameter::maxDeltaSpeed);
}

int MobileRobot::getDataLeftWheel() 
{
  return leftEncoder.getData();
}

int MobileRobot::getDataRightWheel() 
{
  return rightEncoder.getData();
}

float MobileRobot::setSpeed(float speedCommand, float previousSpeed, float maxDeltaSpeed) 
{
  float deltaSpeed = speedCommand - previousSpeed;
  if(deltaSpeed > maxDeltaSpeed)
    return previousSpeed + maxDeltaSpeed;
  else if(deltaSpeed < -maxDeltaSpeed)
    return previousSpeed - maxDeltaSpeed;
  else
    return speedCommand;
}
