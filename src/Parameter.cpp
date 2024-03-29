#include "Parameter.h"

// Motors Parameters
// Pins
byte Parameter::leftWheelPin1      = 9;
byte Parameter::leftWheelPin2      = 7;
byte Parameter::leftWheelpinSleep  = 5;
byte Parameter::rightWheelPin1     = 10;
byte Parameter::rightWheelPin2     = 8;
byte Parameter::rightWheelpinSleep = 4;
byte Parameter::motorSpeedMin      = 0;
byte Parameter::motorSpeedMax      = 230;
bool Parameter::leftWheelTuning    = false; 
bool Parameter::rightWheelTuning   = false;
float Parameter::maxIntegral       = 100;
Constant::MotorMode Parameter::motorMode = Constant::PWM_DIRECTION; 
float Parameter::wheelCorrection = 1.0;

// Controller
float Parameter::kp = 1;
float Parameter::kd = 0.001;
float Parameter::ki = 40;
float Parameter::acceleration = 1.5;

// Encoders Parameters
byte Parameter::rightWheelEncA = 3;
byte Parameter::rightWheelEncB = 13;
byte Parameter::leftWheelEncA  = 2;
byte Parameter::leftWheelEncB  = 11;
float Parameter::minRawSpeed = 100;
float Parameter::maxRawSpeed = 2145;
Constant::EncoderMode Parameter::encoderMode = Constant::RISING_A; 

// Debugging Parameters
float Parameter::angularSpeed = 0;  // [rad/s]
float Parameter::linearSpeed  = 0;  // [m/s] max 0.525
int Parameter::timerTicks     = 30; // [ms] 
int Parameter::timerSpeed     = 5;  // [ms]
int Parameter::timerPause     = 1000;  // [ms]

// Robot Parameters
float Parameter::wheelRadius        = 0.034; // [m]
float Parameter::lengthBetweenWheel = 0.2085; // [m]
// Number of ticks per wheel revolution 3591.84/2
float Parameter::ticksPerRevolution = 1795.92/2; //
// TICKS_PER_REVOLUTION/(2*pi*WHEEL_RADIUS)
//const float ticksPerMeter = 8166.56; 4083.27921997
float Parameter::ticksPerMeter      = Parameter::ticksPerRevolution/(2.0*PI*Parameter::wheelRadius);
float Parameter::rotationLength     = (2.0*PI*0.5*Parameter::lengthBetweenWheel);
float Parameter::maxDeltaSpeed      = Parameter::acceleration*Parameter::timerSpeed*1e-3;