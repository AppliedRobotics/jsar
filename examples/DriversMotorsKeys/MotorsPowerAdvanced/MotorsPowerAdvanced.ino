#include <JsAr.h>
#include <JsArMotors.h>

int16_t power1 = 50, power2 = 100;
unsigned long t = millis();

void setup()
{
  Serial.begin(115200);
  JsAr.begin();
  JsArMotors.begin();
  JsArMotors.encoderModeAB();
}

void loop()
{
  if(millis() - t > 2000)
  {
    t = millis();
    power1 = -power1;
    power2 = -power2;
  }
  
  JsArMotors.powerWrite(1, power1);
  JsArMotors.powerWrite(2, power2);  
  
  int16_t e1, e2, s1, s2, p1, p2;
  JsArMotors.positionReadAll(e1, e2);
  JsArMotors.speedReadAll(s1, s2);
  JsArMotors.powerReadAll(p1, p2);
  Serial.print(String(p1) + "\t" + String(p2) + "\t");
  Serial.print(String(e1) + "\t" + String(e2) + "\t");
  Serial.print(String(s1) + "\t" + String(s2) + "\n");

  delay(100);
}
