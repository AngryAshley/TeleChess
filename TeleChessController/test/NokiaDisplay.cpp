#include <Arduino.h>
#include <SPI.h>
#include <stdint.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_PCD8544.h>

#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24L)

/* Useful Macros for getting elapsed time */
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)  
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN) 
#define numberOfHours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)  

#define maxItemSize 10

const int itemsPerScreen = 7;
const int fontSize = 8;


static int pinA = 2; // Our first hardware interrupt pin is digital pin 2
static int pinB = 3; // Our second hardware interrupt pin is digital pin 3
static int enSW = 9;

volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile uint16_t encoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
volatile uint16_t
oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 8 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 8);

//Declare the Menus you need. 
char menu[][maxItemSize] ={"Date","Time","Alarm","Format","Zone","Daylight","BACK"};
// Only 2 sub-menus are shown. You can add as many as you wish.
char subMenu0[][maxItemSize] = {"Date", "Month", "Year", "BACK"};
char subMenu1[][maxItemSize] = {"Hours", "Min", "Secs", "BACK"};


int cnt = 0; 
int itemSelected, subMenuSelected;
int itemsToDisplay=0;
unsigned long startmillis, milliSecs,mins,secs,hour; 
void setup() {

  display.begin();
  pinMode(enSW, INPUT_PULLUP); 
  pinMode(pinA, INPUT_PULLUP); 
  pinMode(pinB, INPUT_PULLUP);
  attachInterrupt(0,PinA,RISING);
  attachInterrupt(1,PinB,RISING); 
  Serial.begin(115200); 
  display.setContrast(100);
  display.display();
  delay(2000);
  display.clearDisplay();  
  //display.setTextSize(fontSize/8);
  display.setTextColor(BLACK);

  startmillis = millis();

}

void loop() {

  //Show time on the default Screen.
  display.setTextSize(2);
  display.clearDisplay();
  display.setCursor(20,16);
  time(millis() / 1000);
  display.display();
  display.setTextSize(fontSize/8);
  
 // Enter the settings menu if select Switch is pressed
 if(digitalRead(enSW)==0){
    while(digitalRead(enSW)==0);//wait till switch is released.
    
    itemSelected = displayMenu(menu, sizeof(menu)/maxItemSize); 
    switch(itemSelected){
        
         case 0: 
                Serial.print("calling submenu");
                subMenuSelected = displayMenu(subMenu0, sizeof(subMenu0)/maxItemSize); 
                break;
  
         case 1: 
                subMenuSelected = displayMenu(subMenu1, sizeof(subMenu1)/maxItemSize); 
                break;

         //you may include other cases as required!        
  
         default: break;       
              
     }


   //if the selected option is BACK, we will go straight to the main menu.  
   if(itemSelected!= 6){
     switch(subMenuSelected){
          // Only case 0 is shown. Also the user input is not saved anywhere, which might be required in real use-case.
          case 0: display.clearDisplay();
                  display.setCursor(0,0);
                  display.println("Date");
                  display.setCursor(28,16);
                  display.println(encoderPos);
                  display.display();
                  
                  while(digitalRead(enSW)){
                        display.setCursor(0,0);
                        display.clearDisplay();
                        display.println("Date");
                  
                        display.setCursor(16,16);
                        display.println(encoderPos);
                        display.display(); 
                  }  

                  while(digitalRead(enSW)==0);
                  break;
          
          default:break;       
         
     }

   }   
    
 }

 
}



// This function accepts the a 2D character array and its length and display it on the screen.
// The function montiers the encoder position and moves the menu up and down.
// It returns the selected menu option to the calling functions
     
int displayMenu(char menuInput[][maxItemSize], int menuLength){
    int curPos,startPos, endPos;
 do{ 
      
            startPos = encoderPos%menuLength;    
            Serial.println("startPos:");
            Serial.println(startPos);
            display.clearDisplay();
      
            endPos = itemsPerScreen;
            
            if(menuLength < itemsPerScreen)
            {
                 endPos = menuLength -startPos;  
            }
      
            if((menuLength-startPos)<itemsPerScreen)
            {
                endPos = menuLength -startPos;
            }

            Serial.print("endPos:");
            Serial.println(endPos);
      
            for(cnt = 0; cnt<=(endPos-1); cnt++){
                if(cnt == 0)
                {
                  display.setCursor(0,0);
                  display.print("->");
                }
                
                display.setCursor(16, cnt*fontSize);
                display.println(menuInput[cnt+startPos]);
                Serial.println(menuInput[cnt+startPos]);   
            }
            
            display.display();
            cnt = 0;

          if(oldEncPos != encoderPos) {
            oldEncPos = encoderPos;   
          }  
 }while(digitalRead(enSW));
 while(digitalRead(enSW)==0); //wait till switch is reseleased 
 return startPos;
}

/*******************************Utility Functions *******************************/
void time(long val){  
int days = elapsedDays(val);
int hours = numberOfHours(val);
int minutes = numberOfMinutes(val);
int seconds = numberOfSeconds(val);

 // digital clock display of current time
// display.print(days,DEC);  
// printDigits(hours);  
 display.print(minutes);
 printDigits(seconds);
 display.println();  
 
}

void printDigits(byte digits){
 // utility function for digital clock display: prints colon and leading 0
 display.print(":");
 if(digits < 10)
   display.print('0');
 display.print(digits,DEC);  
}

void PinA(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
  if(reading == B00001100 && aFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos --; //decrement the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00000100) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  sei(); //restart interrupts
}


void PinB(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values
  if (reading == B00001100 && bFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos ++; //increment the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00001000) aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  sei(); //restart interrupts
}