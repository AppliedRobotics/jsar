#include "JsAr.h"

void setup() {
  // put your setup code here, to run once:
  JsAr.begin();
  JsAr.expanderPinMode(23, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  JsAr.expanderDigitalWrite(23, HIGH);
  delay(400);
  JsAr.expanderDigitalWrite(23, LOW);
  delay(400);
}
