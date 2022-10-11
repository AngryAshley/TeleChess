// #include <Arduino.h>
#include <stdint.h>
#include <SparkFun_Qwiic_OLED.h>
#include <res/qw_fnt_5x7.h>
#include <Wire.h>
#include <string.h>

#include "config.h"
#include "RotaryEncoder.h"

QwiicMicroOLED myOLED; // Screen

RotaryEncoder Encoder = RotaryEncoder(ENC_PIN_A,ENC_PIN_B,ENC_PIN_SW);

// I2C Wire config

TwoWire I2C = TwoWire(0); // I2C wire object

IRAM_ATTR void PinA()
{
  Encoder.CheckPinA();
}

IRAM_ATTR void PinB()
{
  Encoder.CheckPinB();
}

IRAM_ATTR void Switch()
{
  Encoder.SetSwitch();
}

void printValToScreen(int val)
{

  char count[20];
  String nr = String(itoa(val, count, 10));

  myOLED.rectangleFill(myOLED.getHeight() / 2 - 8, 16, myOLED.getHeight() - 16, 16);

  int x0 = (myOLED.getWidth() - QW_FONT_5X7.width * nr.length()) / 2;

  int y0 = (myOLED.getHeight() - QW_FONT_5X7.height) / 2;

  myOLED.text(x0, y0, nr, 0);

  myOLED.display();
}

void setup()
{

  Serial.begin(115200);

  //Encoder
  Encoder.INIT();

  attachInterrupt(Encoder.GetPinA(), PinA, RISING);
  attachInterrupt(Encoder.GetPinB(), PinB, RISING);
  attachInterrupt(Encoder.GetPinSW(), Switch, RISING);

  I2C.begin(SDA, SCL);

  delay(500);

  if (!myOLED.begin(I2C, 0X3D))
  {
    Serial.println("Device Begin Failed");
    while (1);
  }

  Serial.println("Begin Success");

  printValToScreen(0);
}

void loop()
{

  if(Encoder.GetSwitchState())
  {
    Serial.printf("Button has been pressed %li\n",clock());
  }

  if (Encoder.CheckCountChanged())
  {
    printValToScreen(Encoder.GetCount());
  }
}