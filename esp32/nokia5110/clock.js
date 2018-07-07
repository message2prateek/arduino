var g;

var MONTHS = [
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
];
E.setTimeZone(13);

function draw() {
    g.clear();
    g.setContrast(0.7);
    g.setRotation(2);
    var t = new Date();
    var date = t.getDate() + " " + MONTHS[t.getMonth()] + " " + t.getFullYear();
    var time = t.getHours() + ":" +
        ("0" + t.getMinutes()).substr(-2);
    var secs = ("0" + t.getSeconds()).substr(-2);
    // top left date
    g.setFontBitmap();
    g.drawString(date, 0, 0);
    // middle time
    g.setFontVector(20);
    var timeWidth = g.stringWidth(time);
    g.drawString(time, (g.getWidth() - timeWidth - 12) / 2, 10);
    // seconds over to the right
    g.setFontBitmap();
    g.drawString(secs, (g.getWidth() + timeWidth - 8) / 2, 26);
    // send to LCD
    g.flip();
}

function onInit() {
    clearInterval();
    SPI1.setup({ sck: D18, mosi: D23 });

    g = require('PCD8544').connect(SPI1, D15 /* RS / DC */, D2 /* CS / CE */,
        D0 /*RST*/, function () {
            setInterval(draw, 1000);
        });
}

onInit();