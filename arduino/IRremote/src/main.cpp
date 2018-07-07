/*
  Demonstrates how to read and send IR codes using Arduino. The sketch reads the IR code received from a Sony Tv remote
  and sends the read code to the Tv when the user presses a pushbutton.
*/

#include <IRremote.h>

const int IR_RECEIVE_PIN = 11;
const int IR_SEND_PIN = 3;
const int BUTTON_PIN = 12;
const int STATUS_LED = 13;

decode_results results;
IRrecv irrecv(IR_RECEIVE_PIN);
IRsend irsend;
unsigned long receivedCode;
int buttonState;
int previousButtonState = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(STATUS_LED, OUTPUT);
  irrecv.enableIRIn();
}

void sendCode(unsigned long receivedCode)
{
  digitalWrite(STATUS_LED, HIGH);

  //Sony requires the same code to be sent three times
  for (int i = 0; i < 3; i++)
  {
    irsend.sendSony(receivedCode, 12);
    Serial.println(receivedCode, HEX);
    delay(40);
  }

  digitalWrite(STATUS_LED, LOW);
}

void saveReceiveCode()
{
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    receivedCode = results.value;
    irrecv.resume(); // Receive the next value
  }
}

void loop()
{
  buttonState = digitalRead(BUTTON_PIN);
  if (previousButtonState == HIGH && buttonState == LOW)
  {
    Serial.println("Released");
    irrecv.enableIRIn(); // Re-enable receiver
  }

  if (buttonState)
  {
    Serial.println("Pressed, sending");
    sendCode(receivedCode);
    delay(50); // Wait a bit between retransmissions
  }
  else if (irrecv.decode(&results))
  {
    saveReceiveCode();
  }
  previousButtonState = buttonState;
  delay(100);
}
