#ifndef PID_H
#define PID_H

class PID {
  private:
    float kp, kd, ki;
    float previousError, previousIntegral, maxIntegral;
  public:
    PID(float kp, float kd, float ki);
    PID(float kp, float kd, float ki, float maxIntegral);
    float getOutput(float setpoint, float measurement, float deltaTime);
    void printTuning(float setpoint, float measurement, float command);
};

#endif
