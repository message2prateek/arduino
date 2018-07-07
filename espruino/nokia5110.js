/* digitalWrite(D0, 0);
   digitalWrite(D4, 0);
   digitalWrite(D16, 0);
     digitalWrite(D18, 0);
   digitalWrite(D23, 0);
  pinMode(D0, "input_pullup");
   pinMode(D4, "input_pullup");
 pinMode(D16, "input_pullup");
   pinMode(D18, "input_pullup");
   pinMode(D23, "input_pullup");
   */

SPI1.setup({ baud: 1000000, sck:D18, mosi:D23 });
// var ow = new OneWire(B13);

var g /*, temp */;

function onInit() {
  console.log("it begins");
  clearInterval();
 /* pinMode(D25, "input_pullup");
    pinMode(D17, "input_pullup");
    pinMode(D16, "input_pullup");
    */
  digitalWrite(D25, 0);
  digitalWrite(D17, 0);
  digitalWrite(D19, 0);
  pinMode(D18, "input_pullup");
  pinMode(D23, "input_pullup");
  
 // temp = require("DS18B20").connect(ow);
  g = require("PCD8544").connect(SPI1,D25 /*DC*/,D17 /*CE*/,D19 /*RST*/, function() {
    setInterval(onTimer, 500);
  });
}

function onTimer() {
  // Get the temperature
 // var t = temp.getTemp();
  // Round it to the nearest 0.1
 // t = Math.round(t*10)/10;
  // Now draw!
   console.log("timer starts");
  var t = 12;
  g.clear();
  g.setFontBitmap(); // simple 8x8 font
  g.drawString("Temp",2,0);
  g.drawLine(0,10,84,10);
  g.setFontVector(25); // large font
  g.drawString(t, 0, 15);
  g.flip(); // copy this to the screen
}

onInit();