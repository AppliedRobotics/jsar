#include "JsAr.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  JsAr.begin();
  pinMode(36, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = JsAr.analogRead(36);
  Serial.println(val);
  delay(100);
}
