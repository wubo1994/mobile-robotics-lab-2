#include <Adafruit_RGBLCDShield.h>
#include "MySharpSensor.h"
#include "MyServos.h"
#include "MyEncoders.h"

const char* colorNames[]  = {"RED","GREEN","YELLOW","BLUE","VIOLET","TEAL","WHITE"};
uint8_t     colors[]      = { 0x1 ,  0x2  ,  0x3   ,  0x4 ,  0x5   , 0x6  ,  0x7  };
const char* erraseString  = "       ";
int         option        = 0;

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

float desiredDistance = 5;
float actualDistance = 0;
float distanceError = 0;
float proportion = 0.6;
float initInputSpeed = 0;
float actualInputSpeed = 0;

void setup() {
  // put your setup code here, to run once:
  //pinMode(10,INPUT_PULLUP);
  //pinMode(11,INPUT_PULLUP);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setBacklight(colors[option]);
  lcd.setCursor(2,1);
  //calibrate();
  setSpeeds(0,0);

  while(true)
  {
  delay(200);
  lcd.setCursor(2,1);
  uint8_t buttons = lcd.readButtons();
  
  if(buttons & BUTTON_SELECT)
  {
     for(int i=0;i<10;i++)
     {
        SFRaw[i]=analogRead(1);
     }
     break;
  }
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  takeNewMeasurement(1);
  actualDistance = getCombinedDistance(1);
  distanceError = actualDistance - desiredDistance;
  initInputSpeed = distanceError*proportion;

  if(initInputSpeed<-6)
    actualInputSpeed = -6;
  else if((initInputSpeed>=-6)&&(initInputSpeed<=6))
    actualInputSpeed = initInputSpeed;
  else
    actualInputSpeed = 6;

  setSpeedsIPS(actualInputSpeed,actualInputSpeed);
  delay(20);
}
