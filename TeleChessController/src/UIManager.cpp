#include "UIManager.h"

#include <res/qw_fnt_5x7.h>
#include <SparkFun_Qwiic_OLED.h>
#include "config.h"
#include "Rotaryencoder.h"
#include <string.h>

String MAIN_MENU[] = {"Network", "Value", "message"};
String MESSAGE_SUBMENU[] = {"Hi", "Move", "Dunno", "Test", "Taart", "Back"};
String NETWORK_SUBMENU[] = {"Connect", "Discon", "Back"};

UIManager::UIManager(QwiicMicroOLED* display, RotaryEncoder* encoder, WiFiClient* client, String* receiveBuffer, String* sendBuffer)
{
  this->display = display;
  this->encoder = encoder;
  this->client = client;
  this->receiveBuffer = receiveBuffer;
  this->sendBuffer = sendBuffer;
  this->state = MainMenu;
}


void UIManager::PrintValToScreen(int val)
{
  char count[20];
  String nr = String(itoa(val, count, 10));

  display->rectangleFill(display->getHeight() / 2 - 8, 16, display->getHeight() - 16, 16);

  int x0 = (display->getWidth() - QW_FONT_5X7.width * nr.length()) / 2;

  int y0 = (display->getHeight() - QW_FONT_5X7.height) / 2;

  display->text(x0, y0, nr, 0);

  display->display();
}

int UIManager::displayMenu(String menuInput[], int menulength, String header = "")
{
  int startPos = encoder->GetCount() % menulength;
  int endPos = ITEMS_PER_SCREEN;

  //display->erase();

  if (menulength < ITEMS_PER_SCREEN)
  {
    endPos = menulength - startPos;
  }

  if ((menulength - startPos) < ITEMS_PER_SCREEN)
  {
    endPos = menulength - startPos;
  }

  display->setCursor(0, 0);
  display->printf("%s", header.c_str());

  int offset = 0;
  if (header != "")
  {
    offset = QW_FONT_5X7.height;
  }

  for (int cnt = 0; cnt < endPos; cnt++)
  {
    if (cnt == 0)
    {
      display->setCursor(0, offset);
      display->print("->");
    }

    display->setCursor(16, (cnt + (header != "")) * QW_FONT_5X7.height);
    display->println(menuInput[cnt + startPos]);
  }

  display->display();

  return startPos;
}

void UIManager::UpdateDisplay()
{
  // update the screen
  //Serial.printf("state: %i\n",state);
  display->erase();
  switch (state)
  {
  case MainMenu:
  {
    String header = "";
    char cHeader[30];
    header.toCharArray(cHeader,30);
    sprintf(cHeader, "Host: %s", client->connected() ? "Con" : "N/A");//todo get network state here
    int selected = displayMenu(MAIN_MENU, MAINMENU_ITEMS_COUNT, cHeader);
    if (encoder->GetSwitchState())
      {
        state = (MenuState)(selected + 1);
        encoder->ResetCount();
      }

    display->text(0,display->getHeight() - QW_FONT_5X7.height, *receiveBuffer, 1); 
    display->display();
  }
    break;
  case ValueEncoder:
  {
    PrintValToScreen(encoder->GetCount());
    if (encoder->GetSwitchState())
    {
//client.printf("Value:%i", encoder->GetCount());
      *sendBuffer = encoder->GetCount();
      encoder->ResetCount();
      state = MainMenu;
    }
  }
    break;

  case MessageSubMenu:
  {
    int subMenuSelected = displayMenu(MESSAGE_SUBMENU, MESSAGE_MENU_ITEMS_COUNT);
    if (encoder->GetSwitchState())
    {
      if (subMenuSelected < MESSAGE_MENU_ITEMS_COUNT - 1)
      {
      *sendBuffer = MESSAGE_SUBMENU[subMenuSelected];
      }
      encoder->ResetCount();
      state = MainMenu;
    }
  }
    break;

  case NetworkSubMenu:
  {
    int subMenuSelected = displayMenu(NETWORK_SUBMENU, NETWORK_MENU_ITEMS_COUNT);
    if (encoder->GetSwitchState())
    {
      if (subMenuSelected == 0 && !client->connected()) //todo fix network control
      {
        connectToHost();
        netState = HostConnected;
      }
      else if (subMenuSelected == 1 && client->connected())
      {
        client->stop();
        netState = NetworkConnected;
      }
      encoder->ResetCount();
      state = MainMenu;
      break;
    }
  }
    default:
      break;
    }
}

void UIManager::PrintLoadAnim(String header)
{
  int x0 = (display->getWidth() - (QW_FONT_5X7.width * 4)) / 2;

  int y0 = (display->getHeight() - (QW_FONT_5X7.height * 2)) / 2;

  display->erase();
  display->text(0, 0, header, 1);

  for (size_t i = 0; i < 3; i++)
  {
    display->text(x0 + (QW_FONT_5X7.width * i), y0, ".", 1);
    display->display();
    delay(250);
  }
}

int UIManager::connectToHost()
{
  while (!client->connect(HOST, PORT))
  {
    this->PrintLoadAnim();
  }
  Serial.println("Connected to server successful!");
  return 1;
}

