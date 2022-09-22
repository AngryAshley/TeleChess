#include <Arduino.h>
#include <stdint.h>
#include <SparkFun_Qwiic_OLED.h>
#include <res/qw_fnt_5x7.h>
#include <Wire.h>
#include <ESP32Encoder.h>
#include <string.h>

QwiicMicroOLED myOLED;

#define encA 19
#define encB 18
volatile int encCount = 0;
int encCountLast = 0;
// int aVal;
ESP32Encoder encoder;

#define sda 21
#define scl 22
TwoWire I2C = TwoWire(0);

IRAM_ATTR void enc_cb(){

  if(digitalRead(encB) == HIGH)
  {
    encCount++;
  }else
  {
    encCount--;
  }
  
  Serial.printf("enc cb: count: %i\n", encCount);
}

void printValToScreen(int val){
  
  char count[20]; 
  String nr = String(itoa(val, count,10));

  //myOLED.erase();

  myOLED.rectangleFill(myOLED.getHeight()/2 -8,  16, myOLED.getHeight()-16, 16);
  
  int x0 = (myOLED.getWidth() - QW_FONT_5X7.width * nr.length())/2;

  int y0 = (myOLED.getHeight() - QW_FONT_5X7.height)/2;

  myOLED.text(x0, y0, nr, 0);

  myOLED.display();
}


void setup() {
  
  Serial.begin(115200);

  pinMode(encA,INPUT);
  pinMode(encB,INPUT);
  // encALast = digitalRead(encA);
  attachInterrupt(encA,enc_cb,RISING);

  // ESP32Encoder::useInternalWeakPullResistors=UP;
  // encoder.attachHalfQuad(encA,encB);
  // encoder.clearCount();

  I2C.begin(sda,scl);

  delay(500);

  if(!myOLED.begin(I2C,0X3D)){

        Serial.println(" - Device Begin Failed");
        while(1);
    }

    Serial.println("- Begin Success");

    //myOLED.rectangleFill(4, 4, myOLED.getWidth()-8, myOLED.getHeight()-8);

    printValToScreen(0);
}

void loop() {

  if(encCount != encCountLast){
    printValToScreen(encCount);
    encCountLast = encCount;
  }
}