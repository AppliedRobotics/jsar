#include "JsAr.h"

void setup() {
  // put your setup code here, to run once:
  JsAr.begin();
  ledcAttachPin(23, 1);
  ledcSetup(1, 12000, 8);
}

void loop() {
  // put your main code here, to run repeatedly:
  ledcWrite(1, 100);
  delay(100);
  ledcWrite(1, 200);
  delay(100);
}
