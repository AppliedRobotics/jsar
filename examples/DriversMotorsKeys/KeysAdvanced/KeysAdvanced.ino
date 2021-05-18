#include <JsAr.h>
#include <JsArKeys.h>

int16_t speed = 0;
uint8_t pid_p = 16, pid_i = 32, pid_d = 0;
uint8_t encoder_mode = 1;

void setup()
{
  Serial.begin(115200);
  JsAr.begin();
  JsArKeys.begin();
  JsArKeys.loopPeriodWrite(10);
  JsArKeys.encodersEnable();
  JsArKeys.pidWrite(pid_p, pid_i, pid_d);
  //JsArKeys.maxPowerWrite(800);
}

void loop()
{
  uint16_t e1, e2, e3, e4, s1, s2, s3, s4, p4;
  delay(100);
  uint8_t buf[128];
  uint8_t p = 0, pp = 0;
  
  while(Serial.available()) {
    buf[p++] = Serial.read();
  }
  while(pp < p) {
    char c = buf[pp++];
    switch(c) {
      case ']': speed += 5; JsArKeys.speedWrite(4, speed); break;
      case '[': speed -= 5; JsArKeys.speedWrite(4, speed); break;
      //case ']': speed += 5; JsArKeys.powerWrite(1, speed); break;
      //case '[': speed -= 5; JsArKeys.powerWrite(1, speed); break;
      case '1': pid_p -= 1; JsArKeys.pidWrite(pid_p, pid_i, pid_d); break;
      case '2': pid_p += 1; JsArKeys.pidWrite(pid_p, pid_i, pid_d); break;
      case '3': pid_i -= 1; JsArKeys.pidWrite(pid_p, pid_i, pid_d); break;
      case '4': pid_i += 1; JsArKeys.pidWrite(pid_p, pid_i, pid_d); break;
      case '5': pid_d -= 1; JsArKeys.pidWrite(pid_p, pid_i, pid_d); break;
      case '6': pid_d += 1; JsArKeys.pidWrite(pid_p, pid_i, pid_d); break;
    }
  };
  e1 = JsArKeys.positionRead(1);
  e2 = JsArKeys.positionRead(2);
  e3 = JsArKeys.positionRead(3);
  e4 = JsArKeys.positionRead(4);
  s1 = JsArKeys.speedRead(1);
  s2 = JsArKeys.speedRead(2);
  s3 = JsArKeys.speedRead(3);
  s4 = JsArKeys.speedRead(4);
  
  p4 = JsArKeys.powerRead(4);
  
  Serial.print(String(speed) + "\t" + String(p4) + "\t" );
  Serial.print(String(pid_p) + "\t" + String(pid_i) + "\t" + String(pid_d) + "\t");
  Serial.print(String(e1) + "\t" + String(e2) + "\t");
  Serial.print(String(e3) + "\t" + String(e4) + "\t");
  Serial.print(String(s1) + "\t" + String(s2) + "\t");
  Serial.print(String(s3) + "\t" + String(s4) + "\n");

}
