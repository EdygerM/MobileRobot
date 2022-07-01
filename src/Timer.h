#ifndef TIMER_H
#define TIMER_H

class Timer {
  private:
    unsigned long previousTime, interval;
  public:
    Timer(unsigned long interval);
    bool isTime();
    void init();
};

#endif
