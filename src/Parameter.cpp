#include "Parameter.h"

// Motors Parameters
// Pins
byte Parameter::leftWheelPin1      = 9;
byte Parameter::leftWheelPin2      = 7;
byte Parameter::leftWheelpinSleep  = 5;
byte Parameter::rightWheelPin1     = 10;
byte Parameter::rightWheelPin2     = 8;
byte Parameter::rightWheelpinSleep = 4;
byte Parameter::motorSpeedMin      = 15;
byte Parameter::motorSpeedMax      = 255;
bool Parameter::leftWheelTuning    = true; 
bool Parameter::rightWheelTuning   = false;
Constant::MotorMode Parameter::motorMode = Constant::PWM_DIRECTION; 

// Controller
float Parameter::kp = 2;
float Parameter::kd = 0;
float Parameter::ki = 1;

// Encoders Parameters
byte Parameter::rightWheelEncA = 3;
byte Parameter::rightWheelEncB = 13;
byte Parameter::leftWheelEncA  = 2;
byte Parameter::leftWheelEncB  = 11;
Constant::EncoderMode Parameter::encoderMode = Constant::RISING_A; 

// Robot Parameters
float Parameter::wheelRadius        = 0.035; // [m]
float Parameter::lengthBetweenWheel = 0.210; // [m]
// Number of ticks per wheel revolution 3591.84/2
float Parameter::ticksPerRevolution = 1795.92/2; //
// TICKS_PER_REVOLUTION/(2*pi*WHEEL_RADIUS)
//const float ticksPerMeter = 8166.56; 4083.27921997
float Parameter::ticksPerMeter      = Parameter::ticksPerRevolution/(2.0*PI*Parameter::wheelRadius);

// Debugging Parameters
float Parameter::angularSpeed = 0;  // [rad/s]
float Parameter::linearSpeed  = 0.3;  // [m/s] max 0.525
int Parameter::timerTicks     = 30; // [ms] 
int Parameter::timerSpeed     = 5;  // [ms]
int Parameter::timerPause     = 3000;  // [ms]