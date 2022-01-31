#include "Timer.h"
#include "Arduino.h"

Timer::Timer(unsigned long interval) : 
  previousTime(millis())
{
  this->interval = interval;
}

bool Timer::isTime() 
{
  bool isTime = false;
  unsigned long currentTime = millis();

  if(currentTime - previousTime > interval) {
    previousTime = currentTime;
    isTime = true;
  }

  return isTime;
}
