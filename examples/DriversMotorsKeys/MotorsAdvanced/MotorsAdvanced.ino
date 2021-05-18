#include <JsAr.h>
#include <JsArMotors.h>

int16_t speed = 1;
uint8_t pid_p = 16, pid_i = 32, pid_d = 0;
uint8_t encoder_mode = 1;

void setup()
{
  Serial.begin(115200);
  JsAr.begin();
  JsArMotors.begin();
  Serial.println("Start!");
  JsArMotors.loopPeriodWrite(10);
  JsArMotors.pidWrite(pid_p, pid_i, pid_d);
  JsArMotors.encoderModeAB();
  JsArMotors.maxPowerWrite(500);
  Serial.println("Start!");
  delay(2000);
}

void loop()
{
  int16_t e1, e2, s1, s2, p1, p2;
  delay(100);
  uint8_t buf[128];
  uint8_t p = 0, pp = 0;
  
  while(Serial.available())
    buf[p++] = Serial.read();
  while(pp < p){
    char c = buf[pp++];
  //char c = Serial.read();
  //Serial.write(c);
  switch(c) {
    case ']': speed += 5; JsArMotors.speedWrite(2, speed); break;
    case '[': speed -= 5; JsArMotors.speedWrite(2, speed); break;
    //case ']': speed += 5; JsArMotors.powerWrite(1, speed); break;
    //case '[': speed -= 5; JsArMotors.powerWrite(1, speed); break;
    case '1': pid_p -= 1; JsArMotors.pidWrite(pid_p, pid_i, pid_d); break;
    case '2': pid_p += 1; JsArMotors.pidWrite(pid_p, pid_i, pid_d); break;
    case '3': pid_i -= 1; JsArMotors.pidWrite(pid_p, pid_i, pid_d); break;
    case '4': pid_i += 1; JsArMotors.pidWrite(pid_p, pid_i, pid_d); break;
    case '5': pid_d -= 1; JsArMotors.pidWrite(pid_p, pid_i, pid_d); break;
    case '6': pid_d += 1; JsArMotors.pidWrite(pid_p, pid_i, pid_d); break;  
    case 'b': JsArMotors.encoderModeAB(); break;
    case 'a': JsArMotors.encoderModeA();  break;
    case 'r': JsArMotors.encoderModeARising(); break;
//    case 's': JsArMotors.encoderModeSingle(); break;
  }
  delay(10); 
  };
  JsArMotors.readAll(e1, s1, e2, s2);
  p1 = JsArMotors.powerRead(2);
  
  Serial.print(String(speed) + "\t" + String(p1) + "\t" );
  Serial.print(String(pid_p) + "\t" + String(pid_i) + "\t" + String(pid_d) + "\t");
  Serial.print(String(e1) + "\t" + String(e2) + "\t");
  Serial.print(String(s1) + "\t" + String(s2) + "\n");

}
