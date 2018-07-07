
#include <Arduino.h>
#include <U8g2lib.h>
#include "DHT.h"

DHT dht;
// U8X8_PCD8544_84X48_4W_SW_SPI u8x8(/* clock=*/18, /* data=*/23, /* cs=*/2, /* dc=*/15, /* reset=*/0); // Nokia 5110 Display
U8G2_PCD8544_84X48_1_4W_SW_SPI disp(U8G2_R0, /* clock=*/18, /* data=*/23, /* cs=*/2, /* dc=*/15, /* reset=*/0);

void setup(void)
{
    disp.begin();
    disp.setPowerSave(0);
    Serial.begin(9600);
    Serial.println();
    Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

    dht.setup(17); // data pin 2
}

void loop(void)
{
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
    Serial.print(dht.getStatusString());
    Serial.print("\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Serial.print("\n");

    disp.setContrast(180);
    // disp.drawRFrame(1, 1, 50, 40, 5);
    disp.setFont(u8g2_font_courB08_tf);
    char heading[] = "Weather";
    disp.drawStr(10, 10, heading);
    // disp.drawLine(10, 30, 80, 30);
    disp.drawStr(10, 40, "Temp: ");
    disp.setCursor(20, 50);
    disp.print(temperature);
    // disp.drawStr(6, 15, "Humd: ");
    // disp.setCursor(20, 15);
    // disp.print(humidity);
    disp.sendBuffer();
    delay(3000);
}