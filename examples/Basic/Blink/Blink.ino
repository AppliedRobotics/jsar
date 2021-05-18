#include "JsAr.h"

void setup() {
  JsAr.begin();
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, LOW);
  delay(300);
  digitalWrite(2, HIGH);
  delay(300);
}
