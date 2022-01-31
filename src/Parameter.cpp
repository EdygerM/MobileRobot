#include "Parameter.h"

// Motors Parameters
// Pins
byte Parameter::leftWheelPin1      = 10;
byte Parameter::leftWheelPin2      = 8;
byte Parameter::leftWheelpinSleep  = 4;
byte Parameter::rightWheelPin1     = 9;
byte Parameter::rightWheelPin2     = 7;
byte Parameter::rightWheelpinSleep = 5;
byte Parameter::motorSpeedMin      = 5;
byte Parameter::motorSpeedMax      = 255;
bool Parameter::leftWheelTuning    = false; 
bool Parameter::rightWheelTuning   = false;
Constant::MotorMode Parameter::motorMode = Constant::PWM_DIRECTION; 

// Controller
float Parameter::kp = 2;
float Parameter::kd = 0;
float Parameter::ki = 5;

// Encoders Parameters
byte Parameter::rightWheelEncA = 2;
byte Parameter::rightWheelEncB = 11;
byte Parameter::leftWheelEncA  = 3;
byte Parameter::leftWheelEncB  = 13;
Constant::EncoderMode Parameter::encoderMode = Constant::CHANGE_A; 

// Robot Parameters


float Parameter::wheelRadius = 0.035; // [m]
float Parameter::lengthBetweenWheel = 0.210; // [m]
// Number of ticks per wheel revolution 3591.84/2
float Parameter::ticksPerRevolution = 1795.92; //
// TICKS_PER_REVOLUTION/(2*pi*WHEEL_RADIUS)
//const float ticksPerMeter = 8166.56;
float Parameter::ticksPerMeter = Parameter::ticksPerRevolution/(2.0*PI*Parameter::wheelRadius);