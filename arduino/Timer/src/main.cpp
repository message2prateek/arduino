#include "Arduino.h"

void setup(){
for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop(){
  for(int i=2; i<10; i++){
    digitalWrite(i, HIGH);
    delay(100);
    digitalWrite(i, LOW);
    delay(100);
  }
  for(int i=0; i< 150 ; i++){
    analogWrite(10, i);
    delay(10);
  }
}
