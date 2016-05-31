#ifndef _PINDEFINE_H_
#define _PINDEFINE_H_

#include "gpio_map.h"

/**********************Pin definition**************************/
/* beep */
#define PIN_BEEPER     GPIO_2_2

/* LCD busy */
#define PIN_LCD_BUSY   GPIO_4_28

/* switch */
#define PIN_SW1        GPIO_2_8
#define PIN_SW2        GPIO_2_9
#define PIN_SW3        GPIO_2_7
#define PIN_SW4        GPIO_1_20
#define PIN_SW5        GPIO_1_19
#define PIN_SW6        GPIO_1_18

/* status led */
#define PIN_CH1_PASS_LED  GPIO_0_8
#define PIN_CH1_FAIL_LED  GPIO_0_9

#define PIN_CH2_PASS_LED  GPIO_0_6
#define PIN_CH2_FAIL_LED  GPIO_0_7

#define PIN_CH3_PASS_LED  GPIO_1_9
#define PIN_CH3_FAIL_LED  GPIO_1_10

#define PIN_CH4_PASS_LED  GPIO_1_1
#define PIN_CH4_FAIL_LED  GPIO_1_0

#define PIN_CH5_PASS_LED  GPIO_1_8
#define PIN_CH5_FAIL_LED  GPIO_1_4

#define PIN_CH6_PASS_LED  GPIO_1_31
#define PIN_CH6_FAIL_LED  GPIO_1_30

#define PIN_CH7_PASS_LED  GPIO_0_30
#define PIN_CH7_FAIL_LED  GPIO_0_29

#define PIN_CH8_PASS_LED  GPIO_1_23
#define PIN_CH8_FAIL_LED  GPIO_1_22

/* 4051 */
#define PIN_4051_EN    GPIO_1_24
#define PIN_H0_S1      GPIO_1_25
#define PIN_H0_S2      GPIO_1_26
#define PIN_H0_S3      GPIO_1_28

/* i2c */
#define PIN_SCL        GPIO_0_11
#define PIN_SDA        GPIO_0_10

/* SPI flash */
#define PIN_FLASH_CS   GPIO_2_10
#define PIN_FLASH_SCK  GPIO_0_11
#define PIN_FLASH_MOSI GPIO_0_10
#define PIN_FLASH_MISO GPIO_0_22

#endif

