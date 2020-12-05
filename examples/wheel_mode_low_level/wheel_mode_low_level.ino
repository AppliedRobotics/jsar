#include "DxlMaster.h"

// id of the motor
const uint8_t id = 1;

// speed, between -1023 and 1023
int16_t speed = 512;

// communication baudrate
const long unsigned int baudrate = 1000000;

int16_t makeSpeed(int16_t speed)
{
  if(speed < 0)
  {
    speed = -speed | 1024;
  }
  return speed;
}

DynamixelDevice device(id);

void setup() 
{
  DxlMaster.begin(baudrate);
  delay(100);

  // check if we can communicate with the motor
  // if not, we stop here
  uint8_t status = device.init();
  if(status != DYN_STATUS_OK)
  {
    while(1);
  }
 device.write(DYN_ADDRESS_ENABLE_TORQUE, 1); 
 device.write(DYN_ADDRESS_CW_LIMIT, 0);
 device.write(DYN_ADDRESS_CCW_LIMIT, 0); 
}

void loop() 
{
  device.write(DYN_ADDRESS_GOAL_SPEED, makeSpeed(speed));
  speed = -speed;
  delay(5000);
}
