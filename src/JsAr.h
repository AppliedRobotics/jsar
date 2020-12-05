#ifndef __JS_AR_H
#define __JS_AR_H

#define ESP_JS_AR (1)

#include "DxlMaster.h"


class JsAr_t
{
private:
	HardwareDynamixelInterface dxl_interface;
	void set8(uint8_t addr, uint8_t val);
	void set16(uint8_t addr, uint16_t val);
	uint8_t get8(uint8_t addr);
	uint16_t get16(uint8_t addr);
	int id;
	int last_error;
	uint8_t regs[255];
public:
	JsAr_t();
	int  begin(int id = 250);

    void enableEthernet();
    void disableEthernet();

    void enableI2CPins();
    void disableI2CPins();

    void enableCanModule();
    void disableCanModule(); 

    void disableSpiPins(); 
    void enableSpiPins3V3Mode();
    void enableSpiPinsFast3V3Mode();
    void enableSpiPins5VMode();
    void enableSpiPinsFast5VMode();

    void disableSDPort();
    void enableSDPort1BitMode();
    void enableSDPort4BitMode();
    void enableSDPortSpiMode();

    void enableMisoPin();
    void disableMisoPin();

    void enableIrTx();
    void disableIrTx();

    void enableIrRx();
    void disableIrRx();

    void writeMinVoltageToStart(float v);
    void writeMinVoltageToWork(float v);
    float readVoltage();

    void writeLed(uint8_t is_en);

    void replacePin36By25AsOUTPUT();
    void replacePin36By25AsDAC();
    void replacePin35By26AsOUTPUT();
    void replacePin35By26AsDAC();
    void replacePinByExpander(uint8_t pin);
    void expanderDigitalWrite(uint8_t pin, uint8_t value);
    void expanderAnalogWrite(uint8_t pin, uint8_t value);
    void expanderPinMode(uint8_t pin, uint8_t mode);

    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, uint8_t value);
    void analogWrite(uint8_t pin, uint16_t value);
	int digitalRead(uint8_t pin);
	int analogRead(uint8_t pin);

    int t;
};

extern JsAr_t JsAr;

// class JsArReplacer
// {
// public:
// 	static void jsArDigitalWrite(uint8_t pin, uint8_t value)
// 	{
// 		if(JsAr.t)
// 		{
// 			JsAr.expanderDigitalWrite(pin, value);
// 		}
// 		digitalWrite(pin, value);
// 	}

// 	static void analogWrite(uint8_t pin, uint8_t value)
// 	{
// 		if(JsAr.t)
// 		{
// 			JsAr.expanderAnalogWrite(pin, value);
// 		}
// 		digitalWrite(pin, value);
// 	}

// 	static void jsArPinMode(uint8_t pin, uint8_t mode)
// 	{
// 		if(JsAr.t)
// 		{
// 			JsAr.expanderPinMode(pin, mode);
// 		}
// 		pinMode(pin, mode);
// 	}
// };




//#define digitalWrite(_pin_, _value_) JsAr.digitalWrite((_pin_), (_value_))
//#define pinMode(_pin_, _mode_) JsAr.inMode((_pin_), (_mode_))
//#define analogWrite(_pin_, _value_) JsAr.analogWrite((_pin_), (_value_))


/*
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
/*
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
*/
#endif
