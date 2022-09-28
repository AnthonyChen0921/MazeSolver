
#include <M5Stack.h>

#include "FastLED.h"



#define Neopixel_PIN 1

#define NUM_LEDS 7



CRGB leds[NUM_LEDS];

int leftDistance = 50; //medium

int rightDistance = 50; //medium

int driveSpeed = 6000; //positive numbers are FWD. 100 = 1 full revolution
#define lowG 196
#define Bb 233.1
#define C 261.6
#define D 293.6
#define Eb 311.13
#define E 329.6
#define F 349.2
#define G 392
#define Ab 415.3
#define A 440
#define B 493.8
#define highC 523.25

#define NOTHING 0

void setup() {
  M5.begin();
   Serial2.begin(115200, SERIAL_8N1, 16, 17);
     FastLED.addLeds<WS2811,Neopixel_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  FastLED.setBrightness(100);
  M5.Speaker.setVolume(0);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  


if (M5.BtnA.wasPressed()) {
  delay(2000);
  pthread_t thread1, thread2, thread3;

    // make threads
    pthread_create(&thread1, NULL, music,NULL);
    pthread_create(&thread2, NULL, moveBot,NULL);
    pthread_create(&thread3, NULL, openleds,NULL);

    // wait for them to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL); 
    pthread_join(thread3, NULL); 

  
  } 
M5.update();

}


void* moveBot(void* mom){
 
for (int i = 0; i < 4; i++){
  Serial2.printf("$J=G21 G91 X%d Y%d F%d", leftDistance, -rightDistance, driveSpeed);
  Serial2.print("\r\n\r\n");
  delay(800);
  Serial2.printf("$J=G21 G91 X%d Y%d F%d", -leftDistance, rightDistance, driveSpeed);
  Serial2.print("\r\n\r\n");
  delay(800);
}

Serial2.printf("$J=G21 G91 X%d Y%d F%d", leftDistance*8, rightDistance*8, driveSpeed*4);
  Serial2.print("\r\n\r\n");
  delay(1600);
   
for (int i = 0; i < 2; i++){
  Serial2.printf("$J=G21 G91 X%d Y%d F%d", leftDistance, -rightDistance, driveSpeed*4);
  Serial2.print("\r\n\r\n");
  delay(400);
  Serial2.printf("$J=G21 G91 X%d Y%d F%d", -leftDistance, rightDistance, driveSpeed*4);
  Serial2.print("\r\n\r\n");
  delay(400);
}
Serial2.printf("$J=G21 G91 X%d Y%d F%d", leftDistance*8, -rightDistance*8, driveSpeed*4);
  Serial2.print("\r\n\r\n");
  delay(3200);




}
void* music(void* mom){
 
for (int i = 0; i < 2; i++){
playNote(C, 100);
  notePause(100);
  playNote(Eb,100);
  notePause(50);
  playNote(C, 50);
  notePause(50);
  playNote(C, 50);

  playNote(F, 50);
  notePause(50);
  playNote(C, 50);
  notePause(50);
  playNote(Bb,50);
  notePause(50);
  playNote(C, 100);
  notePause(100);
  playNote(G, 100);
  notePause(50);
  playNote(C, 50);
  notePause(50);
  playNote(C, 50);

  playNote(Ab, 50);
  notePause(50);
  playNote(G, 50);
  notePause(50);
  playNote(Eb,50);
  notePause(50);
  playNote(C, 50);
  notePause(50);
  playNote(G,50);
  notePause(50);
  playNote(highC, 50);
  notePause(50);
    playNote(C, 50);
playNote(Bb, 50);
  notePause(50);
  playNote(Bb, 50);
playNote(lowG, 50);
  notePause(50);
  playNote(Eb, 50);
  notePause(50);
  playNote(C, 200);
  notePause(800);
}
  

  
 
  M5.powerOFF();
  
  
}
void notePause(int ms){
M5.Speaker.end();
M5.Speaker.begin();
delay(ms*2);  
}
void playNote(float frq, int ms){
    M5.Speaker.tone(frq, 50);
  delay(ms*2);
}





void* openleds(void* mom){
  while(1){
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
