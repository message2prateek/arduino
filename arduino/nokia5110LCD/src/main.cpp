#include <Arduino.h>
#include "U8glib.h"
#include <SPI.h>
#include <Wire.h>

// U8X8_PCD8544_84X48_4W_SW_SPI u8x8(13, 11, 6, 7, 5);
// U8X8_PCD8544_84X48_4W_HW_SPI u8x8(6, 7, 5);

U8GLIB_PCD8544 u8g(8, 4, 7, 5, 6);
//U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(0, 20); 
  // call procedure from base class, http://arduino.cc/en/Serial/Print
  u8g.print("Prateek!");
}


void setup()
{
}


void loop(void) {
  // picture loop
  u8g.setContrast(175);
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(500);
}
