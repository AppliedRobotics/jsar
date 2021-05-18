#include <JsAr.h>
#include <JsArKeys.h>

void setup()
{
  Serial.begin(115200);
  JsAr.begin();
  JsArKeys.begin();
}

void loop()
{
  JsArKeys.powerWrite(1, 10); //0..1023
  JsArKeys.powerWrite(2, 20);
  JsArKeys.powerWrite(3, 30);
  JsArKeys.powerWrite(4, 40);
  delay(1000);

  JsArKeys.powerWrite(1, 40);
  JsArKeys.powerWrite(2, 30);
  JsArKeys.powerWrite(3, 20);
  JsArKeys.powerWrite(4, 10);
  delay(1000);
}
