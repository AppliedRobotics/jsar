#include "JsArInterface.h"
#include "JsArMotors.h"
#include "regs.h"

static void 	set8(uint8_t addr, uint8_t val) 	{JsArInterface.set8(addr, val);}
static void 	set16(uint8_t addr, uint16_t val) 	{JsArInterface.set16(addr, val);}
static uint8_t 	get8(uint8_t addr)					{return JsArInterface.get8(addr);}
static uint16_t get16(uint8_t addr)					{return JsArInterface.get16(addr);}
static void 	set(uint8_t addr, uint8_t size, uint8_t* data){JsArInterface.set(addr, size, data);}
static void 	get(uint8_t addr, uint8_t size, uint8_t* data){JsArInterface.get(addr, size, data);}
static uint8_t* regs = JsArInterface.regs;

JsArMotors_t JsArMotors;

void JsArMotors_t::begin()
{
	set8(DRIVER_MODE, DRIVER_MODE_2_H_BRIDGES);
}

void JsArMotors_t::pidWrite(uint8_t p, uint8_t i, uint8_t d)
{
	set8(PID_P, p);
	set8(PID_I, i);
	set8(PID_D, d);
}

void JsArMotors_t::loopPeriodWrite(uint8_t period_ms)
{
	if(period_ms < 1)
		return;
	set8(CONTROL_PERIOD, period_ms);
}

void JsArMotors_t::encoderModeAB()
{
	set8(ENCODER_MODE, ENCODER_MODE_AB);
}

void JsArMotors_t::encoderModeA()
{
	set8(ENCODER_MODE, ENCODER_MODE_A);
}

void JsArMotors_t::encoderModeARising()
{
	set8(ENCODER_MODE, ENCODER_MODE_A_RISING);
}

void JsArMotors_t::powerWrite(uint8_t motor_n, int16_t val)
{
	if(motor_n != 1 && motor_n != 2)
		return;
	int addr = POWER_3 + motor_n*2 - 2;
	set16(addr, val);
}

void JsArMotors_t::speedWrite(uint8_t motor_n, int16_t val)
{
	if(motor_n != 1 && motor_n != 2)
		return;
	if(regs[MOTOR_CONTROL_MODE] != CONTROL_MODE_SPEED)
		set8(regs[MOTOR_CONTROL_MODE], CONTROL_MODE_SPEED);

	int addr = GOAL_SPEED_1 + motor_n*2 - 2;
	set16(addr, val);
}

int16_t JsArMotors_t::powerRead(uint8_t motor_n)
{
	if(motor_n != 1 && motor_n != 2)
		return 0;
	int addr = POWER_1 + motor_n*2 - 2;
	return get16(addr);
}

int16_t JsArMotors_t::positionRead(uint8_t motor_n)
{
	if(motor_n != 1 && motor_n != 2)
		return 0;
	int addr = PRESENT_POSITION_1 + motor_n*2 - 2;
	return get16(addr);
}

int16_t JsArMotors_t::speedRead(uint8_t motor_n)
{
	if(motor_n != 1 && motor_n != 2)
		return 0;
	int addr = PRESENT_SPEED_1 + motor_n*2 - 2;
	return get16(addr);
}

void JsArMotors_t::powerWriteAll(int16_t power1, int16_t power2)
{
	uint8_t data[4];
	int idx = 0;
	data[idx++] = power1;
	data[idx++] = power1 << 8;
	data[idx++] = power2;
	data[idx++] = power2 << 8;
	set(POWER_1, idx, data);
}

void JsArMotors_t::speedWriteAll(int16_t speed1, int16_t speed2)
{
	if(regs[MOTOR_CONTROL_MODE] != CONTROL_MODE_SPEED)
		set8(regs[MOTOR_CONTROL_MODE], CONTROL_MODE_SPEED);

	uint8_t data[4];
	int idx = 0;
	data[idx++] = speed1;
	data[idx++] = speed1 << 8;
	data[idx++] = speed2;
	data[idx++] = speed2 << 8;
	set(GOAL_SPEED_1, idx, data);
}

void JsArMotors_t::positionReadAll(int16_t &position1, int16_t &position2)
{
	uint8_t data[4];
	get(PRESENT_POSITION_1, sizeof(data), data);
	position1 = data[0] | ((uint16_t)data[1] << 8);
	position2 = data[2] | ((uint16_t)data[3] << 8);
}

void JsArMotors_t::speedReadAll(int16_t &speed1, int16_t &speed2)
{
	uint8_t data[4];
	get(PRESENT_SPEED_1, sizeof(data), data);
	speed1 = data[0] | ((uint16_t)data[1] << 8);
	speed2 = data[2] | ((uint16_t)data[3] << 8);
}


void JsArMotors_t::allRead(int16_t &position1, int16_t &speed1, int16_t &position2, int16_t &speed2)
{
	uint8_t data[12];
	get(PRESENT_POSITION_1, sizeof(data), data);
	position1 = data[0] | ((uint16_t)data[1] << 8);
	position2 = data[2] | ((uint16_t)data[3] << 8);
	speed1 = data[8] | ((uint16_t)data[9] << 8);
	speed2 = data[10] | ((uint16_t)data[11] << 8);
}






















