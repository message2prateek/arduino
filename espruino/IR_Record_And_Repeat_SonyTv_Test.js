/*
IR Receiver Module
------------------
VCC = 3.3v
GND = GND
Data= D0;

IR Transmitter Module
---------------------
VCC = 3.3v
GND = D12
Data= D13

Push Button = D15
Status LED  = D2

*/


let buttonPin = D15;
let receiveIRPin = D0;// (VCC = 3.3, GND = GND)
let irTransmitterDataPin = D13;
let irTransmitterGrndPin = D12;
let statusLedPin = D2;


let irCode = [];

function onInit() {
    receiveIRCode();
    setWatch(sendIRCode, buttonPin, { repeat: true, edge: 'rising', debounce: 50 });
}


function receiveIRCode() {
    let pulseTime;
    receiveIRCodeWatch = setWatch(function (e) {
            pulseTime = (e.time - e.lastTime) * 1000;
            if (pulseTime < 1000) {
                irCode.push(pulseTime);
                print(pulseTime);
            } else {
                irCode = [];
            }
    }, receiveIRPin, { repeat: true });
}

function sendSingleCodePulse() {
    analogWrite(irTransmitterGrndPin, 0.9, { freq: 38000 });
    digitalPulse(irTransmitterDataPin, 1, irCode);
    digitalPulse(irTransmitterDataPin, 1, 0);
    digitalWrite(irTransmitterDataPin, 0);
    digitalWrite(irTransmitterGrndPin, 0);

}


function sendIRCode() {
    console.log('Sending code');
    digitalWrite(statusLedPin, 1);

    sendSingleCodePulse();

    digitalWrite(statusLedPin, 0);

}


onInit();

