#include <Arduino.h>
#include <stdint.h>
#include <SparkFun_Qwiic_OLED.h>
#include <res/qw_fnt_5x7.h>
#include <Wire.h>
#include <string.h>

QwiicMicroOLED myOLED; // Screen

// Encoder config
#define ENC_PIN_A 19          // CLK pin
#define ENC_PIN_B 18          // DT pin
volatile byte aFlag = 0;      // A First pin with signal
volatile byte bFlag = 0;      // B First pin with signal
volatile int encCount = 0;    // Position of encoder
volatile int oldEncCount = 0; // Last position of encoder
// volatile byte reading = 0;    // Value being read from encoder

// I2C Wire config
#define sda 21            // I2C data pin
#define scl 22            // I2C clock pin
TwoWire I2C = TwoWire(0); // I2C wire object

IRAM_ATTR void PinA()
{
  //cli();
  if (digitalRead(ENC_PIN_B) && digitalRead(ENC_PIN_A) && aFlag)
  {
    encCount--;
    bFlag = 0;
    aFlag = 0;
  }
  else if (digitalRead(ENC_PIN_A))
  {
    bFlag = 1;
  }
  //sei();
}

IRAM_ATTR void PinB()
{
  //cli();
  if (digitalRead(ENC_PIN_B) && digitalRead(ENC_PIN_A) && bFlag)
  {
    encCount++;
    bFlag = 0;
    aFlag = 0;
  }
  else if (digitalRead(ENC_PIN_B))
  {
    aFlag = 1;
  }
  //sei();
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

  pinMode(ENC_PIN_A, INPUT);
  pinMode(ENC_PIN_B, INPUT);

  attachInterrupt(ENC_PIN_A, PinA, RISING);
  attachInterrupt(ENC_PIN_B, PinB, RISING);

  I2C.begin(sda, scl);

  delay(500);

  if (!myOLED.begin(I2C, 0X3D))
  {

    Serial.println(" - Device Begin Failed");
    while (1)
      ;
  }

  Serial.println("- Begin Success");

  // myOLED.rectangleFill(4, 4, myOLED.getWidth()-8, myOLED.getHeight()-8);

  printValToScreen(0);
}

void loop()
{

  if (encCount != oldEncCount)
  {
    printValToScreen(encCount);
    oldEncCount = encCount;
  }
}