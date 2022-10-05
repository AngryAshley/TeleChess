#ifndef STEPPER_H
#define STEPPER_H
#include <vector>
#include "Timer.h"

typedef struct
{
    bool dir;
    int nrOfSteps;
} Move;

class Stepper: ITimer
{
    private:
        const int enablePin;
        const int directionPin;
        const int stepPin;

        const long maxStepTime = 1000;
        const long minStepTime = 100;
        const long accel = 50;

        Timer *timer;
        std::vector<Move> moves;
        int stepsLeft;
        bool stepPhase = false;
        bool moving = false;
        long stepTime = 0;
    public:
        Stepper(int enablePin, int directionPin, int stepPin);
        void move(bool direction, int nrOfSteps);
        void event();
        void update();
        ~Stepper();
};


#endif