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
    if (!moving)
    {
        Move nextMove = moves.front();
        stepsLeft = nextMove.nrOfSteps;
        digitalWrite(directionPin, nextMove.dir);
        timer->setDelay(maxStepTime);
    }
    else if (stepsLeft > 0)
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
        moving = false;
    }
}

void Stepper::move(bool direction, int nrOfSteps)
{
    Move newMove;
    newMove.dir = direction;
    newMove.nrOfSteps = nrOfSteps;
    moves.push_back(newMove);
    moving = true;
}

void Stepper::update()
{
    if (!moves.empty() || moving)
    {
        timer->update();
    }
}

Stepper::~Stepper()
{
    delete timer;
}

