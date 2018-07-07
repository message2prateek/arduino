let ledBrightness = 0;
let ledPin = D15;
let fadeIn = false;

function fadeLED() {
    if ((ledBrightness <= 0) || (ledBrightness >= 1)) {
        fadeIn = !fadeIn;
    }

    setLedBrightness(fadeIn);

}

function setLedBrightness(fadeIn) {
    if (fadeIn) {
        ledBrightness += 0.01;
    } else {
        ledBrightness -= 0.01;
    }

    analogWrite(ledPin, ledBrightness);
}

setInterval(fadeLED, 10);