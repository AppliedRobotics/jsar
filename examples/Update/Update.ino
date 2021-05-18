#include "JsAr.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial.available())
    ;
  int res = JsAr.updateFirmware();
  if(res) 
  {
    Serial.println("Error " + String(res));
  } 
  else 
  {
    Serial.println("Success");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
