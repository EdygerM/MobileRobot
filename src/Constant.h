#ifndef CONSTANT_H
#define CONSTANT_H

namespace Constant {
  extern float toMicro, toMilli;
  // Minumum and maximum values for 16-bit integers
  extern int intMin, intMax;

  // Encoder Modes
  enum Mode {
    RISING_A,
    CHANGE_A,
    CHANGE_AB
  };
}

#endif
