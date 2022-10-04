#include <Arduino.h>
#include "Stepper.h"

Stepper::Stepper(int enablePin, int directionPin, int stepPin)
    :enablePin(enablePin)
    ,directionPin(directionPin)
    ,stepPin(stepPin)
{
    this->timer = new Timer(0, this);
    pinMode(enablePin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    digitalWrite(enablePin, LOW);
}

void Stepper::event()
{
    if (stepsLeft > 0)
    {
        if (stepTime > minStepTime)
        {
            stepTime -= accel;
            if (stepTime < minStepTime)
            {
                stepTime = minStepTime;
            }

            timer->setDelay(stepTime);
        }
        stepPhase = !stepPhase;
        digitalWrite(stepPin, stepPhase);
        if (stepPhase)
        {
            stepsLeft--;
        }
    }
    else
    {
        timer->setDelay(0);
    }

}

void Stepper::move(bool direction, int nrOfSteps)
{
    digitalWrite(directionPin, direction);
    stepTime = maxStepTime;
    stepsLeft = nrOfSteps;
    timer->setDelay(maxStepTime);
}

void Stepper::update()
{
    timer->update();
}

Stepper::~Stepper()
{
    delete timer;
}


