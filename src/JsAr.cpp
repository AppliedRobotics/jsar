#include "JsAr.h"
#include "regs.h"
#include "DxlMaster.h"

#define _d() Serial.println(__LINE__)

typedef enum
{
	JsAr_A0 = 0, JsAr_A1, JsAr_A2, JsAr_A3, JsAr_A4, JsAr_A5, JsAr_D2, JsAr_D3, JsAr_D4, 
	JsAr_D5, JsAr_D6, JsAr_D7, JsAr_D8, JsAr_D9, JsAr_D10, JsAr_D11, JsAr_D12, JsAr_D13, 
	JsAr_E1A, JsAr_E1B, JsAr_E2A, JsAr_E2B, JsAr_H1, JsAr_H2, JsAr_H3, JsAr_H4, JsArIO_N
}JsArIO_t;


typedef struct
{
	uint8_t mode_reg;
	uint8_t out_reg;
	uint8_t in_reg;
}ReplacerPin_t;

JsAr_t JsAr;

static const ReplacerPin_t rpins[JsAr_D12] = {//JsArIO_N] = {
	[JsAr_A0] = {A0_MODE, A0_OUTPUT_VAL, A0_PRESENT_VAL},
	[JsAr_A1] = {A1_MODE, A1_OUTPUT_VAL, A1_PRESENT_VAL},
	[JsAr_A2] = {A2_MODE, A2_OUTPUT_VAL, A2_PRESENT_VAL},
	[JsAr_A3] = {A3_MODE, A3_OUTPUT_VAL, A3_PRESENT_VAL},
	[JsAr_A4] = {A4_MODE, A4_OUTPUT_VAL, A4_PRESENT_VAL},
	[JsAr_A5] = {A5_MODE, A5_OUTPUT_VAL, A5_PRESENT_VAL},
	{0, 0, 0},
	[JsAr_D3] = {D3_MODE, D3_OUTPUT_VAL, D3_PRESENT_VAL},
	[JsAr_D4] = {D4_MODE, D4_OUTPUT_VAL, D4_PRESENT_VAL},
	[JsAr_D5] = {D5_MODE, D5_OUTPUT_VAL, D5_PRESENT_VAL},
	[JsAr_D6] = {D6_MODE, D6_OUTPUT_VAL, D6_PRESENT_VAL},
	[JsAr_D7] = {D7_MODE, D7_OUTPUT_VAL, D7_PRESENT_VAL},
	[JsAr_D8] = {D8_MODE, D8_OUTPUT_VAL, D8_PRESENT_VAL},
	[JsAr_D9] = {D9_MODE, D9_OUTPUT_VAL, D9_PRESENT_VAL},
	{0, 0, 0},
	[JsAr_D11] = {D11_MODE, D11_OUTPUT_VAL, D11_PRESENT_VAL}
};

static uint8_t get_replacer_pin(uint8_t pin)
{
	switch(pin)
	{
		case 36: return JsAr_A0;
		case 39: return JsAr_A1;
		case 34: return JsAr_A2;
		case 35: return JsAr_A3;
		case 32: return JsAr_A4;
		case 33: return JsAr_A5;
		case 23: return JsAr_D3;
		case 19: return JsAr_D4;
		case 18: return JsAr_D5;
		case 21: return JsAr_D6;
		case 22: return JsAr_D7;
		case 2 : return JsAr_D8;
		case 4 : return JsAr_D9;
		case 13: return JsAr_D11;
	}
	return 0xFF;
}

JsAr_t::JsAr_t(): 	dxl_interface(Serial)
{
	last_error = 0;
}

typedef enum
{
	JsAr_PinMode_DISABLED = 0,
	JsAr_PinMode_ESP,
	JsAr_PinMode_ESP_OUT,
	JsAr_PinMode_ESP_DAC,
	JsAr_PinMode_ST_ADC,
	JsAr_PinMode_ST_INPUT,
	JsAr_PinMode_ST_INPUT_PULLUP,
	JsAr_PinMode_ST_OUTPUT,
	JsAr_PinMode_ST_OUTPUT_OPEN_DRAIN,
	JsAr_PinMode_ST_PWM	
}JsAr_PinMode_t;

