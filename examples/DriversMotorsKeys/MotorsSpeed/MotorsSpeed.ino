#include <JsAr.h>
#include <JsArMotors.h>

void setup()
{
  JsAr.begin();
  JsArMotors.begin();
  JsArMotors.encoderModeAB();
  JsArMotors.speedWrite(1, 100);
  JsArMotors.speedWrite(2, 200);  
}

void loop()
{
  int16_t pos1, pos2;
  JsArMotors.positionReadAll(pos1, pos2);
  Serial.println(String(pos1) + "\t" + String(pos2));
  delay(100);
}
