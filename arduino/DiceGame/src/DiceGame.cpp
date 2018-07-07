/*
   This sketch is to simulate a Dice throw.

   There are 6 LEDs which are connected to digital pings 2-7. There is a
   push button connected to digital pin 11

   When tha push button is pressed the game starts and a randow number is
   generated between 1-6.

   Anticipation is build by flasing all the 6 leds in a sequential pattern and
   then a number the result of dice throw is shown by lighting number of LEDs,
   in sequnce, equal to the random number generated.

 */
#include "Arduino.h"
const int BUTTON = 11;
int diceThrow;
const unsigned long LED_FLASH_DURATION = 2000;
unsigned long start;

void setup(){
        Serial.begin(9600);
        //Set the pins connected to LEDs as Output
        for(int i=2; i<8; i++) {
                pinMode(i, OUTPUT);
        }
        //Set the pin connected to push button as input
        pinMode(BUTTON, INPUT);
}

void swithOffAllLEDs(){
        for(int i=2; i<8; i++) {
                digitalWrite(i, LOW);
                delay(10);
        }
}

void revealAnswer(int number){
        //turn on number of LEDS
        for (int i = 0; i < number; i++) {
                digitalWrite(7 - i, HIGH);
        }
}

void flashLEDsInSequentialPattern(){
        start = millis();
        while((millis() - start ) < LED_FLASH_DURATION ) {
                for (int i = 7; i > 1; i--) {
                        digitalWrite(i, HIGH);
                        delay(75);
                        digitalWrite(i, LOW);
                        delay(75);
                }
        }
}

void loop(){
        if(digitalRead(BUTTON) == HIGH) {
                delay(10);
                swithOffAllLEDs();

                //Flash the LEDs for the given time to build Anticipation.
                flashLEDsInSequentialPattern();

                diceThrow = rand()%6 + 1;

                revealAnswer(diceThrow);
        }
}
