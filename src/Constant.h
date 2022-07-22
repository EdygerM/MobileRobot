#ifndef CONSTANT_H
#define CONSTANT_H

namespace Constant {
  extern float toMicro, toMilli;
  extern short shortMin, shortMax;
  extern float floatMax;

  enum EncoderMode {
    RISING_A,
    CHANGE_A,
    CHANGE_AB
  };

  enum MotorMode {
    PWM_DIRECTION,
    DOUBLE_PWM
  };
}

#endif
