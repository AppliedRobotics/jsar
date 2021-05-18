#include <JsAr.h>
#include <JsArMotors.h>

void setup()
{
  JsAr.begin();
  JsArMotors.begin();
  JsArMotors.powerWrite(1, 50);
  JsArMotors.powerWrite(2, 100);
}

void loop()
{
}
