#include "Arduino.h"

const int dataPin = 8;
const int latchPin = 9;
const int clockPin = 10;
const byte numbers[] = {
  0b11111100, //0
  0b01100000, //1
  0b11011010, //2
  0b11110010, //3
  0b01100110, //4
  0b10110110, //5
  0b10111110, //6
  0b11100000, //7
  0b11111110, //8
  0b11100110  //9
};

void setup(){
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW);
  Serial.begin(9600);
}

void loop(){

  for (int i = 0; i <= 9; i++) {
        digitalWrite(latchPin, LOW);
        Serial.print(i);
        Serial.print("\n");
        Serial.print(numbers[i], BIN);
        Serial.print("\n");
        Serial.print("\n");
        shiftOut(dataPin, clockPin, LSBFIRST, numbers[i] );
        digitalWrite(latchPin, HIGH);
        delay(500);
    }
}
