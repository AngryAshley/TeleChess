#include <Arduino.h>
#include "Timer.h"

Timer::Timer(long delay, ITimer *callback)
    :delay(delay)
    ,callback(callback)
{
    micros = 0;
}

int Timer::setDelay(long delay)
{
    this->delay = delay;
    return 0;
}

int Timer::update()
{
    micros += TIMER_STEP;
    if (delay != 0)
    {
        if (micros - lastMicros > delay)
        {
            lastMicros = micros;
            callback->event();
        }
    }
    return 0;
}