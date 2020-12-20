#ifndef __JS_AR_MOTORS_H
#define __JS_AR_MOTORS_H

class JsArMotors_t
{
public:
    void begin();
    void pidWrite(uint8_t p, uint8_t i, uint8_t d);
    void loopPeriodWrite(uint8_t period_ms);
    void encoderModeAB();
    void encoderModeA();
    void encoderModeARising();
    
    void powerWrite(uint8_t motor_n, int16_t val);
    void speedWrite(uint8_t motor_n, int16_t val);
    int16_t powerRead(uint8_t motor_n);
    int16_t positionRead(uint8_t motor_n);
    int16_t speedRead(uint8_t motor_n);

    void powerWriteAll(int16_t power1, int16_t power2);
    void speedWriteAll(int16_t speed1, int16_t speed2);
    void positionReadAll(int16_t &position1, int16_t &position2);
    void speedReadAll(int16_t &speed1, int16_t &speed2);
    void allRead(int16_t &position1, int16_t &speed1, int16_t &position2, int16_t &speed2);
};

class JsArKeys_t
{
private:
public:
    void begin();
    void pidWrite(uint8_t p, uint8_t i, uint8_t d);
    void loopPeriodWrite(uint8_t period_ms);
    
    void digitalWrite(uint8_t key_n, uint8_t val);
    void powerWrite(uint8_t key_n, uint16_t val);
    void speedWrite(uint8_t key_n, uint16_t val);
    uint16_t positionRead(uint8_t key_n);
    uint16_t speedRead(uint8_t key_n);

    void digitalWriteAll(uint8_t val1,  uint8_t val2,  uint8_t val3,  uint8_t val4);
    void powerWriteAll(uint16_t val1,  uint16_t val2,  uint16_t val3,  uint16_t val4);
    void speedWriteAll(uint16_t val1,  uint16_t val2,  uint16_t val3,  uint16_t val4);
    void positionReadAll(uint16_t & val1, uint16_t & val2, uint16_t & val3, uint16_t & val4);
    void speedReadAll(uint16_t & val1, uint16_t & val2, uint16_t & val3, uint16_t & val4);
};

extern JsArMotors_t JsArMotors;

#endif
