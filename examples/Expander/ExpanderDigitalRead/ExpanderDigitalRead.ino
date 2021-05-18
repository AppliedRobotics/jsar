#include "JsAr.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  JsAr.begin();
  JsAr.expanderPinMode(23, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = JsAr.expanderDigitalRead(23);
  Serial.println(val);
  delay(100);
}
