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
  JsArKeys.digitalWrite(1, HIGH);
  JsArKeys.digitalWrite(2, LOW);
  JsArKeys.digitalWrite(3, HIGH);
  JsArKeys.digitalWrite(4, LOW);
  delay(1000);

  JsArKeys.digitalWrite(1, LOW);
  JsArKeys.digitalWrite(2, HIGH);
  JsArKeys.digitalWrite(3, LOW);
  JsArKeys.digitalWrite(4, HIGH);
  delay(1000);
}
