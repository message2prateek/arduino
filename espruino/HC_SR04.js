
SPI1.setup({ sck: D18, mosi: D23 });
 g = require('PCD8544').connect(SPI1,
        D15 /* RS / DC */,
        D2 /* CS / CE */,
        D0 /*RST*/
        );
var sensor = require("HC-SR04").connect(D27,D14,function(dist) {
  console.log(dist.toFixed(2) +" cm away");
  displayReading(dist);
});
setInterval(function() {
  sensor.trigger(); // send pulse
}, 1000);

function displayReading(dist){
    g.setContrast(0.6);
    g.setRotation(2);
    // draw in a vector font
    g.setFontVector(12);
    g.drawString("Distance : " + dist + "cm", 0, 0);
    g.flip();  
}

