#include "RotaryEncoder.h"

#include <Arduino.h>

RotaryEncoder::RotaryEncoder(int PinA,int PinB,int PinSW)
{
    this->PinA = PinA;
    this->PinB = PinB;
    this->PinSW = PinSW;
}

void RotaryEncoder::INIT()
{
    pinMode(PinA, INPUT);
    pinMode(PinB, INPUT);
    pinMode(PinSW, INPUT);

    readingMask = (0x1 << PinA) | (0x1 << PinB);
}

void RotaryEncoder::CheckPinA()
{
    cli();
    reading = GPIO_REG_READ(GPIO_IN_REG) & readingMask;
    if (reading == readingMask && aFlag)
    {
        encCount--;
        bFlag = 0;
        aFlag = 0;
    }
    else if (reading == (0x1 << PinA))
    {
        bFlag = 1;
    }
    sei();
}

void RotaryEncoder::CheckPinB()
{
    cli();
    reading = GPIO_REG_READ(GPIO_IN_REG) & readingMask;
    if (reading == readingMask && bFlag)
    {
        encCount++;
        bFlag = 0;
        aFlag = 0;
    }
    else if (reading == (0x1 << PinB))
    {
        aFlag = 1;
    }
    sei();
}

void RotaryEncoder::SetSwitch()
{
    ButtonPressed = true;
}

int16_t RotaryEncoder::GetCount()
{
    oldEncCount = encCount;
    return encCount;
}

int RotaryEncoder::GetPinA()
{
    return PinA;
}

int RotaryEncoder::GetPinB()
{
    return PinB;
}

int RotaryEncoder::GetPinSW()
{
    return PinSW;
}

bool RotaryEncoder::GetSwitchState()
{
    if(ButtonPressed)
    {
        ButtonPressed = false;
        return true;
    }
    return false;
}

bool RotaryEncoder::CheckCountChanged()
{
    return oldEncCount != encCount;
}
