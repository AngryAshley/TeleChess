// #include <Arduino.h>
#include <stdint.h>
#include <SparkFun_Qwiic_OLED.h>
#include <res/qw_fnt_5x7.h>
#include <Wire.h>
#include <string.h>
#include <WiFi.h>

#include "config.h"
#include "RotaryEncoder.h"

// wifi
const char *ssid = "LAPTOP-Mees";
const char *password = "0987654321";

const int port = 1100;
const char *host = "217.105.47.86";
WiFiClient client;
String IncomingBuffer;

// interface variables
#define MENU_ITEMS_AMOUNT 3
#define SUBMENU_MESSAGE_ITEMS 6
#define SUBMENU_NETWORK_ITEMS 3

char menu[][MAX_ITEM_SIZE] = {"Network", "Value", "message"};
char subMenuMessages[][MAX_ITEM_SIZE] = {"Hi", "Move", "Dunno", "Test", "Taart", "Back"};
char subMenuNetwork[][MAX_ITEM_SIZE] = {"Connect", "Discon", "Back"};

MenuState state = MainMenu;
int itemSelected = 0;
int subMenuSelected;
int ItemsToDisplay = 0;

QwiicMicroOLED Display; // Screen

RotaryEncoder Encoder = RotaryEncoder(ENC_PIN_A, ENC_PIN_B, ENC_PIN_SW);

// I2C Wire config

TwoWire I2C = TwoWire(0); // I2C wire object

IRAM_ATTR void PinA() { Encoder.CheckPinA(); }

IRAM_ATTR void PinB() { Encoder.CheckPinB(); }

IRAM_ATTR void Switch() { Encoder.SetSwitch(); }

void printValToScreen(int val)
{

  char count[20];
  String nr = String(itoa(val, count, 10));

  Display.rectangleFill(Display.getHeight() / 2 - 8, 16, Display.getHeight() - 16, 16);

  int x0 = (Display.getWidth() - QW_FONT_5X7.width * nr.length()) / 2;

  int y0 = (Display.getHeight() - QW_FONT_5X7.height) / 2;

  Display.text(x0, y0, nr, 0);

  Display.display();
}

int displayMenu(char menuInput[][MAX_ITEM_SIZE], int menulength, char header[] = "", bool hasHeader = false)
{
  int startPos = Encoder.GetCount() % menulength;
  int endPos = ITEMS_PER_SCREEN;

  Display.erase();

  if (menulength < ITEMS_PER_SCREEN)
  {
    endPos = menulength - startPos;
  }

  if ((menulength - startPos) < ITEMS_PER_SCREEN)
  {
    endPos = menulength - startPos;
  }
  Display.setCursor(0, 0);
  Display.printf("%s", header);

  int offset = 0;
  if (hasHeader)
  {
    offset = QW_FONT_5X7.height;
  }

  for (int cnt = 0; cnt < endPos; cnt++)
  {
    if (cnt == 0)
    {
      Display.setCursor(0, offset);
      Display.print("->");
    }

    Display.setCursor(16, (cnt + hasHeader) * QW_FONT_5X7.height);
    Display.println(menuInput[cnt + startPos]);
  }

  Display.display();

  return startPos;
}

void printLoadAnim(char header[] = "")
{

  int x0 = (Display.getWidth() - (QW_FONT_5X7.width * 4)) / 2;

  int y0 = (Display.getHeight() - (QW_FONT_5X7.height * 2)) / 2;

  Display.erase();
  Display.text(0, 0, header, 1);

  for (size_t i = 0; i < 3; i++)
  {
    Display.text(x0 + (QW_FONT_5X7.width * i), y0, ".", 1);
    Display.display();
    delay(250);
  }
}

void setup()
{
  Serial.begin(115200);
  // Encoder
  Encoder.INIT();

  attachInterrupt(Encoder.GetPinA(), PinA, RISING);
  attachInterrupt(Encoder.GetPinB(), PinB, RISING);
  attachInterrupt(Encoder.GetPinSW(), Switch, RISING);

  I2C.begin(SDA, SCL);

  delay(500);

  while (!Display.begin(I2C, 0X3D))
  {
    Serial.println("Device Begin Failed");
    delay(500);
  }
  Display.setColor(1);
  Serial.println("Begin Success");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("...");
    printLoadAnim("Connecting");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  Display.setFont(QW_FONT_5X7);
  displayMenu(menu, MENU_ITEMS_AMOUNT, "Host: N/A", true);
}

MenuState MainMenuHandler(int selected)
{
  switch (selected)
  {
  case 0:
    return NetworkSubMenu;
    break;
  case 1:
    return ValueEncoder;
    break;
  case 2:
    return MessageSubMenu;
    break;
  default:
    return MainMenu;
    break;
  }
  return MainMenu;
}

int connectToHost()
{
  while (!client.connect(host, port))
  {
    printLoadAnim();
  }
  Serial.println("Connected to server successful!");
}

void loop()
{
  // update the screen
  Display.erase();
  switch (state)
  {
  case MainMenu:
    char header[15];
    sprintf(header, "Host: %s", client.connected() ? "Con" : "N/A");
    itemSelected = displayMenu(menu, MENU_ITEMS_AMOUNT, header, true);
    char buffer[15];
    IncomingBuffer.toCharArray(buffer,15);
    Display.text(0,Display.getHeight() - QW_FONT_5X7.height,buffer,1);
    Display.display();
    if (Encoder.GetSwitchState())
    {
      state = MainMenuHandler(itemSelected);
      Encoder.ResetCount();
    }
    break;

  case ValueEncoder:
    printValToScreen(Encoder.GetCount());
    if (Encoder.GetSwitchState())
    {
      client.printf("Value:%i", Encoder.GetCount());
      Encoder.ResetCount();
      state = MainMenu;
    }
    break;

  case MessageSubMenu:
    subMenuSelected = displayMenu(subMenuMessages, SUBMENU_MESSAGE_ITEMS);
    if (Encoder.GetSwitchState())
    {
      if (subMenuSelected < 5)
      {
        client.printf("%s", subMenuMessages[subMenuSelected]);
      }
      Encoder.ResetCount();
      state = MainMenu;
    }
    break;

  case NetworkSubMenu:
    subMenuSelected = displayMenu(subMenuNetwork, SUBMENU_NETWORK_ITEMS);
    if (Encoder.GetSwitchState())
    {
      if (subMenuSelected == 0 && !client.connected())
      {
        connectToHost();
      }
      else if (subMenuSelected == 1 && client.connected())
      {
        client.stop();
      }
      Encoder.ResetCount();
      state = MainMenu;
      break;
    default:
      break;
    }
  }

  if(client.available())
  {
    IncomingBuffer = client.readString();
  }
}
