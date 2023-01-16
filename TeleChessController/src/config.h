#ifndef CONFIG_H
#define CONFIG_H

//Rotart Encoder
#define ENC_PIN_A 19          // CLK pin
#define ENC_PIN_B 18          // DT pin
#define ENC_PIN_SW 5          // SW pin

//Oled Display I2C
#define SDA 21            // I2C data pin
#define SCL 22            // I2C clock pin

//Menu Config
#define ITEMS_PER_SCREEN 7
#define MAX_ITEM_SIZE 10
#define MAX_MESSAGE_DISPLAY_LENGTH 15

#define MAINMENU_ITEMS_COUNT 3
#define MESSAGE_MENU_ITEMS_COUNT 6
#define NETWORK_MENU_ITEMS_COUNT 3

//Menu layout

//Network 
#define NETNAME "LAPTOP-Mees"
#define PASSWORD "0987654321"

//Server
#define PORT 1100
#define HOST "217.105.47.86"

#endif