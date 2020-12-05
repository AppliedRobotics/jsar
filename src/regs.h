#ifndef __REGS_H
#define __REGS_H


#define MODEL_NUMBER_L             (0)
#define MODEL_NUMBER_H             (1)
#define FIRMWARE_VERSION           (2)
#define ID                         (3)
#define BAUD_RATE                  (4)
#define RETURN_DELAY_TIME          (5)
#define MIN_VOLTAGE_LIMIT          (12)
#define MIN_VOLTAGE_TO_START       (13)
#define STATUS_RETURN_LEWEL        (16)
#define RESET_REG                  (23)

#define TORQUE_ENABLE              (24)
#define LED                        (25)
#define D_GAIN                     (26)
#define I_GAIN                     (27)
#define P_GAIN                     (28)
#define RESET_ENCODERS             (29)
#define ENCODER_TURN_TICKS		   (30)
#define D3_D7_PULL_UP_ENABLE       (32)
//#define                          (34)
//#define                          (36)
//#define                          (38)
//#define                          (40)

#define PRESENT_VOLTAGE            (42)
#define PRESENT_TEMPERATURE        (43)
#define REGISTRED                  (44)
#define MOVING                     (46)
#define LOCK                       (47)
#define PUNCH                      (48)
#define REAL_TIME_TICK             (50)

#define GOAL_POSITION_1            (60)
#define GOAL_POSITION_2            (62)
#define GOAL_POSITION_3            (64)
#define GOAL_POSITION_4            (66)
#define MOVING_SPEED_1             (68)
#define MOVING_SPEED_2             (70)
#define MOVING_SPEED_3             (72)
#define MOVING_SPEED_4             (74)
#define TORQUE_1                   (76)
#define TORQUE_2                   (78)
#define TORQUE_3                   (80)
#define TORQUE_4                   (82)
#define PRESENT_POSITION_1         (84)
#define PRESENT_POSITION_2         (86)
#define PRESENT_POSITION_3         (88)
#define PRESENT_POSITION_4         (90)
#define PRESENT_SPEED_1            (92)
#define PRESENT_SPEED_2            (94)
#define PRESENT_SPEED_3            (96)
#define PRESENT_SPEED_4            (98)
#define PRESENT_LOAD_1             (100)
#define PRESENT_LOAD_2             (102)
#define PRESENT_LOAD_3             (104)
#define PRESENT_LOAD_4             (106)

#define ETHERNET_ENABLE            (110)
#define ETHERNET_RST               (111)
#define IR_RX_ENABLE               (112)
#define IR_TX_ENABLE               (113)
#define GPIO_PULL_UP_ENABLE        (114)
#define CAN_ENABLE                 (115)
#define I2C_MODE                   (116)
#define SPI_MODE                   (117)
#define SD_MODE                    (118)
#define MOTOR_MODE                 (119)
#define MISO_OUTPUT_EN             (120)

#define A0_MODE        (130)
#define A1_MODE        (131)
#define A2_MODE        (132)
#define A3_MODE        (133)
#define A4_MODE        (134)
#define A5_MODE        (135)
#define D2_MODE        (136)
#define D3_MODE        (137)
#define D4_MODE        (138)
#define D5_MODE        (139)
#define D6_MODE        (140)
#define D7_MODE        (141)
#define D8_MODE        (142)
#define D9_MODE        (143)
#define D10_MODE       (144)
#define D11_MODE       (145)
#define E1A_MODE       (146)
#define E1B_MODE       (147)
#define E2A_MODE       (148)
#define E2B_MODE       (149)

#define A0_OUTPUT_VAL        (150)
#define A1_OUTPUT_VAL        (152)
#define A2_OUTPUT_VAL        (154)
#define A3_OUTPUT_VAL        (156)
#define A4_OUTPUT_VAL        (158)
#define A5_OUTPUT_VAL        (160)
//#define D2_OUTPUT_VAL        (162)
#define D3_OUTPUT_VAL        (164)
#define D4_OUTPUT_VAL        (166)
#define D5_OUTPUT_VAL        (168)
#define D6_OUTPUT_VAL        (170)
#define D7_OUTPUT_VAL        (172)
#define D8_OUTPUT_VAL        (174)
#define D9_OUTPUT_VAL        (176)
//#define D10_OUTPUT_VAL       (178)
#define D11_OUTPUT_VAL       (180)
#define E1A_OUTPUT_VAL       (182)
#define E1B_OUTPUT_VAL       (184)
#define E2A_OUTPUT_VAL       (186)
#define E2B_OUTPUT_VAL       (188)

#define A0_PRESENT_VAL        (190)
#define A1_PRESENT_VAL        (192)
#define A2_PRESENT_VAL        (194)
#define A3_PRESENT_VAL        (196)
#define A4_PRESENT_VAL        (198)
#define A5_PRESENT_VAL        (200)
//#define D2_PRESENT_VAL        (202)
#define D3_PRESENT_VAL        (204)
#define D4_PRESENT_VAL        (206)
#define D5_PRESENT_VAL        (208)
#define D6_PRESENT_VAL        (210)
#define D7_PRESENT_VAL        (212)
#define D8_PRESENT_VAL        (214)
#define D9_PRESENT_VAL        (216)
//#define D10_PRESENT_VAL       (218)
#define D11_PRESENT_VAL       (220)
#define E1A_PRESENT_VAL       (222)
#define E1B_PRESENT_VAL       (224)
#define E2A_PRESENT_VAL       (226)
#define E2B_PRESENT_VAL       (228)


#define SD_MODE_DISABLED (0)
#define SD_MODE_1BIT			(1)
#define SD_MODE_4BIT			(2)
#define SD_MODE_SPI			(3)

#define I2C_MODE_DISABLED   (0)
#define I2C_MODE_3V3        (1)
#define I2C_MODE_5V         (2)

typedef enum
{
	PinMode_DISABLED = 0,
	PinMode_ESP,
	PinMode_ESP_OUT,
	PinMode_ESP_DAC,
	PinMode_ST_ADC,
	PinMode_ST_INPUT,
	PinMode_ST_INPUT_PULLUP,
	PinMode_ST_OUTPUT,
	PinMode_ST_OUTPUT_OPEN_DRAIN,
	PinMode_ST_PWM	
}PinMode_t;

typedef enum
{
	SPI_MODE_DISABLED = 0,
	SPI_MODE_3V3,
	SPI_MODE_3V3_DRV,
	SPI_MODE_5V,
	SPI_MODE_5V_DRV
}SPI_MODE_t;

#endif
