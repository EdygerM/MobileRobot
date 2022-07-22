#include "PID.h"
#include "Arduino.h"

PID::PID(float kp, float kd, float ki) : 
  previousError(0), 
  previousIntegral(0)
{
  this->kp = kp;
  this->kd = kd;
  this->ki = ki;
}

// Return the controller signal
float PID::getOutput(float setpoint, float measurement, float deltaTime) 
{
  if(setpoint == 0)
    previousIntegral = 0;
  if(previousIntegral >= 100)
    previousIntegral = 100;
  float error = 0;
  float derivative = 0;
  float integral = 0;
  if (deltaTime > 0) {
    error = setpoint - measurement;
    derivative = (error - previousError)/deltaTime;
    integral = previousIntegral + error*deltaTime;
    previousError = error;
    previousIntegral = integral;
    //Serial.println(integral);
  }

  return kp*error + kd*derivative + ki*integral;
}

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
