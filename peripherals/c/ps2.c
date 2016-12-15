// Copyright (c) 2014-16, Joe Krachey
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright 
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

#include "ps2.h"


volatile uint16_t PS2_X_DATA = 0;
volatile uint16_t PS2_Y_DATA = 0;

volatile bool ALERT_NEW_ADC = false;
/*******************************************************************************
* Function Name: initialize_adc_gpio_pins
********************************************************************************
* Used to initialize the PS2 joystick GPIO pins for both the analog inputs
*
* Configuration Info
*		Fill out relevant information in ps2.h.  ps2.h defines 
*		how various peripherals are physically connected to the board.
*******************************************************************************/
static void initialize_adc_gpio_pins(void)
{
	//Enable desired port in  (RCGCGPIO)
	//Poll he GPIO Peripheral Ready Register (PRGPIO)
	gpio_enable_port(PS2_GPIO_BASE);
	//Configure the pin as an input (DIR)
	gpio_config_enable_input(PS2_GPIO_BASE, PS2_X_DIR_MASK | PS2_Y_DIR_MASK);
	//Configure the pin as an analog input (AMSEL)
	gpio_config_analog_enable(PS2_GPIO_BASE, PS2_X_DIR_MASK | PS2_Y_DIR_MASK);
	//Configure the pin as an alternate function (AFSEL).
	gpio_config_alternate_function(PS2_GPIO_BASE, PS2_X_DIR_MASK | PS2_Y_DIR_MASK);

	
	
}

/*******************************************************************************
* Function Name: ps2_initialize
********************************************************************************
* Initializes the GPIO pins connected to the PS2 Joystick.  It also configures
* ADC0 to use Sample Sequencer #2 to convert a programmable channel number.
*******************************************************************************/
void ps2_initialize(void)
{
	initialize_adc_gpio_pins();
	initialize_adc(PS2_ADC_BASE);
}

/*******************************************************************************
* Function Name: ps2_get_x
********************************************************************************
*Returns the most current reading of the X direction  Only the lower 12-bits
* contain data.
********************************************************************************/
uint16_t ps2_get_x(void)
{
    return PS2_X_DATA;
}

/*******************************************************************************
* Function Name: ps2_get_y
********************************************************************************
* Returns the most current reading of the Y direction.  Only the lower 12-bits
*  contain data.
********************************************************************************/
uint16_t ps2_get_y(void)
{
    return PS2_Y_DATA;
}



#define PRESS_DOWN 	1517 //if <
#define PRESS_UP		3052 //if >

#define PRESS_LEFT 3052 //if > 3052
#define PRESS_RIGHT 1517 // if < 1017

bool ps2_press_up(uint16_t y){
	
	return y > PRESS_UP_THRESH;
}
bool ps2_press_down(uint16_t y){
	
	return y < PRESS_DOWN_THRESH;
}

bool ps2_press_left(uint16_t x){
	
	return x > PRESS_LEFT_THRESH;
}
bool ps2_press_right(uint16_t x){
	
	return x < PRESS_RIGHT_THRESH;
}

