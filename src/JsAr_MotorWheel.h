#ifndef __JS_AR_MOTOR_WHEEL_H
#define __JS_AR_MOTOR_WHEEL_H

#define ESP_JS_AR (1)

#include "JsAr.h"

class JsArWheelMotor_t
{
private:
	int bridge;
public:
    JsArWheelMotor_t(int bridge): bridge(bridge){};
    void        begin();
	void 		set_pid(uint8_t p, uint8_t i, uint8_t d);
	void 		set_punch(uint8_t punch);
	void 		set_speed(uint16_t max_speed);
	uint16_t 	get_present_speed();
	uint16_t 	get_present_position();
	uint16_t 	get_present_load();
};

class JsArJointMotors_t
{
private:
    int bridge;
public:
    void        set_pid(uint8_t p, uint8_t i, uint8_t d);
    void        set_punch(uint8_t punch);
    void        set_position(uint16_t position);
    void        set_max_speed(uint16_t max_speed);
    void        set_max_power(uint16_t max_power);
    void        is_moving();
    uint16_t    get_present_speed();
    uint16_t    get_present_position();
    uint16_t    get_present_load();
};

class JsArPowerKeys_t
{
private:
    int h_bridge;
public:
    void begin(int h_bridge_key);
    void set(uint8_t gnd_0_vcc_1);
};
#endif
