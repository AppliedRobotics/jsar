#include "JsAr.h"


#define LED_1 2

int brightStep = 1;
int brightness = 0;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    //JsAr.begin();

    jsArAnalogWriteFrequency(800);
    
}

void loop() {
    // put your main code here, to run repeatedly:
    brightness += brightStep;
    if ( brightness == 0 || brightness == 255 ) {
    brightStep = -brightStep;
    }

    jsArAnalogWrite(LED_1, brightness);

    delay(5);
}