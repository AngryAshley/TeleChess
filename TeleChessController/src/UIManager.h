#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SparkFun_Qwiic_OLED.h>
#include <string.h>
#include "config.h"
#include "RotaryEncoder.h"
#include <WiFi.h>

enum MenuState
    {
    MainMenu,
    NetworkSubMenu,
    ValueEncoder,
    MessageSubMenu
    };

enum NetworkState
{
  Disconnected,
  NetworkConnected,
  HostConnected
};

class UIManager
{
private:
    MenuState state;
    NetworkState netState = Disconnected;
    String* receiveBuffer;
    String* sendBuffer;

    RotaryEncoder* encoder;
    QwiicMicroOLED* display;
    WiFiClient* client;
    int displayMenu(String menuInput[], int menulength, String header);

public:
    UIManager(QwiicMicroOLED* display, RotaryEncoder* encoder,WiFiClient* client , String* receiveBuffer, String* sendBuffer);

    void UpdateDisplay();

    void PrintLoadAnim(String header = "");

    void PrintValToScreen(int val);

    int connectToHost();
    
};



#endif