#include <JsAr.h>
#include <JsArMotors.h>

int16_t speed1 = 50, speed2 = 100;
unsigned long t = millis();

void setup()
{
  Serial.begin(115200);
  JsAr.begin();
  JsArMotors.begin();
  JsArMotors.loopPeriodWrite(10);
  JsArMotors.pidWrite(16, 32, 0);
  JsArMotors.encoderModeAB();
  JsArMotors.maxPowerWrite(500);
}

void loop()
{
  if(millis() - t > 2000)
  {
    t = millis();
    speed1 = -speed1;
    speed2 = -speed2;
  }
  
  JsArMotors.speedWrite(1, speed1);
  JsArMotors.speedWrite(2, speed2);  
  
  int16_t e1, e2, s1, s2, p1, p2;
  JsArMotors.positionReadAll(e1, e2);
  JsArMotors.speedReadAll(s1, s2);
  JsArMotors.powerReadAll(p1, p2);
  Serial.print(String(p1) + "\t" + String(p2) + "\t");
  Serial.print(String(e1) + "\t" + String(e2) + "\t");
  Serial.print(String(s1) + "\t" + String(s2) + "\n");

  delay(100);
}
