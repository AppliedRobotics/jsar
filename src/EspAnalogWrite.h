#ifndef _ESP_ANALOG_WRITE_H_
#define _ESP_ANALOG_WRITE_H_

#include <Arduino.h>

typedef struct js_analog_write_channel
{
  int8_t pin;
  double frequency;
  uint8_t resolution;
} js_ar_analog_write_channel_t;

int jsArAnalogWriteChannel(uint8_t pin);

void jsArAnalogWriteFrequency(double frequency);
void jsArAnalogWriteFrequency(uint8_t pin, double frequency);

void jsArAnalogWriteResolution(uint8_t resolution);
void jsArAnalogWriteResolution(uint8_t pin, uint8_t resolution);

void jsArAnalogWrite(uint8_t pin, uint32_t value, uint32_t valueMax = 255);

#endif