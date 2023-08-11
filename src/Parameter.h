#ifndef PARAMETER_H
#define PARAMETER_H

#include "Arduino.h"
#include "Constant.h"

namespace Parameter{
  // Motors Parameters
  extern byte leftWheelPin1, leftWheelPin2, leftWheelpinSleep;
  extern byte rightWheelPin1, rightWheelPin2, rightWheelpinSleep;
  extern float kp, kd, ki;
  extern float acceleration;
  extern byte motorSpeedMin, motorSpeedMax;
  extern bool leftWheelTuning, rightWheelTuning;
  extern Constant::MotorMode motorMode;
  extern float maxIntegral;
  extern float wheelCorrection;
  extern float maxDeltaSpeed;

  // Encoders Parameters
  extern byte rightWheelEncA, rightWheelEncB;
  extern byte leftWheelEncA, leftWheelEncB;
  extern Constant::EncoderMode encoderMode;
  extern float minRawSpeed, maxRawSpeed;

  // Robot Parameters
  extern float wheelRadius, lengthBetweenWheel;
  extern float ticksPerRevolution, ticksPerMeter;
  extern float rotationLength;

  // Debugging parameters
  extern float angularSpeed,linearSpeed;
  extern int timerTicks, timerSpeed, timerPause;
}

#endif
