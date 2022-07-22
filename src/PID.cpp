#include "PID.h"
#include "Arduino.h"
#include "Constant.h"

PID::PID(float kp, float kd, float ki) : 
  previousError(0), 
  previousIntegral(0),
  maxIntegral(Constant::floatMax)
{
  this->kp = kp;
  this->kd = kd;
  this->ki = ki;
}

PID::PID(float kp, float kd, float ki, float maxIntegral) : 
  previousError(0), 
  previousIntegral(0)
{
  this->kp = kp;
  this->kd = kd;
  this->ki = ki;
  this->maxIntegral = maxIntegral;
}

// Return the controller signal
float PID::getOutput(float setpoint, float measurement, float deltaTime) 
{
  float error = 0;
  float derivative = 0;
  float integral = 0;

  if(setpoint == 0)
    previousIntegral = 0;
  else if(previousIntegral >= maxIntegral)
    previousIntegral = maxIntegral;
  else if(previousIntegral <= -maxIntegral)
    previousIntegral = -maxIntegral;

  if (deltaTime > 0) {
    error = setpoint - measurement;
    derivative = (error - previousError)/deltaTime;
    integral = previousIntegral + error*deltaTime;
    previousError = error;
    previousIntegral = integral;
  }

  return kp*error + kd*derivative + ki*integral;
}

// Print the PID parameters useful for tuning
void PID::printTuning(float setpoint, float measurement, float command) 
{
  Serial.print("setpoint:");
  Serial.print(setpoint);
  Serial.print(", ");
  Serial.print("measurement:");
  Serial.print(measurement);
  Serial.print(", ");
  Serial.print("command:");
  Serial.println(command);
}
