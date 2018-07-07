#include "Arduino.h"

const int dataPin = 8;
const int latchPin = 9;
const int clockPin = 10;

const int hundredthDigit = 2;
const int tensDigit = 3;
const int unitDigit = 4;

const byte numbersI[]  = {
        0b11111100, //0
        0b01100000, //1
        0b11011010, //2
        0b11110010, //3
        0b01100110, //4
        0b10110110, //5
        0b10111110, //6
        0b11100000, //7
        0b11111110, //8
        0b11100110 //9
};

byte* numbersJ = numbersI;
byte* numbersK = numbersI;

void setup(){
        pinMode(dataPin, OUTPUT);
        pinMode(latchPin, OUTPUT);
        pinMode(clockPin, OUTPUT);

        pinMode(hundredthDigit, OUTPUT);
        pinMode(tensDigit, OUTPUT);
        pinMode(unitDigit, OUTPUT);

        digitalWrite(clockPin, LOW);
        digitalWrite(latchPin, LOW);
        Serial.begin(9600);
}


void loop(){

        for (int i = 0; i <= 9; i++) {
                for (int j = 0; j < count; j++) {
                        for (int k = 0; k < count; k++) {
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
        }
}