int JsAr_t::begin(int id)
{
	delay(100);
	
	delay(100);

	this->id = id;

	dxl_interface.begin(1000000);


	while(dxl_interface.ping(id) != DYN_STATUS_OK)
		;

	Serial.println("hello");

	for(int i = 0; i < 229; i++)
	{
		get8(i);
	}

	set8(ETHERNET_ENABLE, 1);
	set8(ETHERNET_RST, 1);
	set8(GPIO_PULL_UP_ENABLE, 1);
	set8(MISO_OUTPUT_EN, 1);
	set8(D3_D7_PULL_UP_ENABLE, 1);
	set8(SPI_MODE, SPI_MODE_5V);
	set8(I2C_MODE, I2C_MODE_5V);

	for(int i = A0_MODE; i <= D11_MODE; i++)
	{
		set8(i, PinMode_ESP);
	}

	for(int i = E1A_MODE; i <= E2B_MODE; i++)
	{
		set8(i, PinMode_ST_INPUT);
	}
	
	delay(100);
}

void JsAr_t::set8(uint8_t addr, uint8_t val)
{
	while(dxl_interface.write(id, addr, val))
		;
	regs[addr] = val;
}

void JsAr_t::set16(uint8_t addr, uint16_t val)
{
	while(dxl_interface.write(id, addr, val))
		;
	regs[addr] = val;
	regs[addr + 1] = val >> 8;
}
uint8_t JsAr_t::get8(uint8_t addr)
{
	uint8_t val;
	while(dxl_interface.read(id, addr, val))
		;
	regs[addr] = val;
	return val;
}
uint16_t JsAr_t::get16(uint8_t addr)
{
	uint16_t val;
	while(dxl_interface.read(id, addr, val))
		;
	regs[addr] = val;
	regs[addr + 1] = val >> 8;
	return val;
}

void JsAr_t::enableEthernet() 			{set8(ETHERNET_ENABLE, 1); set8(ETHERNET_RST, 0);}
void JsAr_t::disableEthernet() 			{set8(ETHERNET_RST, 1); set8(ETHERNET_ENABLE, 0);}

void JsAr_t::enableI2CPins() 			{set8(I2C_MODE, I2C_MODE_5V);}
void JsAr_t::disableI2CPins() 			{set8(I2C_MODE, I2C_MODE_DISABLED);}

void JsAr_t::enableCanModule() 			{set8(CAN_ENABLE, 1);}
void JsAr_t::disableCanModule() 		{set8(CAN_ENABLE, 0);} 

void JsAr_t::disableSpiPins() 			{set8(SPI_MODE, SPI_MODE_DISABLED);} 
void JsAr_t::enableSpiPins3V3Mode() 	{set8(SPI_MODE, SPI_MODE_3V3);}
void JsAr_t::enableSpiPinsFast3V3Mode() {set8(SPI_MODE, SPI_MODE_3V3_DRV);}
void JsAr_t::enableSpiPins5VMode() 		{set8(SPI_MODE, SPI_MODE_5V);}
void JsAr_t::enableSpiPinsFast5VMode() 	{set8(SPI_MODE, SPI_MODE_5V_DRV);}

void JsAr_t::disableSDPort() 			{set8(SD_MODE, SD_MODE_DISABLED);}
void JsAr_t::enableSDPort1BitMode() 	{set8(SD_MODE, SD_MODE_1BIT);}
void JsAr_t::enableSDPort4BitMode() 	{set8(SD_MODE, SD_MODE_4BIT);}
void JsAr_t::enableSDPortSpiMode() 		{set8(SD_MODE, SD_MODE_SPI);}

