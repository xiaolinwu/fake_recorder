#include <Arduino.h>
#include "loop.h"

unsigned long bat_timer;
unsigned long sen_timer;

void setup() {
  pinMode(13, OUTPUT);// put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop() {
 if ( (long)(millis()-bat_timer)>=0){
   bat_timer=millis()+10000;
   battery_loop();
 }
 if ( (long)(millis()-sen_timer)>=0){
   sen_timer=millis()+1000;
   sensor_loop();
 }
 if (!bat_low) recording_loop();
 else if(recording){
   digitalWrite(13, LOW);
   Serial.print("nonrecording bat_low");
   recording=false;
 }
}
