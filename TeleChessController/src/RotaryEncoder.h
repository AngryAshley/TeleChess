#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <stdint.h>

class RotaryEncoder{
private:
    int PinA;
    int PinB;
    int PinSW;

    volatile uint8_t aFlag = 0;      // A First pin with signal
    volatile uint8_t bFlag = 0;      // B First pin with signal
    volatile int16_t encCount = 0;    // Position of encoder
    volatile int16_t oldEncCount = 0; // Last position of encoder
    volatile uint32_t reading;    // Input reading from register
    volatile uint32_t readingMask; 
    bool ButtonPressed = false;

public:
    RotaryEncoder(int PinA,int PinB,int PinSW);
    void INIT();
    void CheckPinA();
    void CheckPinB();
    void SetSwitch();
    int16_t GetCount();
    int GetPinA();
    int GetPinB();
    int GetPinSW();
    bool GetSwitchState();
    bool CheckCountChanged();
};


#endif