#include "JsAr.h"

void setup() {
  // put your setup code here, to run once:
  JsAr.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  JsAr.expanderWriteLed(1);
  delay(400);
  JsAr.expanderWriteLed(0);
  delay(400);
}
