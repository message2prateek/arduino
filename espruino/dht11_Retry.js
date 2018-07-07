
var dht = require("DHT11").connect(D17);

function onInit() {
    setInterval(function () {
        dht.read(function (a) {
            console.log(JSON.stringify(a));
        });
    }, 3000);
}

onInit();