#include "JsAr.h"


void setup() {
  // put your setup code here, to run once:
  JsAr.begin();
  JsAr.writeMinVoltageToStart(6.5);
  JsAr.writeMinVoltageToWork(6.0);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(JsAr.readVoltage());
}
