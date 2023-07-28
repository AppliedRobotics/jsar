#ifndef __JS_AR_INTERFACE_H
#define __JS_AR_INTERFACE_H

#include "DxlMaster2.h"
#include "DynamixelInterface2.h"
#include "Arduino.h"
#include "regs.h"


class JsArInterface_t : public HardwareDynamixelInterface
{
public:
    JsArInterface_t(HardwareSerial &aSerial): HardwareDynamixelInterface(aSerial), id(250){};
	void set8(uint8_t addr, uint8_t val);
	void set16(uint8_t addr, uint16_t val);
	uint8_t get8(uint8_t addr);
	uint16_t get16(uint8_t addr);
    void set(uint8_t addr, uint8_t size, uint8_t* data);
    void get(uint8_t addr, uint8_t size, uint8_t* data);
	uint8_t id;
	int last_error;
	uint8_t regs[255];
};

extern JsArInterface_t JsArInterface;

#endif
