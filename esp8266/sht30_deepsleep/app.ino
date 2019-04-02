#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WEMOS_SHT3X.h>
#include <ESP8266WiFi.h>

#define OLED_RESET 0 // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

SHT3X sht30(0x45);

void setup()
{
    WiFi.mode(WIFI_AP_STA);
    pinMode(D5, OUTPUT); // Esp8266 D5 is attached to the Vin pin on the OLED, so that we can turn the display off before going to deepsleep

    powerOnDisplay();

    initializeDisplay();
    displaySensorData();
    powerOffDisplay();

    ESP.deepSleep(10000000, WAKE_RF_DISABLED);
    delay(100);
}

void loop()
{
}

void powerOnDisplay()
{
    digitalWrite(D5, HIGH); //turn the display ON
    delay(200);             // introduce a slight delay for display to turn on properly
}

void powerOffDisplay()
{
    digitalWrite(D5, LOW);
}

void initializeDisplay()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // I2C address of the display us 0x3C
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
}

void displaySensorData()
{
    if (sht30.get() == 0)
    {
        display.println("Temp: ");
        display.setTextSize(2);
        display.println(sht30.cTemp);

        display.setTextSize(1);
        display.println("Humid: ");
        display.setTextSize(2);
        display.println(sht30.humidity);
    }
    else
    {
        display.println("Error!");
    }

    display.display();
    delay(5000);
}

void gotoDeepSleep()
{
}