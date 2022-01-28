#ifndef CONSTANT_H
#define CONSTANT_H

namespace Constant {
  extern float toMicro;
  extern float toMilli;

  // Encoder Modes
  enum Mode {
    RISING_A,
    CHANGE_A,
    CHANGE_AB
  };
}

#endif
