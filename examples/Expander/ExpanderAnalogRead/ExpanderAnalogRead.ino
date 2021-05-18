#include "JsAr.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  JsAr.begin();
  JsAr.expanderPinMode(36, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = JsAr.expanderAnalogRead(36);
  Serial.println(val);
  delay(100);
} 
