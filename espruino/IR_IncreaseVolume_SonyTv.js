let buttonPin = D15;
let receiveIRPin = D0;
let sendIRPin = D5;
let irTransmitterDataPin = D13;
let irTransmitterGrndPin = D12;
let statusLedPin = D2;


let irCode = [
 2.3820400238,
0.5919933319,
0.6136894226,
0.56219100952,
1.22690200805,
0.5829334259,
0.57911872863,
0.61321258544,
0.58388710021,
0.58388710021,
1.21212005615,
0.57578086853,
0.62417984008,
0.57005882263,
0.63204765319,
0.56099891662,
1.21283531188,
0.56409835815,
0.61583518981,
0.60725212097,
0.60486793518,
0.57315826416,
0.62775611877,
0.58507919311,
0.60391426086,
26.30305290222,
2.40111351013,
0.56791305541,
0.60391426086,
0.59604644775,
1.19304656982,
0.6079673767,
0.60105323791,
0.56910514831,
0.58484077453,
0.61607360839,
1.19996070861,
0.60486793518,
0.60200691223,
0.57411193847,
0.59914588928,
0.58579444885,
1.21092796325,
0.58817863464,
0.59413909912,
0.60582160949,
0.59080123901,
0.58627128601,
0.61583518981,
0.57411193847,
0.5989074707,
26.30996704101,
2.375125885,
0.57697296142,
0.60510635375,
0.61082839965,
1.20902061462,
0.55813789367,
0.60296058654,
0.59103965759,
0.59986114501,
0.60820579528,
1.17683410644,
0.59509277343,
0.57888031005,
0.6148815155,
0.60009956359,
0.58889389038,
1.22308731079,
0.5669593811,
0.58197975158,
0.61321258544,
0.60009956359,
0.58674812316,
0.63419342041,
0.5657672882,
0.6251335144];

function onInit() {
  //  startReceivingIRCode();
    setWatch(sendIRCode, buttonPin, { repeat: true, edge: 'rising', debounce: 50 });
}


/* function startReceivingIRCode() {
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

function stopReceivingIRCode() {
  clearWatch(receiveIRCodeWatch);
}
*/

function sendIRCode() {
    digitalWrite(statusLedPin, 1);
 //   stopReceivingIRCode();

    analogWrite(irTransmitterGrndPin, 0.9, { freq: 38000 });
    digitalPulse(irTransmitterDataPin, 1, irCode);
    digitalPulse(irTransmitterDataPin, 1, 0);
    digitalWrite(irTransmitterDataPin, 0);
    digitalWrite(irTransmitterGrndPin, 0);

//    startReceivingIRCode();
    digitalWrite(statusLedPin, 0);
}


onInit();

