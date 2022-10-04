#ifndef TIMER_H
#define TIMER_H
#include "ITimer.h"
#define TIMER_STEP 10

class Timer
{
private:
    long delay;
    long lastMicros;
    long micros;
    ITimer *callback;
public:
    Timer(long delay, ITimer *callback);
    int update();
    int setDelay(long delay);
};

#endif