void JsAr_t::enableMisoPin() 			{set8(MISO_OUTPUT_EN, 1);}
void JsAr_t::disableMisoPin() 			{set8(MISO_OUTPUT_EN, 0);}

void JsAr_t::enableIrTx() 				{set8(IR_TX_ENABLE, 1);}
void JsAr_t::disableIrTx() 				{set8(IR_TX_ENABLE, 0);}

void JsAr_t::enableIrRx() 				{set8(IR_RX_ENABLE, 1);}
void JsAr_t::disableIrRx() 				{set8(IR_RX_ENABLE, 0);}

void JsAr_t::writeMinVoltageToStart(float v)
										{set8(MIN_VOLTAGE_TO_START, (uint8_t)(v*10));}
void JsAr_t::writeMinVoltageToWork(float v)	
										{set8(MIN_VOLTAGE_LIMIT, (uint8_t)(v*10));}

float JsAr_t::readVoltage() 			{return ((float)get8(PRESENT_VOLTAGE))/10;}

void JsAr_t::writeLed(uint8_t is_en) 	{set8(LED, is_en);}

void JsAr_t::pinMode(uint8_t pin, uint8_t mode)
{
	uint8_t rpin_n = get_replacer_pin(pin);
	if(rpin_n == 0xFF)
	{
		::pinMode(pin, mode);
		return;
	}

	ReplacerPin_t rpin = rpins[rpin_n];

	uint8_t old_mode = regs[rpin.mode_reg];
	if(old_mode < PinMode_ST_ADC)
	{
		::pinMode(pin, mode);
		return;
	}
	
	switch(mode)
	{
		case INPUT: set8(rpin.mode_reg, PinMode_ST_INPUT); break;
		case INPUT_PULLUP: set8(rpin.mode_reg, PinMode_ST_INPUT_PULLUP); break;
		case OUTPUT: set8(rpin.mode_reg, PinMode_ST_OUTPUT); Serial.println("hello"); break;
	}
}

void JsAr_t::digitalWrite(uint8_t pin, uint8_t value)
{
	uint8_t rpin_n = get_replacer_pin(pin);
	if(rpin_n == 0xFF)
	{
		::digitalWrite(pin, value);
		return;
	}
	ReplacerPin_t rpin = rpins[rpin_n];

	uint8_t mode = regs[rpin.mode_reg];
	switch(mode)
	{
		case PinMode_DISABLED: 
		case PinMode_ESP: 
			::digitalWrite(pin, value);
			break;
		case PinMode_ESP_OUT: 
			if(pin == 36 || pin == 25)
				::digitalWrite(25, value);
			else if(pin == 35 || pin == 26)
				::digitalWrite(26, value);
			break;
		case PinMode_ST_PWM:
			set8(rpin.mode_reg, PinMode_ST_OUTPUT);
		case PinMode_ST_ADC:
		case PinMode_ST_INPUT:
		case PinMode_ST_INPUT_PULLUP:
		case PinMode_ST_OUTPUT:
		case PinMode_ST_OUTPUT_OPEN_DRAIN:
			set8(rpin.out_reg, value);
			break;
	}
}

void JsAr_t::analogWrite(uint8_t pin, uint16_t value)
{
	uint8_t rpin_n = get_replacer_pin(pin);
	if(rpin_n == 0xFF)
	{
		return;
	}
	ReplacerPin_t rpin = rpins[rpin_n];
	uint8_t mode = regs[rpin.mode_reg];

	switch(mode)
	{
		case PinMode_DISABLED: 
		case PinMode_ESP:
			break;
		case PinMode_ST_OUTPUT:
		case PinMode_ST_OUTPUT_OPEN_DRAIN:
			set8(rpin.mode_reg, PinMode_ST_PWM);
		case PinMode_ST_INPUT:
		case PinMode_ST_INPUT_PULLUP:
		case PinMode_ST_ADC:
		case PinMode_ST_PWM:
			set16(rpin.out_reg, value <= 1024? value: 1024);
			break;
	}
}

