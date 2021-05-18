#include "JsAr.h"

void setup() {
  // put your setup code here, to run once:
  JsAr.begin();
  pinMode(23, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(23, HIGH);
  delay(400);
  digitalWrite(23, LOW);
  delay(400);
}
