#ifndef __ECE353_MCP23017_H__
#define __ECE353_MCP23017_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "TM4C123.h"

#include "driver_defines.h"

#include "gpio_port.h"
#include "i2c.h"

#define MCP23017_DEV_ID			0x27

#define IODIRA    0x00 //DIR reg for LED
#define IODIRB    0x01 //DIR reg for btns

#define   IO_EXPANDER_GPIO_BASE         GPIOA_BASE
#define   IO_EXPANDER_I2C_BASE          I2C1_BASE

#define LED_GPIO_BASE   0x12
#define BTN_GPIO_BASE   0x13


#define PIN0 0 
#define PIN1 1 
#define PIN2 2 
#define PIN3 3 
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7


#define LED0_PIN PIN0
#define LED1_PIN PIN1
#define LED2_PIN PIN2
#define LED3_PIN PIN3
#define LED4_PIN PIN4
#define LED5_PIN PIN5
#define LED6_PIN PIN6
#define LED7_PIN PIN7

#define BTN_UP_PIN 		PIN0
#define BTN_DOWN_PIN 	PIN1
#define BTN_LEFT_PIN 	PIN2
#define BTN_RIGHT_PIN PIN3




bool io_expander_init(uint32_t  i2c_base);
i2c_status_t io_expander_byte_write
( 
  uint32_t  i2c_base,
  uint16_t  address,
  uint8_t   data
);

i2c_status_t io_expander_byte_write
( 
  uint32_t  i2c_base,
  uint16_t  address,
  uint8_t   data
);

i2c_status_t io_expander_byte_read
( 
  uint32_t  i2c_base,
  uint16_t  address,
  uint8_t   *data
);

bool  io_expander_set_pin(uint32_t  i2c_base, uint16_t  address, uint8_t pin_number);

bool  io_expander_clear_pin(uint32_t  i2c_base, uint16_t  address, uint8_t pin_number);

bool  io_expander_read_pin(uint32_t  i2c_base, uint16_t  address, uint8_t pin_number);


#endif
