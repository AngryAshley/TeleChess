#ifndef TIMER_H
#define TIMER_H
#include "ITimer.h"

class Timer
{
private:
    long delay;
    long lastMicros;
    ITimer *callback;
public:
    Timer(long delay, ITimer *callback);
    int update();
    int setDelay(long delay);
};

#endif