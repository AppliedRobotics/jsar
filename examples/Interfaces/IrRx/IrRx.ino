#include <Arduino.h>
#include <assert.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>
#include <JsAr.h>

const uint16_t recvPin = 34;
IRrecv irrecv(recvPin, 1024, 50, true);
decode_results results; 

// This section of code runs only once at start-up.
void setup() {
  Serial.begin(115200);
  JsAr.begin();
  JsAr.enableIrRx();
  irrecv.enableIRIn();
}

// The repeating section of the code
void loop() {
  if (irrecv.decode(&results)) {
    Serial.print(resultToHumanReadableBasic(&results));
    Serial.println(resultToSourceCode(&results));
    Serial.println();
    yield();
  }
}