int JsAr_t::digitalRead(uint8_t pin)
{
	uint8_t rpin_n = get_replacer_pin(pin);
	if(rpin_n == 0xFF)
		return ::digitalRead(pin);
	ReplacerPin_t rpin = rpins[rpin_n];
	uint8_t mode = regs[rpin.mode_reg];
	if(mode < PinMode_ST_ADC)
		return ::digitalRead(pin);
	if(mode == PinMode_ST_ADC)
		set8(rpin.mode_reg, PinMode_ST_INPUT);
	if(mode == PinMode_ST_ADC || mode == PinMode_ST_INPUT || mode == PinMode_ST_INPUT_PULLUP)
		return get8(rpin.in_reg);
	return 0;
}

int JsAr_t::analogRead(uint8_t pin)
{
	uint8_t rpin_n = get_replacer_pin(pin);
	if(rpin_n == 0xFF)
		return ::analogRead(pin);
	ReplacerPin_t rpin = rpins[rpin_n];
	uint8_t mode = regs[rpin.mode_reg];
	if(mode < PinMode_ST_ADC)
		return ::analogRead(pin);
	if(mode != PinMode_ST_ADC)
	{
		set8(rpin.mode_reg, PinMode_ST_ADC);
		delay(1);
	}
	return get8(rpin.in_reg);
}

void JsAr_t::replacePinByExpander(uint8_t pin)
{
	uint8_t rpin_n = get_replacer_pin(pin);
	if(rpin_n == 0xFF)
		return;
	ReplacerPin_t rpin = rpins[rpin_n];
	set8(rpin.mode_reg, PinMode_ST_INPUT);
	return;
}

void JsAr_t::replacePin36By25AsOUTPUT()
{
	set8(rpins[JsAr_A0].mode_reg, PinMode_ESP_OUT);
}
void JsAr_t::replacePin35By26AsOUTPUT()
{
	set8(rpins[JsAr_A3].mode_reg, PinMode_ESP_OUT);
}
void JsAr_t::replacePin36By25AsDAC()
{
	set8(rpins[JsAr_A0].mode_reg, PinMode_ESP_DAC);
}
void JsAr_t::replacePin35By26AsDAC()
{
	set8(rpins[JsAr_A3].mode_reg, PinMode_ESP_DAC);	
}

/*void 		setup_ir_rx(int is_en);
void 		setup_ir_tx(int is_en);
void 		setup_can(int is_en);
void 		setup_i2c(int is_en);
void 		setup_spi_mode(int mode);
void 		setup_sd_mode(int mode);
void 		setup_miso_pin(int is_en);

void 		pinMode(uint8_t pin, uint8_t mode);
void 		digitalWrite(uint8_t pin, uint8_t val);
int 		digitalRead(uint8_t pin);
void 		analogWrite(uint8_t pin, int val);
};

class JsAr_Motor_Wheel_t
{
private:
	int bridge;
public:
	void 		set_pid(uint8_t p, uint8_t i, uint8_t d);
	void 		set_punch(uint8_t punch);
	void 		set_speed(uint16_t max_speed);
	uint16_t 	get_present_speed();
	uint16_t 	get_present_position();
	uint16_t 	get_present_load();
}

class JsAr_Motor_Joint_t
{
private:
	int bridge;
public:
	void 		set_pid(uint8_t p, uint8_t i, uint8_t d);
	void 		set_punch(uint8_t punch);
	void 		set_position(uint16_t position);
	void 		set_max_speed(uint16_t max_speed);
	void 		set_max_power(uint16_t max_power);
	void 		is_moving();
	uint16_t 	get_present_speed();
	uint16_t 	get_present_position();
	uint16_t 	get_present_load();
}

class JsAr_Power_Key_t
{
private:
	int h_bridge;
public:
	void begin(int h_bridge_key);
	void set(uint8_t gnd_0_vcc_1);
}

#endif
*/

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
