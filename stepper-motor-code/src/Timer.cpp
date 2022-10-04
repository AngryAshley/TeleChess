#include <Arduino.h>
#include "Timer.h"

Timer::Timer(long delay, ITimer *callback)
    :delay(delay)
    ,callback(callback)
{
    this->lastMicros = micros();
}

int Timer::setDelay(long delay)
{
    this->delay = delay;
    return 0;
}

int Timer::update()
{
    if (delay != 0)
    {
        long time = micros();
        if (time - lastMicros > delay)
        {
            lastMicros = time;
            callback->event();
        }
    }
    return 0;
}