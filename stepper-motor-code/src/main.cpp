#include <Arduino.h>
#include "Stepper.h"

#define ENABLE_PIN 25
#define DIRECTION_PIN 33
#define STEP_PIN 32

Stepper *stepper;
hw_timer_t * timer = NULL;


void IRAM_ATTR onTimer() {
  stepper->update();
}

void setup() {
  Serial.begin(9600);
  stepper = new Stepper(ENABLE_PIN, DIRECTION_PIN, STEP_PIN);

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, TIMER_STEP, true);
  timerAlarmEnable(timer);
  
}

void loop() {
  stepper->move(true, 1600);
  delay(2000);
  stepper->move(false, 1600);
  delay(2000);
}