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

#include "main.h"

char individual_1[] = "Student 1: Giang Nguyen";
char individual_2[] = "Student 2: Thomas Linden";
char group[] = "Team Number: 27";


void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}
void EnableInterrupts(void)
{
  __asm {
	    CPSIE  I
  }
}

//*****************************************************************************
//*****************************************************************************
void initialize_hardware(void)
{
	init_serial_debug(true, true);
	
	if(!eeprom_init())
	{
		printf("eeprom_init ERROR \r\n");
	}
		//LCD
	lcd_config_gpio();
	lcd_config_screen();
	
	lp_io_init(); //Configures the GPIO pins connected to the Launchpad LEDs and 2 push buttons
	ps2_initialize();//PS2 Joystick
	
	if(!io_expander_init(IO_EXPANDER_I2C_BASE)){
		printf("fuykk \n\r");
	}else{
		printf("io_expander_init ok \n\r");
	}
	
	timer0_init();
	timer1_init();
	//watchdog_init();
	
}

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	
  
  initialize_hardware();
	
	eeprom_read_team_info();
	
	
  while(1){
		
		if(get_alert_adc()){
			clear_alert_adc();
			if(sw_is_pressed(SW1_PIN)){
				selection_sceen();
				
			}
		}
		
		if(sw_is_pressed(SW2_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("sw2_is_pressed \r\n");
			eeprom_write_team_info(individual_1, individual_2, group);
		}
		
		if(btn_is_pressed(BTN_LEFT_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("LEFT btn_is_pressed \r\n");
		}
		
		if(btn_is_pressed(BTN_RIGHT_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("RIGHT btn_is_pressed \r\n");
		}
		
		if(btn_is_pressed(BTN_UP_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("UP btn_is_pressed \r\n");
		}
		
		if(btn_is_pressed(BTN_DOWN_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("DOWN btn_is_pressed \r\n");
		}

		
		
  };
}
