#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

/* pins connented to BJTs for controlling which all of the digits of the 4 digit 7 segment display is ON at a time
   unit digit is connect to pin 4, tens digit is conneted to pin 5 and so on...
 */
const int digits[] = {4, 5, 6, 7};

//pin declaration for the Shift Registor("SN74HC595")
const int dataPin = 8; // also called SER or Ds. It's pin 14 on SN74HC595
const int clockPin = 9; // also called SRCLK(Shift Registor Clock) or SHcp (SHift registor clock pin). It's pin 11 on SN74HC595
const int latchPin = 10; //also called RCLK or STcp(STorage clock pin). It's pin 12 on SN74HC595
// const int masterReset = 11; //also called SRCLR(Shift Registor clear or MR. It's pin 10 on SN74HC595

//pin declaration for DHT11 temperatue and humidity sensor
#define DHTPIN  2
#define DHTTYPE           DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t dataDisplayDuration;

struct displayChar {
        char id;
        byte charRepesentation;
} displayChars[15];

/* Numbers to be displayed on the 7 segment display in binary format where each digit represents the state of a LED segment on the display
   i.e. 1= "off" and zero = "on"
   e.g. to display number 1 on the display LEDs a=1 i.e off, b=0 i.e. on, c=0, d=1, e=1, f=1, g=1 and dp=1 Combined it forms binary number 10011111
 */
const byte numbers[] = {
        0b00000011, //0
        0b10011111, //1
        0b00100101, //2
        0b00001101, //3
        0b10011001, //4
        0b01001001, //5
        0b01000001, //6
        0b00011111, //7
        0b00000001, //8
        0b00001001  //9
};

const byte degreeSymbol = 0b00111001;
const byte charC = 0b01100011;
const byte charP = 0b00110001;
const byte charE = 0b01100001;
const byte charR = 0b11110101;

char dhtSensorReading[2];

int numberOfDisplayableCharacters;

void initializeDispalyCharacters(){
        for(int i=0; i<=9; i++) {
                displayChars[i].id = i + '0';
                displayChars[i].charRepesentation= numbers[i];
        }

        displayChars[10].id = 'C';
        displayChars[10].charRepesentation = charC;

        displayChars[11].id = 'P';
        displayChars[11].charRepesentation = charP;

        displayChars[12].id = 'E';
        displayChars[12].charRepesentation = charE;

        //degrees symbol
        displayChars[13].id = 'd';
        displayChars[13].charRepesentation = degreeSymbol;

        displayChars[14].id = 'r';
        displayChars[14].charRepesentation = charR;

        numberOfDisplayableCharacters = sizeof(displayChars) / sizeof(displayChars[0]);
}

void setup() {
//display
        for(int i=0; i<= 3; i++) {
                pinMode(digits[i], OUTPUT);
                digitalWrite(digits[i], LOW);
        }
        initializeDispalyCharacters();

//Shift Registor
        pinMode(dataPin, OUTPUT);
        pinMode(clockPin, OUTPUT);
        pinMode(latchPin, OUTPUT);

//DHT sensor
        dht.begin();
        sensor_t sensor;
        dht.temperature().getSensor(&sensor);
        dht.humidity().getSensor(&sensor);

        dataDisplayDuration = (sensor.min_delay / 1000) + 1000;
}

byte getCharacterRepresentationForDisplay(char characterToDisplay){

        for(int i=0; i < numberOfDisplayableCharacters; i++) {
                if(displayChars[i].id == characterToDisplay) {
                        return displayChars[i].charRepesentation;
                }
        }
}

void printDataOnDisplay(char* charData){

        uint32_t displayUntilMillis = millis() + dataDisplayDuration;
        for(uint32_t j = millis(); j < displayUntilMillis; j=millis()) {
                for(int i = 0; i<= 3; i++) {
                        for(int k =0; k<=3; k++) {
                                digitalWrite(digits[k], LOW);
                        }
                        digitalWrite(latchPin, LOW);
                        shiftOut(dataPin, clockPin, LSBFIRST, getCharacterRepresentationForDisplay(charData[i]));
                        //We need to first shirt the data and then open up the display digit for output to avoid ghosting
                        digitalWrite(digits[i], HIGH);
                        digitalWrite(latchPin, HIGH);
                        delay(5);
                        digitalWrite(digits[i], LOW);
                }
        }
}

void loop() {

        sensors_event_t event;
        char data[4];

        // Get temperature event
        dht.temperature().getEvent(&event);
        if (isnan(event.temperature)) {
                strcpy(data,"Err0");
                printDataOnDisplay(data);
        }
        else {
                itoa(event.temperature, dhtSensorReading, 10);
                strcpy(data,strcat(dhtSensorReading, "dC"));
                printDataOnDisplay(data);
        }

        // Get humidity event
        dht.humidity().getEvent(&event);
        if(isnan(event.relative_humidity)) {
                strcpy(data,"Err0");
                printDataOnDisplay(data);
        }
        else {
                itoa(event.relative_humidity, dhtSensorReading, 10);
                strcpy(data,strcat(dhtSensorReading, "PC"));
                printDataOnDisplay(data);
        }

}
