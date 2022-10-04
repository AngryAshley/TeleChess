#ifndef ITIMER_H
#define ITIMER_H

class ITimer
{
    public:
        virtual void event() = 0;
        virtual ~ITimer() {}
};

#endif