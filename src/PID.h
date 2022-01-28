/* 
 *  PID.h
 *  
 *  Created: 26.01.22
 *  By: Edy Mariano
 *  
 *  Modified: 26.01.22 
 *  By: Edy Mariano
 *  
 */ 

#ifndef PID_H
#define PID_H

class PID {
  private:
    float kp, kd, ki;
    float previousError;
    float integral;
  public:
    PID(float kp, float kd, float ki);
    float getOutput(float setpoint, float measurement, float deltaTime);
};

#endif
