#include "Motor.h"
#include "Constant.h"

Motor::Motor(byte pin1, byte pin2, byte pinSleep, byte encoderA, byte encoderB) : 
  encoder(encoderA, encoderB), 
  controller(1, 0, 0), 
  previousTime(0), 
  previousPos(0) 
{
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->pinSleep = pinSleep;
  init();
}

Motor::Motor(byte pin1, byte pin2, byte pinSleep, byte encoderA, byte encoderB, Constant::Mode mode) : 
  encoder(encoderA, encoderB, mode), 
  controller(1, 0, 0), 
  previousTime(0), 
  previousPos(0) 
{
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->pinSleep = pinSleep;
  init();
}

Motor::Motor(byte pin1, byte pin2, byte pinSleep, byte encoderA, byte encoderB, Constant::Mode mode, float kp, float kd, float ki) : 
  encoder(encoderA, encoderB, mode), 
  controller(kp, kd, ki), 
  previousTime(0), 
  previousPos(0) 
{
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->pinSleep = pinSleep;
  init();
}

void Motor::init() 
{
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pinSleep, OUTPUT);
}

void Motor::setSpeed(float speedSetpoint, bool tuning) 
{ 
  float deltaTime = getDeltaTime();
  int deltaPos = getDeltaPos();
  float speedMeasure = getSpeed(deltaPos, deltaTime);
  float speedOutput = controller.getOutput(speedSetpoint, speedMeasure, deltaTime);
  
  if(tuning) {
    controller.printTuning(speedSetpoint, speedMeasure);
  } 

  // Motor direction
  int dir = 1;
  if(speedOutput < 0){
    dir = -1;
  }
  
  unsigned int speedPWM = abs(speedOutput);
  
  if(speedPWM > Parameter::speedMax)
    speedPWM = Parameter::speedMax;
  else if(speedPWM < Parameter::speedMin)
    speedPWM = 0;
  
  sleepManagement(speedPWM);

  setMotor(dir, speedPWM);
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
int Motor::getDeltaPos() 
{
  int pos = encoder.getData();
  int deltaPos = pos - previousPos;
  previousPos = pos;
  
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

void Motor::sleepManagement(unsigned int speedCommand) 
{
  if(pinSleep) {
    if(speedCommand < Parameter::speedMin)
      digitalWrite(pinSleep, LOW);
    else
      digitalWrite(pinSleep, HIGH);
  }
}

void Motor::setMotor(int dir, int pwmVal)
{
  if(dir == 1){
    analogWrite(pin1, pwmVal);
    digitalWrite(pin2, HIGH);
  }
  else if(dir == -1){
    analogWrite(pin1, pwmVal);
    digitalWrite(pin2, LOW);
  }
  else{
    digitalWrite(pin1, 0);
    digitalWrite(pin2, HIGH);
  }
}

void Motor::incrementA() 
{
  encoder.incrementA();
}

void Motor::incrementB() 
{
  encoder.incrementB();
}

int Motor::getData() 
{
  return encoder.getData();
}
