// #include <Arduino.h>
#include <stdint.h>
#include <SparkFun_Qwiic_OLED.h>
#include <res/qw_fnt_5x7.h>
#include <Wire.h>
#include <string.h>
#include <WiFi.h>
#include "config.h"
#include "RotaryEncoder.h"
#include "UIManager.h"
#include "ConnectionManager.h"

WiFiClient client;
NetworkState network;

String receiveBuffer;
String sendBuffer;
QwiicMicroOLED display; // Screen
RotaryEncoder encoder = RotaryEncoder(ENC_PIN_A, ENC_PIN_B, ENC_PIN_SW);
UIManager uiManager = UIManager(&display,&encoder,&client,&receiveBuffer,&sendBuffer);

// I2C Wire config

TwoWire I2C = TwoWire(0); // I2C wire object

IRAM_ATTR void PinA() { encoder.CheckPinA(); }

IRAM_ATTR void PinB() { encoder.CheckPinB(); }

IRAM_ATTR void Switch() { encoder.SetSwitch(); }

void printLoadAnim(String header = "")
{

  int x0 = (display.getWidth() - (QW_FONT_5X7.width * 4)) / 2;

  int y0 = (display.getHeight() - (QW_FONT_5X7.height * 2)) / 2;

  display.erase();
  display.text(0, 0, header, 1);

  for (size_t i = 0; i < 3; i++)
  {
    display.text(x0 + (QW_FONT_5X7.width * i), y0, ".", 1);
    display.display();
    delay(250);
  }
}

void setup()
{
  Serial.begin(115200);
  // encoder
  encoder.INIT();

  attachInterrupt(encoder.GetPinA(), PinA, RISING);
  attachInterrupt(encoder.GetPinB(), PinB, RISING);
  attachInterrupt(encoder.GetPinSW(), Switch, RISING);

  I2C.begin(SDA, SCL);

  delay(500);

  while (!display.begin(I2C, 0X3D))
  {
    Serial.println("Device Begin Failed");
    delay(500);
  }
  
  display.setColor(1);
  Serial.println("Begin Success");

  WiFi.begin(NETNAME, PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("...");
    printLoadAnim("Connecting");
  }
  network = NetworkConnected;
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  display.setFont(QW_FONT_5X7);
  uiManager.UpdateDisplay();
}

// int connectToHost()
// {
//   while (!client.connect(HOST, PORT))
//   {
//     printLoadAnim();
//   }
//   Serial.println("Connected to server successful!");
//   return 1;
// }

void loop()
{
  // update the screen
  uiManager.UpdateDisplay();

  if(client.available())
  {
    receiveBuffer = client.readString();
  }
  
  if(client.connected() && !sendBuffer.isEmpty())
  {
    client.println(sendBuffer);
    //Serial.println(sendBuffer);
    sendBuffer.clear();
  }
}
