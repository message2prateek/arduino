var g;
var pos = 0;

function draw() {
    g.clear();
    g.setContrast(0.6);
    g.setRotation(2);
    // draw in a vector font
    g.setFontVector(12);
    g.drawString("Hello", 0, 0);
    // draw in a font that changes size over time
    pos += 0.5;
    g.setFontVector(18 + Math.sin(pos) * 4);
    // here we centre the text by finding out how long
    // it is with g.stringWidth first
    g.drawString("World!", 42 - g.stringWidth("World!") / 2, 16);
    // switch back to the small font again
    g.setFontBitmap();
    g.drawString("a tiny font", 25, 40);
    // send the graphics to the display
    g.flip();
}

function onInit() {
    SPI1.setup({ sck: D18, mosi: D23 });

    g = require('PCD8544').connect(SPI1,
        D15 /* RS / DC */,
        D2 /* CS / CE */,
        D0 /*RST*/, function () {
            setInterval(draw, 50);
        });
}

onInit();