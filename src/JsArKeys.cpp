#include "JsArInterface.h"
#include "JsArKeys.h"
#include "regs.h"

#define MAX_POWER (1023)

static void 	set8(uint8_t addr, uint8_t val) 	{JsArInterface.set8(addr, val);}
static void 	set16(uint8_t addr, uint16_t val) 	{JsArInterface.set16(addr, val);}
static uint8_t 	get8(uint8_t addr)					{return JsArInterface.get8(addr);}
static uint16_t get16(uint8_t addr)					{return JsArInterface.get16(addr);}
static void 	set(uint8_t addr, uint8_t size, uint8_t* data){JsArInterface.set(addr, size, data);}
static void 	get(uint8_t addr, uint8_t size, uint8_t* data){JsArInterface.get(addr, size, data);}
static uint8_t* regs = JsArInterface.regs;

JsArKeys_t JsArKeys;

void JsArKeys_t::begin()
{
	set8(DRIVER_MODE, DRIVER_MODE_4_KEYS);
}

void JsArKeys_t::pidWrite(uint8_t p, uint8_t i, uint8_t d)
{
	set8(PID_P, p);
	set8(PID_I, i);
	set8(PID_D, d);
}

void JsArKeys_t::loopPeriodWrite(uint8_t period_ms)
{
	if(period_ms < 1)
		return;
	set8(CONTROL_PERIOD, period_ms);
}

void JsArKeys_t::encodersEnable()
{
	set8(ENCODER_MODE, ENCODER_MODE_SINGLE);
}

void JsArKeys_t::maxPowerWrite(uint16_t max_power)
{
	if(max_power > 1023)
		max_power = 1023;
	set16(MAX_POWER_LIMIT, max_power);
}

void JsArKeys_t::digitalWrite(uint8_t key_n, uint8_t is_on)
{
	if( !(1 <= key_n && key_n <= 4))
		return;
	uint16_t val = is_on? MAX_POWER: 0;
	powerWrite(key_n, val);
}

void JsArKeys_t::powerWrite(uint8_t key_n, uint16_t val)
{
	if( !(1 <= key_n && key_n <= 4))
		return;
	if(val > MAX_POWER)
		val = MAX_POWER;
	uint8_t addr;
	switch(key_n)
	{
		case 1: addr = POWER_1; break;
		case 2: addr = POWER_2; break;
		case 3: addr = POWER_3; break;
		case 4: addr = POWER_4; break;
	}
	set16(addr, val);
}

void JsArKeys_t::speedWrite(uint8_t key_n, uint16_t val)
{
	if( !(1 <= key_n && key_n <= 4))
		return;
	if(regs[MOTOR_CONTROL_MODE] != CONTROL_MODE_SPEED_SINGLE)
		set8(MOTOR_CONTROL_MODE, CONTROL_MODE_SPEED_SINGLE);

	uint8_t addr;
	switch(key_n)
	{
		case 1: addr = GOAL_SPEED_1; break;
		case 2: addr = GOAL_SPEED_2; break;
		case 3: addr = GOAL_SPEED_3; break;
		case 4: addr = GOAL_SPEED_4; break;
	}
	set16(addr, val);
}

uint16_t JsArKeys_t::powerRead(uint8_t key_n)
{
	if( !(1 <= key_n && key_n <= 4))
		return 0;
	uint8_t addr;
	switch(key_n)
	{
		case 1: addr = POWER_1; break;
		case 2: addr = POWER_2; break;
		case 3: addr = POWER_3; break;
		case 4: addr = POWER_4; break;
	}
	return get16(addr);
}

uint16_t JsArKeys_t::positionRead(uint8_t key_n)
{
	if( !(1 <= key_n && key_n <= 4))
		return 0;
	uint8_t addr;
	switch(key_n)
	{
		case 1: addr = PRESENT_POSITION_1; break;
		case 2: addr = PRESENT_POSITION_2; break;
		case 3: addr = PRESENT_POSITION_3; break;
		case 4: addr = PRESENT_POSITION_4; break;
	}
	return get16(addr);	
}

uint16_t JsArKeys_t::speedRead(uint8_t key_n)
{
	if( !(1 <= key_n && key_n <= 4))
		return 0;
	uint8_t addr;
	switch(key_n)
	{
		case 1: addr = PRESENT_SPEED_1; break;
		case 2: addr = PRESENT_SPEED_2; break;
		case 3: addr = PRESENT_SPEED_3; break;
		case 4: addr = PRESENT_SPEED_4; break;
	}
	return get16(addr);	
}

void JsArKeys_t::digitalWriteAll(uint8_t val1,  uint8_t val2,  uint8_t val3,  uint8_t val4){}
void JsArKeys_t::powerWriteAll(uint16_t val1,  uint16_t val2,  uint16_t val3,  uint16_t val4){}
void JsArKeys_t::speedWriteAll(uint16_t val1,  uint16_t val2,  uint16_t val3,  uint16_t val4){}
void JsArKeys_t::positionReadAll(uint16_t & val1, uint16_t & val2, uint16_t & val3, uint16_t & val4){}
void JsArKeys_t::speedReadAll(uint16_t & val1, uint16_t & val2, uint16_t & val3, uint16_t & val4){}






















