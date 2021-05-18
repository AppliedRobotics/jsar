#include "JsAr.h"

void setup() {
  // put your setup code here, to run once:
  JsAr.begin();
  JsAr.expanderPinMode(23, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  JsAr.analogWrite(23, 200);
  delay(100);
  JsAr.analogWrite(23, 800);
  delay(100);
}
