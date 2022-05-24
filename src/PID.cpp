#include "PID.h"
#include "Arduino.h"

PID::PID(float kp, float kd, float ki) : 
  previousError(0), 
  integral(0) 
{
  this->kp = kp;
  this->kd = kd;
  this->ki = ki;
}

// Return the controller signal
float PID::getOutput(float setpoint, float measurement, float deltaTime) 
{
  float error = 0;
  float derivative = 0;
  if (deltaTime > 0) {
    error = setpoint - measurement;
    derivative = (error - previousError)/deltaTime;
    integral = integral + error*deltaTime;
    previousError = error;
  }

  return kp*error + kd*derivative + ki*integral;
}

void PID::printTuning(float setpoint, float measurement) 
{
  Serial.print("setpoint:");
  Serial.print(setpoint);
  Serial.print(", ");
  Serial.print("measurement:");
  Serial.println(measurement);
}
