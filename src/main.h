// Copyright (c) 2015-16, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include "TM4C123.h"
#include "driver_defines.h"

#include "utils.h"
#include "game_ui_define.h"
#include "pokemon.h"

#include "wireless_driver.h"
#include "timers.h"
#include "gpio_port.h"
#include "adc.h"
#include "interrupts.h"

#include "serial_debug.h"
#include "launchpad_io.h"
#include "lcd.h"
#include "lcd_images.h"
#include "fonts.h"
#include "ps2.h"
#include "eeprom.h"
#include "mcp23017.h"
#include "ft6x06.h"

uint32_t defense_handler(Pokemon *pkm, Pokemon *opp, Attack *def, Attack *att);
uint32_t attack_handler(Pokemon *pkm, Pokemon *opp, Attack *att, Attack *def);

uint32_t setAttack(uint32_t max_valid_data);
uint32_t setDefense(uint32_t max_valid_data);

bool sendMyMove(uint32_t data);
uint32_t getOpponentMove(uint32_t max_valid_data);
#endif
