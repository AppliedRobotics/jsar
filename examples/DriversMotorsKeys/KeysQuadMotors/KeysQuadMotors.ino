#include <JsAr.h>
#include <JsArKeys.h>

void setup()
{
  Serial.begin(115200);
  JsAr.begin();
  JsArKeys.begin();
  JsArKeys.encodersEnable();
  JsArKeys.speedWrite(1, 50);
  JsArKeys.speedWrite(2, 100);
  JsArKeys.speedWrite(3, 150);
  JsArKeys.speedWrite(4, 200);
}

void loop()
{
  uint16_t e1, e2, e3, e4;
  e1 = JsArKeys.positionRead(1);
  e2 = JsArKeys.positionRead(2);
  e3 = JsArKeys.positionRead(3);
  e4 = JsArKeys.positionRead(4);
  
  Serial.print(String(e1) + "\t" + String(e2) + "\t");
  Serial.print(String(e3) + "\t" + String(e4) + "\n");
}
