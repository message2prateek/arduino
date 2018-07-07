var g;
var dht;


function onInit() {
    clearInterval();
    SPI1.setup({ sck: D18, mosi: D23 });

    g = require('PCD8544').connect(SPI1, D15 /* RS / DC */, D2 /* CS / CE */,
        D0 /*RST*/, function () {
            setInterval(draw, 1000);
        });

    dht = require("DHT11").connect(D22);
    setInterval(onTimer, 3000);
}

function onTimer() {
    // Get the temperature
    var t;
    var rh;
    dht.read(function (a) {
        t = a.temp.toString();
        rh = a.rh.toString();
    });
    // Round it to the nearest 0.1
    t = Math.round(t * 10) / 10;
    console.log("Temp = " + t + "  RH = " + rh);
    // Now draw!
    g.clear();
    g.setFontBitmap(); // simple 8x8 font
    g.drawString("Temp", 2, 0);
    g.drawLine(0, 10, 84, 10);
    g.setFontVector(25); // large font
    g.drawString(t, 0, 15);
    g.flip(); // copy this to the screen
};

onInit();