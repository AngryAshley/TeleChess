#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

Adafruit_SSD1306 lcd(128, 64, &Wire, 4);

#define btnUp   12
#define btnOk   14
#define btnDown 27
#define btnBack 26

bool statusBtnUp   = false;
bool statusBtnOk   = false;
bool statusBtnDown = false;
bool statusBtnBack = false;

bool statusAkhirBtnUp   = false;
bool statusAkhirBtnOk   = false;
bool statusAkhirBtnDown = false;
bool statusAkhirBtnBack = false;

bool UP   = false;
bool _OK   = false;
bool DOWN = false;
bool BACK = false;

int halaman  = 1;
int menuItem = 1;

void setup() {
  Serial.begin(115200);
  lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C);//SSD1306_SWITCHCAPVCC parameter name ,0x3C name adress
  lcd.clearDisplay();//erase data on display

  pinMode(btnUp,   INPUT_PULLUP);
  pinMode(btnOk,   INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);
  pinMode(btnBack, INPUT_PULLUP);
}

void loop() {
  tampil();

  statusBtnUp   = digitalRead(btnUp);
  statusBtnOk   = digitalRead(btnOk);
  statusBtnDown = digitalRead(btnDown);
  statusBtnBack = digitalRead(btnBack);

  saatUpDitekan();
  saatOkDitekan();
  saatDownDitekan();
  saatBackDitekan();

  //  untuk button up
  if (UP && halaman == 1) {
    UP = false;
    menuItem --;
    if (menuItem < 1)menuItem = 8;
  }
  //untuk button down
  if (DOWN && halaman == 1) {
    DOWN = false;
    menuItem ++;
    if (menuItem > 8)menuItem = 1;
  }

  //  untuk button ok
  if (OK) {
    _OK = false;
    if (halaman == 1 && menuItem == 1) 
    {
      halaman = 2;
    } 
    else if (halaman == 1 && menuItem == 2) 
    {
      halaman = 3;
    } 
    else if (halaman == 1 && menuItem == 3) 
    {
      halaman = 4;
    } 
    else if (halaman == 1 && menuItem == 4) 
    {
      halaman = 5;
    }
    else if (halaman == 1 && menuItem == 5) 
    {
      halaman = 6;
    }
    else if (halaman == 1 && menuItem == 6) 
    {
      halaman = 7;
    }
    else if (halaman == 1 && menuItem == 8) 
    {
      halaman = 9;
    }
  }

  //  untuk button back
  if (BACK) {
    BACK = false;
    if (halaman == 2 || halaman == 3 || halaman == 4 || halaman == 5 || halaman == 6 || halaman == 7 || halaman == 8 || halaman == 9) 
    {
      halaman = 1;
    }
  }

  Serial.println(menuItem);
  delay(100);
}

//--------------------------------------------------------------------------------
void saatUpDitekan() {
  if (statusBtnUp != statusAkhirBtnUp) {
    if (statusBtnUp == 0) {
      UP = true;
    }
    delay(50);
  }
  statusAkhirBtnUp = statusBtnUp;
}

void saatOkDitekan() {
  if (statusBtnOk != statusAkhirBtnOk) {
    if (statusBtnOk == 0) {
      _OK = true;
    }
    delay(50);
  }
  statusAkhirBtnOk = statusBtnOk;
}

void saatDownDitekan() {
  if (statusBtnDown != statusAkhirBtnDown) {
    if (statusBtnDown == 0) {
      DOWN = true;
    }
    delay(50);
  }
  statusAkhirBtnDown = statusBtnDown;
}

void saatBackDitekan() {
  if (statusBtnBack != statusAkhirBtnBack) {
    if (statusBtnBack == 0) {
      BACK = true;
    }
    delay(50);
  }
  statusAkhirBtnBack = statusBtnBack;
}
//----------------------------------------------------------------------------
//semua yang tampil di lcd ada di fungsi ini
void tampil() 
{
  if (halaman == 1) 
  {
    lcd.clearDisplay();
    lcd.setTextSize(1);
    lcd.setTextColor(WHITE);
    lcd.setCursor(30, 0);
    lcd.print("E-BIKE ");

    if (menuItem == 1) 
    {
      lcd.setCursor(5, 17);
      lcd.setTextColor(WHITE);
      lcd.print("> kecepatan sepeda");
    } 
    else 
    {
      lcd.setCursor(5, 17);
      lcd.setTextColor(WHITE);
      lcd.print("  kecepatan sepeda");
    }

    if (menuItem == 2) 
    {
      lcd.setCursor(5, 27);
      lcd.setTextColor(WHITE);
      lcd.print("> nilai RPM");
    } 
    else 
    {
      lcd.setCursor(5, 27);
      lcd.setTextColor(WHITE);
      lcd.print("  nilai RPM");
    }

    if (menuItem == 3)
    {
      lcd.setCursor(5, 37);
      lcd.setTextColor(WHITE);
      lcd.print("> nilai PWM");
    } 
    else 
    {
      lcd.setCursor(5, 37);
      lcd.setTextColor(WHITE);
      lcd.print("  menuItem 3");
    }

    if (menuItem == 4) 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("> menuItem 4");
    } 
    else 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("  menuItem 4");
    }
    if (menuItem == 5) 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("> menuItem 5");
    } 
    else 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("  menuItem 5");
    }
    if (menuItem == 6) 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("> menuItem 6");
    } 
    else 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("  menuItem 6");
    }
    if (menuItem == 7) 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("> menuItem 7");
    } 
    else 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("  menuItem 7");
    }
    if (menuItem == 8) 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("> menuItem 8");
    } 
    else 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("  menuItem 8");
    }
    if (menuItem == 9) 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("> menuItem 9");
    } 
    else 
    {
      lcd.setCursor(5, 47);
      lcd.setTextColor(WHITE);
      lcd.print("  menuItem 9");
    }

  } 
  else if (halaman == 2) 
  {
    lcd.clearDisplay();
    lcd.setTextSize(2);
    lcd.setTextColor(WHITE);
    lcd.setCursor(25, 25);
    lcd.print("nilai sensor gps module");
  } else if (halaman == 3) {
    lcd.clearDisplay();
    lcd.setTextSize(2);
    lcd.setTextColor(WHITE);
    lcd.setCursor(10, 15);
    lcd.print("try reading sensor");
    lcd.setCursor(30, 35);
    lcd.print("nilai sensor dht22");
  } else if (halaman == 4) {
    lcd.clearDisplay();
    lcd.setTextSize(2);
    lcd.setTextColor(WHITE);
    lcd.setCursor(25, 25);
    lcd.print("nilai sensor bme 280");
  } else if (halaman == 5) {
    lcd.clearDisplay();
    lcd.setTextSize(2);
    lcd.setTextColor(WHITE);
    lcd.setCursor(25, 25);
    lcd.print("hal 5");
  }

  lcd.display();
}