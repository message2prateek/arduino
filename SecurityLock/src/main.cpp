#include "Arduino.h"
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
const char KEYS[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
};


byte ROW_PINS[ROWS] = {9, 8, 7, 6};
byte COL_PINS[COLS] = { 5, 4, 3, 2};
Keypad keypad =  Keypad(makeKeymap(KEYS), ROW_PINS, COL_PINS, ROWS, COLS);

const int RED_LED = 12;
const int GREEN_LED = 11;
const int YELLOW_LED = 10;
const char password[]={'1', '2', '3', '4'};
char key;
// Flag to indicate the char position in the password array
int position =0;
//Flag to indicate if the user entered key combination matches the correct password
bool sercretKeyMatch = true;

//   This method flashes the green led if the user entered passcode is correct to indicate success.
void openLock(bool sercretKeyMatch){
        if(sercretKeyMatch && position != 0) {
                digitalWrite(RED_LED, LOW);
                digitalWrite(GREEN_LED, HIGH);
                delay(2000);
        }
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
}

//   This method provides feedback for a keypress to the user by flashing yellow LED.
void indicateKeyPress(){
        digitalWrite(YELLOW_LED, HIGH);
        delay(100);
        digitalWrite(YELLOW_LED, LOW);
}
void setup(){
        pinMode(RED_LED, OUTPUT);
        pinMode(GREEN_LED, OUTPUT);
        pinMode(YELLOW_LED, OUTPUT);
        //Indicate locked status by turning on Red LED.
        digitalWrite(RED_LED, HIGH);
}

// Resets the position and sercretKeyMatch to the default values
void reset(){
        position =0;
        sercretKeyMatch = true;
}

// checks if the individual key enterd by the user matches char of the correct password at the given position
boolean isEnteredKeyCorrect(char key, int position){
        return key==password[position];
}

void loop(){

        key = keypad.getKey();
        //Check if key is valid
        if(key) {
                indicateKeyPress();

                switch (key) {
                case '*':
                        reset();
                        break;
                case '#':
                        openLock(sercretKeyMatch);
                        reset();
                        break;
                default:
                        if (!isEnteredKeyCorrect(key,position)) {
                                sercretKeyMatch = false;
                        }
                        position++;
                }
        }
}
