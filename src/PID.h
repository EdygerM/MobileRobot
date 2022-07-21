#ifndef PID_H
#define PID_H

class PID {
  private:
    float kp, kd, ki;
    float previousError, previousIntegral;
  public:
    PID(float kp, float kd, float ki);
    float getOutput(float setpoint, float measurement, float deltaTime);
    void printTuning(float setpoint, float measurement, float command);
};

#endif
