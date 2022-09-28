

#include <M5Stack.h>

#include "FastLED.h"



#define Neopixel_PIN 1

#define NUM_LEDS 7



CRGB leds[NUM_LEDS];

int leftDistance = 500; //medium

int rightDistance = 500; //medium

int driveSpeed = 6000; //positive numbers are FWD. 100 = 1 full revolution

#define C 261.6
#define D 293.6
#define E 329.6
#define F 349.2
#define G 392
#define A 440
#define B 493.8
#define NOTHING 0

void setup() {
  M5.begin();
   Serial2.begin(115200, SERIAL_8N1, 16, 17);
     FastLED.addLeds<WS2811,Neopixel_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  FastLED.setBrightness(100);
  

}

void loop() {
if (M5.BtnA.wasPressed()) {
    delay(2000);
    pthread_t thread2, thread3;

    // make threads
    pthread_create(&thread2, NULL, moveBot,NULL);
    pthread_create(&thread3, NULL, openleds,NULL);

    // wait for them to finish
    pthread_join(thread2, NULL); 
    pthread_join(thread3, NULL); 

  
  } 
  M5.update();
}


void* moveBot(void* mom){
  moveforward(500,5000);
  turn(200,450,5000);
  turn(200,450,5000);
  moveforward(-500,5000);
  
}
void* openleds(void* mom){
  for(int i=0;i<6;i++){
    leds[3] = CRGB(100,200,50);
    
    for(int i =0;i<3;i++)
    {
      leds[i] = CRGB(255, 0, 0);
    }
    
delay(800);
    for(int i =4;i<7;i++)
    {
      leds[i] = CRGB(0, 0, 255);
    }
    FastLED.show();

    
    for(int i =0;i<3;i++)
    {
      leds[i] = CRGB(255, 255, 0);
    }
    
     delay(800);
    for(int i =4;i<7;i++)
    {
      leds[i] = CRGB(0, 255, 0);
    }
    FastLED.show();
   
  }
}

void moveforward(int a,int s){
  Serial2.printf("$J=G21 G91 X%d Y%d F%d", a, a, s);
  Serial2.print("\r\n\r\n");
  delay(100);
}
void turn(int a,int b,int s){
  Serial2.printf("$J=G21 G91 X%d Y%d F%d", a, b, s);
  Serial2.print("\r\n\r\n");
  delay(100);
}
