#include <Arduino.h>
#include <assert.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>
#include <JsAr.h>

const uint16_t rxPin = 34;
const uint16_t txPin = 2;
uint32_t msg = 0x00FFE01F;
IRrecv irrecv(rxPin, 1024, 50, true);
IRsend irsend(txPin); 
decode_results results; 

// This section of code runs only once at start-up.
void setup() {
  Serial.begin(115200);
  JsAr.begin();
  JsAr.enableIrRx();
  JsAr.enableIrTx();
  irrecv.enableIRIn();
  irsend.begin();
}

// The repeating section of the code
void loop() {
  Serial.println("Sending NEC " + String(msg, HEX) + " ...");
  irsend.sendNEC(msg);
  delay(1000);
  Serial.println("Receiving ...");
  if (irrecv.decode(&results)) {
    Serial.print(resultToHumanReadableBasic(&results));
    Serial.println(resultToSourceCode(&results));
    Serial.println();
    yield();
  }
}
