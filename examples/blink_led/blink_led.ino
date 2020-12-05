// This is a simple example to test communication with the motors
// It should make all motor led blink once per second
// Default baudrate is 1000000

#include "DxlMaster.h"

const long unsigned int baudrate = 1000000;

// Use broadcast address to affect all connected motors
DynamixelDevice broadcast_device(BROADCAST_ID);

uint8_t led_state = true;

void setup() {
  DxlMaster.begin(1000000);
  delay(100);
}

void loop() {
  broadcast_device.write(DYN_ADDRESS_LED, led_state);
  led_state = !led_state;
  delay(1000);
}
