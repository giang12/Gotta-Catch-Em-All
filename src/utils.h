#ifndef __ECE353_UTILS_H__
#define __ECE353_UTILS_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "driver_defines.h"

#include "TM4C123.h"

#include "eeprom.h"
#include "launchpad_io.h"
#include "mcp23017.h"


bool sw_is_pressed(uint8_t pin);

bool btn_is_pressed(uint8_t pin);

void eeprom_write_team_info(char  me[], char  you[], char  groupNum[]);

void eeprom_read_team_info(void);


#endif
