#ifndef __ECE353_UTILS_H__
#define __ECE353_UTILS_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "driver_defines.h"

#include "TM4C123.h"

#include "ps2.h"
#include "lcd.h"
#include "eeprom.h"
#include "launchpad_io.h"
#include "mcp23017.h"

void wait(int load);

void DisableInterrupts(void);
void EnableInterrupts(void);

void draw_line(uint16_t x0, uint16_t xf, uint16_t y0, uint16_t yf, uint32_t pen_color);

bool sw_is_pressed(uint8_t pin);

bool btn_is_pressed(uint8_t pin);

bool debounce_ps_press_up(void);
bool debounce_ps_press_down(void);
bool debounce_ps_press_left(void);
bool debounce_ps_press_right(void);


void eeprom_write_team_info(char  me[], char  you[], char  groupNum[]);

void eeprom_read_team_info(void);


#endif
