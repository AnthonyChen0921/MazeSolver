#include "FastLED.h"
#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BamBotMotorDriver.h>
#include "Adafruit_MCP23008.h"
#include <M5Stack.h>

#include <ESP32Servo.h>



#define Neopixel_PIN 1
#define NUM_LEDS 7
#define BLYNK_USE_DIRECT_CONNECT
CRGB leds[NUM_LEDS];
char deviceName[] = "LegendaryCar";
char auth[] = "f9057700072143f89520fcc635d535ee";
Adafruit_MCP23008 mcp;


#define SERVO1_PIN 12
#define SERVO2_PIN 19
Servo servo1;
Servo servo2;

void bUpdate();
int bState = 0;
bool f, b, l, r, m, n;



// Button Forward
BLYNK_WRITE(V0){
  if(param.asInt()==1){
    bState = 1;
    f = true;
  } 
  else {
    f = false;
  }
  bUpdate();
}



// Button Backward

BLYNK_WRITE(V1){
  if(param.asInt()==1){
    bState = 2;
    b = true;
  } 
  else {
    b = false;
  }
  bUpdate();
}



// Button Left
BLYNK_WRITE(V2){
  if(param.asInt()==1){
    bState = 3;
    l = true;
  }
  else {
    l = false;
  }
  bUpdate();
}



// Button Right
BLYNK_WRITE(V3){
  if(param.asInt()==1){
    bState = 4;
    r = true;
  } 
  else {
    r = false; 
  }
  bUpdate();
}

BLYNK_WRITE(V4){
  if(param.asInt()==1){
    bState = 5;
    m = true;
  } 
  else {
    m = false; 
  }
  bUpdate();
}
BLYNK_WRITE(V5){
  if(param.asInt()==1){
    bState = 6;
    n = true;
  } 
  else {
    n = false; 
  }
  bUpdate();
}



void bUpdate(){
  if(!(f || b || l || r || m)){
        setDrive(0,0,0);
        M5.update();
        for(int i =0;i<7;i++)
        {
          leds[i] = CRGB(255, 255, 255);
        }
        FastLED.show();
  } else {
    switch(bState){

      case 1:

        // Case Forward

        
        {
          for(int i =0;i<7;i++)
          {
            leds[i] = CRGB(255, 0, 0);
          }
          FastLED.show();
          
          for(int i =10000;i<50000;i += 1000){
          setDrive(i,i,50000);delay(10);}
          M5.update();
          
        }
        break;

      case 2:

        // Case Backward

        setDrive(-50000,-50000,50000);
        M5.update();
        for(int i =0;i<7;i++)
        {
          leds[i] = CRGB(0, 255, 0);
        }
        FastLED.show();
        break;

      case 3:

        // Case Left
        FastLED.clear();
        setDrive(-10000,10000,50000);
        M5.update();
        for(int i =6;i>=0;i--)
        {
          leds[i] = CRGB(109, 238, 241);
        }
        FastLED.show();
        
        break;

      case 4:

        // Case Right
        FastLED.clear();
        setDrive(10000,-10000,50000);
        M5.update();
        for(int i =6;i>=0;i--)
        {
          leds[i] = CRGB(109, 238, 241);
        }
        FastLED.show();
        

    }

  }

}


void setDrive(int speed1, int speed2, int rate) {
  Serial2.printf("SS %6d %6d\r", speed1, speed2);
}



void setup(){
  // Initializes M5Stack and motors
  M5.begin();
  Wire.begin();

  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  FastLED.addLeds<WS2811,Neopixel_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(50);

  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);
  servo1.attach(SERVO1_PIN, 1000, 2000);
  servo2.attach(SERVO2_PIN, 1000, 2000);
  
  // Begins Blynk services.
  Blynk.setDeviceName(deviceName);
  Blynk.begin(auth);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.setTextSize(10);
  M5.Lcd.printf("DON'T  TOUCH  ME");
}

void loop(){

  Blynk.run();

}
