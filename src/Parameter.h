/* 
 *  Parameter.h
 *  
 *  Created: 26.01.22
 *  By: Edy Mariano
 *  
 *  Modified: 26.01.22 
 *  By: Edy Mariano
 *  
 */ 

#ifndef PARAMETER_H
#define PARAMETER_H

#include "Arduino.h"

namespace Parameter{
  // Motors Parameters
  extern byte leftWheelPin1, leftWheelPin2, leftWheelpinSleep;
  extern byte rightWheelPin1, rightWheelPin2, rightWheelpinSleep;
  extern float kp, kd, ki;
  extern int speedMin, speedMax;

  // Encoder Modes
  enum Mode {
    RISING_A,
    CHANGE_A,
    CHANGE_AB
  };

  // Encoders Parameters
  extern byte rightWheelEncA, rightWheelEncB;
  extern byte leftWheelEncA, leftWheelEncB;
  extern Mode mode;
  
  // Minumum and maximum values for 16-bit integers
  // Range of 65,535
  extern int encDataMin;
  extern int encDataMax;
}


#endif
