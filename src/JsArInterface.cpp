#include "JsArInterface.h"
#include "DxlMaster.h"
#include "Arduino.h"

//HardwareDynamixelInterface dxl(Serial);

JsArInterface_t JsArInterface(Serial);

//JsArInterface_t::JsArInterface_t():
//{
//	last_error = 0;
//	id = 250;
//}

void JsArInterface_t::set8(uint8_t addr, uint8_t val)
{
	while(write(id, addr, val))
		;
	regs[addr] = val;
}

void JsArInterface_t::set16(uint8_t addr, uint16_t val)
{
	while(write(id, addr, val))
		;
	regs[addr] = val;
	regs[addr + 1] = val >> 8;
}
uint8_t JsArInterface_t::get8(uint8_t addr)
{
	uint8_t val;
	while(read(id, addr, val))
		;
	regs[addr] = val;
	return val;
}
uint16_t JsArInterface_t::get16(uint8_t addr)
{
	uint16_t val;
	while(read(id, addr, val))
		;
	regs[addr] = val;
	regs[addr + 1] = val >> 8;
	return val;
}

void JsArInterface_t::set(uint8_t addr, uint8_t size, uint8_t* data)
{
	while(write(id,  addr, size, data) != DYN_STATUS_OK)
		;
	memcpy(regs +  addr, data, size);
}

void JsArInterface_t::get(uint8_t addr, uint8_t size, uint8_t* data)
{
	while(read(id, addr, size, data) != DYN_STATUS_OK)
		;
	memcpy(regs +  addr, data, size);
}

/* Default setup 

A0 - 36 - ESP with divider
A1 - 39 - ESP with divider
A2 - 34 - ESP with divider
A3 - 35 - ESP with divider
A4 - 32 - ESP with PullUp
A5 - 33 - ESP with PullUp

D2 - 5 - ESP with PullUp

D3 - 23 - ESP
D4 - 19 - ESP
D5 - 18 - ESP
D6 - 21 -  ESP
D7 - 22 - ESP

D8 - 2 - ESP
D9 - 4 - ESP
D10 - 15 - ESP
D11 - 13 - ESP
D12 - 12 (MISO) - ESP
D13 - 14 - ESP


Extender functions:
ethernet - Disabled
ethernet_rst - High
ir_rx - Disabled
ir_tx - Disabled
can - Disabled
sd - Disabled
miso_pin - Enabled
*/

 /*

36 - ESP (divider), ESP_OUT (pin 25), ESP_DAC (pin 25), ST_ADC, ST_INPUT, ST_INPUT_PULLUP, ST_OUTPUT, ST_OUTPUT_OPEN_DRAIN
39 - ESP (divider), CAN_RX, ST_ADC, ST_INPUT, ST_INPUT_PULLUP, ST_OUTPUT, ST_OUTPUT_OPEN_DRAIN
34 - ESP (divider), IR_RX, ST_ADC, ST_INPUT, ST_INPUT_PULLUP, ST_OUTPUT, ST_OUTPUT_OPEN_DRAIN
35 - ESP (divider), ESP_OUT (pin 26), ESP_DAC (pin 26), ST_ADC, ST_INPUT, ST_INPUT_PULLUP, ST_OUTPUT, ST_OUTPUT_OPEN_DRAIN
32 - ESP (divider), I2C (ESP pull up), ST_ADC, ST_INPUT, ST_INPUT_PULLUP, ST_OUTPUT, ST_OUTPUT_OPEN_DRAIN
33 - ESP (divider), I2C (ESP pull up), ST_ADC, ST_INPUT, ST_INPUT_PULLUP, ST_OUTPUT, ST_OUTPUT_OPEN_DRAIN

5 - ESP (pull up), Dynamixel Dir

23 - ESP (pull up), Ethernet, ST_INPUT, ST_INPUT_PULLUP, ST_OUTPUT, ST_OUTPUT_OPEN_DRAIN, ST_PWM
19 - ESP (pull up), Ethernet, ST_INPUT, ST_INPUT_PULLUP, ST_OUTPUT, ST_OUTPUT_OPEN_DRAIN, ST_PWM
18 - ESP (pull up), Ethernet, ST_INPUT, ST_INPUT_PULLUP, ST_OUTPUT, ST_OUTPUT_OPEN_DRAIN, ST_PWM
21 - ESP (pull up), Ethernet, ST_INPUT, ST_INPUT_PULLUP, ST_OUTPUT, ST_OUTPUT_OPEN_DRAIN, ST_PWM
22 - ESP (pull up), Ethernet, ST_INPUT, ST_INPUT_PULLUP, ST_OUTPUT, ST_OUTPUT_OPEN_DRAIN, ST_PWM

2 - ESP (pull up), CAN_TX, IR_RX, SDJsAr_1BIT/SDJsAr_4BIT
4 - ESP (pull up), SDJsAr_4BIT
15 - ESP (pull_up), SD_SPI/SDJsAr_1BIT/SDJsAr_4BIT, 
13 - ESP (pull up), SD_SPI/SDJsAr_1BIT/SDJsAr_4BIT, SPI_HIGH_SPEED
12 (MISO) - ESP
14 - ESP

 */

/*
A0 - 36
A1 - 39
A2 - 34
A3 - 35
A4 - 32
A5 - 33

D2 - 5
D3 - 23
D4 - 19
D5 - 18
D6 - 1
D7 - 22
D8 - 2
D9 - 4
D10 - 15
D11 - 13
D12 - 12 (MISO)
D13 - 14
*/