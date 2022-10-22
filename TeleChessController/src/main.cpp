// #include <Arduino.h>
#include <stdint.h>
#include <SparkFun_Qwiic_OLED.h>
#include <res/qw_fnt_5x7.h>
#include <Wire.h>
#include <string.h>

#include "config.h"
#include "RotaryEncoder.h"

// interface variables
#define MENU_ITEMS_AMOUNT 3
#define SUBMENU0_ITEMS_AMOUNT 6

char menu[][MAX_ITEM_SIZE] = {"Hello", "Value", "message"};
char subMenu0[][MAX_ITEM_SIZE] = {"Hi", "Move", "Dunno", "Test", "Taart", "Back"};

enum MenuState
{
  MainMenu,
  ValueEncoder,
  MessageSubMenu
};

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

int displayMenu(char menuInput[][MAX_ITEM_SIZE], int menulength)
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

  for (int cnt = 0; cnt <= (endPos - 1); cnt++)
  {
    if (cnt == 0)
    {
      Display.setCursor(0, 0);
      Display.print("->");
    }

    Display.setCursor(16, cnt * QW_FONT_5X7.height);
    Display.println(menuInput[cnt + startPos]);
  }

  Display.display();

  return startPos;
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

  if (!Display.begin(I2C, 0X3D))
  {
    Serial.println("Device Begin Failed");
    while (1)
      ;
  }

  Serial.println("Begin Success");

  Display.setColor(1);
  Display.setFont(QW_FONT_5X7);
  displayMenu(menu, MENU_ITEMS_AMOUNT);
}

MenuState MainMenuHandler(int selected)
{
  switch (selected)
  {
  case 0:
    Serial.println("Hello World");
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

void loop()
{
  // update the screen
  Display.erase();
  switch (state)
  {
  case MainMenu:
    itemSelected = displayMenu(menu, MENU_ITEMS_AMOUNT);
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
      Serial.printf("Value is: %i \n",Encoder.GetCount());
      Encoder.ResetCount();
      state = MainMenu;
    }
      break;
  case MessageSubMenu:
    subMenuSelected = displayMenu(subMenu0, SUBMENU0_ITEMS_AMOUNT);
    if(Encoder.GetSwitchState())
    {
      if(subMenuSelected < 5)
      {
        Serial.printf("Selected message: %s\n",subMenu0[subMenuSelected]);
      }
      Encoder.ResetCount();
      state = MainMenu;
    }
    break;
  default:
    break;
  }
}
