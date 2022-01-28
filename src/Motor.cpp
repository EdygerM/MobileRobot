#include "Motor.h"

Motor::Motor(byte pin1, byte pin2, byte pinSleep, Constant::MotorMode mode, float kp, float kd, float ki) : 
  controller(kp, kd, ki), 
  previousTime(0), 
  previousPos(0), 
  minPWM(5),
  maxPWM(255)
{
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->pinSleep = pinSleep;
  this->mode = mode;
  init();
}

Motor::Motor(byte pin1, byte pin2, byte pinSleep, Constant::MotorMode mode, float kp, float kd, float ki, byte minPWM, byte maxPWM) : 
  controller(kp, kd, ki), 
  previousTime(0), 
  previousPos(0) 
{
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->pinSleep = pinSleep;
  this->mode = mode;
  this->minPWM = minPWM;
  this->minPWM = maxPWM;
  init();
}

void Motor::init() 
{
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pinSleep, OUTPUT);
}

void Motor::setSpeed(float speedSetpoint, bool speedTuning, int position) 
{ 
  float deltaTime = getDeltaTime();
  int deltaPos = getDeltaPosition(position);
  float speedMeasure = getSpeed(deltaPos, deltaTime);
  float speedOutput = controller.getOutput(speedSetpoint, speedMeasure, deltaTime);
  unsigned int speedPWM = getSpeedPWM(speedOutput);
  
  if(speedTuning)
    controller.printTuning(speedSetpoint, speedMeasure);
  
  sleepManagement(speedPWM);
  setMotor(speedPWM, isForward(speedOutput));
}

// Compute time variation between now and the last call
float Motor::getDeltaTime() 
{
  unsigned long currentTime = micros();
  unsigned long deltaTime = 0;

  // deltaTime is not computed at the first call or when micros() overflows to avoid random values
  if(previousTime > 0 && previousTime < currentTime) 
    deltaTime = currentTime - previousTime;
    
  previousTime = currentTime;
  
  return (float)deltaTime*Constant::toMicro;
}

// Compute position variation read on the encoder between now and the last call
int Motor::getDeltaPosition(int position) 
{
  int deltaPos = position - previousPos;
  previousPos = position;
  
  return deltaPos;
}

// Compute the speed depending on the variation of position and time
float Motor::getSpeed(float deltaPos, float deltaTime) 
{
  float speed = 0;
  if(deltaTime > 0)
    speed = deltaPos/deltaTime;

  return deltaPos/deltaTime;
}

unsigned int Motor::getSpeedPWM(float speed)
{
  unsigned int speedPWM = abs(speed);
  
  if(speedPWM > maxPWM)
    speedPWM = maxPWM;
  else if(speedPWM < minPWM)
    speedPWM = 0;

  return speedPWM;
}

void Motor::sleepManagement(unsigned int speedCommand) 
{
  if(pinSleep) {
    if(speedCommand < minPWM)
      digitalWrite(pinSleep, LOW);
    else
      digitalWrite(pinSleep, HIGH);
  }
}

bool Motor::isForward(float speedOutput) 
{
  bool isForward = true;
  if(speedOutput < 0)
    isForward = false;

  return isForward;
}

void Motor::setMotor(int speedPWM, bool isForward)
{
  if(isForward){
    analogWrite(pin1, speedPWM);
    digitalWrite(pin2, HIGH);
  }
  else{
    analogWrite(pin1, speedPWM);
    digitalWrite(pin2, LOW);
  }
}
