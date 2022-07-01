#ifndef PARAMETER_H
#define PARAMETER_H

#include "Arduino.h"
#include "Constant.h"

namespace Parameter{
  // Motors Parameters
  extern byte leftWheelPin1, leftWheelPin2, leftWheelpinSleep;
  extern byte rightWheelPin1, rightWheelPin2, rightWheelpinSleep;
  extern float kp, kd, ki;
  extern byte motorSpeedMin, motorSpeedMax;
  extern bool leftWheelTuning, rightWheelTuning;
  extern Constant::MotorMode motorMode;

  // Encoders Parameters
  extern byte rightWheelEncA, rightWheelEncB;
  extern byte leftWheelEncA, leftWheelEncB;
  extern Constant::EncoderMode encoderMode;

  // Robot Parameters
  extern float wheelRadius, lengthBetweenWheel;
  extern float ticksPerRevolution, ticksPerMeter;

  // Debugging parameters
  extern float angularSpeed,linearSpeed;
  extern int timerTicks, timerSpeed;
}

#endif
