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
uint8_t individual_1_id[]      = { 3,5,3,3,2};
uint8_t individual_2_id[]  = { 3,5,3,3,3};

volatile player ME = PLAYER_1;

bool isWirelessGood = false;

extern volatile bool ALERT_10MS; //animination timer flag
extern volatile bool ALERT_NEW_ADC; //ADC flag

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
	
	wireless_init() ? printf("Wireless_init successessfull \n\r") 
									: printf("Wireless_init failed \n\r");
	
	
	eeprom_init() ? printf("Eeprom_init successessfull \n\r") 
								:	printf("Reprom_init failed \n\r");
	

		//LCD
	lcd_config_gpio();
	lcd_config_screen();
	
	ft6x06_init() ? printf("ft6x06_init successessfull \n\r") 
								:	printf("ft6x06_init failed \n\r"); 
	
	lp_io_init(); //Configures the GPIO pins connected to the Launchpad LEDs and 2 push buttons
	ps2_initialize();//PS2 Joystick
	
	io_expander_init(IO_EXPANDER_I2C_BASE)	?	printf("io_expander_init successessfull \n\r") 
																					:	printf("io_expander_init failed \n\r");
	
	
	timer0_init();
	timer1_init();
	//watchdog_init();
	
}

//*****************************************************************************
//*****************************************************************************
int setPokeStruct(Pokemon* pkm);
void init_nonch(Pokemon *pkm, Pokemon *opp, Attack *bite, Attack *obite, 
	Attack *sa, Attack *osa);
int attack_handler(Pokemon *pkm, Pokemon *opp, Attack *att, Attack *def) ;
int defense_handler(Pokemon *pkm, Pokemon *opp, Attack *def, Attack *att); 
char pika[] = P;
char squirt[] = S; 
char charm[] = C;
int isTurn;
Attack SA;                 // Specialty Attack
Attack bite; 							 // Bite
Attack OSA;								 // Opponent's special attack
Attack obite; 						 // Opponent's bite attack 
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int 
main(void)
{
	wireless_com_status_t status;
  int a = 0;
  int b = INT_MAX;
	int isGameEnd; 
	int isPlayerFainted; 
	int isOppFainted; 
	int stat_sent, stat_rec; 
	Pokemon pkm;
  Pokemon opp; 
  
	Attack att;
  Attack def; 
  
	att.charCode = GROWL; 
	att.name = G;
		
  initialize_hardware();
	
	eeprom_read_team_info();
	
	init_nonch(&pkm, &opp, &bite, &obite, &SA, &OSA);  
	
	// welcome_screen();
	
	// selection_screen();
	
	// gets pkm charCode 
	pkm.charCode = CHARMANDER;
	
	// waiting_room(); 
	
	// gets opp charCode
	opp.charCode = SQUIRTLE;
	
	// Set up the structures of the pokemon
	setPokeStruct(&pkm);
  setPokeStruct(&opp);
	
	
	// Turns are set, time to begin game 
  while(!isGameEnd) {
    // Set the pre turn vars 
		att.charCode = -1;
    def.charCode = -1;
    stat_sent = -1; 
    stat_rec = -1; 
    // Update the LEDs
		// update_LEDs(pkm.hp, opp.hp); 
		if(isTurn){	
	    choose_attack_move_screen(&pkm, &opp); 
      while(att.charCode < 0) {
			  // att.charCode = setAttack();  something to get the attack from the buttons
			}				
	    while(def.charCode < 0) {
			  // def.charCode = getDefense(); something to get the defense from comm
			}
			// Send the info to the Attack Handler  
			attack_handler(&pkm, &opp, &att, &def);
		}
		else {
		  choose_defense_move_screen(&pkm, &opp);
		  while(def.charCode < 0) {
			  // def.charCode = setDefense(); something to get the defense from the buttons
			}
			while(att.charCode <0) {
			  // att.charCode = getAttack(); something to get the attack from comm
			}
			// Send the info to the Defense Handler
		  defense_handler(&pkm, &opp, &def, &att);
		}
		
		// Between turns check to see if the game will continue 
		if (pkm.hp <= 0) {
		  isPlayerFainted = 1; 
		}
		while(stat_sent < 0) {
		  // stat_sent = sendStat(isPlayerFainted); send opponent isPlayerFainted var
		}
		while(stat_rec < 0) {
		  // stat_rec = recStat(&isOppFainted); get the opponent's isPlayerFainted var
		}
		if (isPlayerFainted == 1) {
		  game_over_screen(&pkm, &opp, true);
		}
		if (isOppFainted == 1) {
		  game_over_screen(&pkm, &opp, false); 
		}
		// Switch whose turn it is 
		isTurn = !isTurn; 
	}	

	
	
  lcd_clear_screen(LCD_COLOR_BLACK );

  choose_defense_move_screen(&pkm, &opp); 
  
	while(1){
		
		if(ALERT_10MS){
			ALERT_10MS = false;
		}
		if(ALERT_NEW_ADC){
			ALERT_NEW_ADC = false;
			if(sw_is_pressed(SW1_PIN)){
				pokemon_selection_sceen();
				
			}
		}
		
		if(sw_is_pressed(SW2_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("sw2_is_pressed \r\n");
			eeprom_write_team_info(individual_1, individual_2, group);
		}
		
		if(btn_is_pressed(BTN_LEFT_PIN) && isWirelessGood){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("LEFT btn_is_pressed \r\n");
			
			printf("Sending: %d\n\r",a);
          status = wireless_send(true, true, a);
          if(status != NRF24L01_TX_SUCCESS)
          {
            printf("Error Message: %s\n\r",wireless_error_messages[status]);
          }else{
						printf("sent \n\r");
					}
          a++;
		}
		
		if(btn_is_pressed(BTN_RIGHT_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("RIGHT btn_is_pressed \r\n");
			
			printf("Sending: %d\n\r",b);
          status = wireless_send(true, true, b);
          if(status != NRF24L01_TX_SUCCESS)
          {
            printf("Error Message: %s\n\r",wireless_error_messages[status]);
          }else{
						printf("sent \n\r");
					}
          b--;
		}
		
		if(btn_is_pressed(BTN_UP_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("UP btn_is_pressed \r\n");
			
			if(wireless_configure_device(individual_1_id, individual_2_id)){
				printf("Wireless Connect %d to %d successessfull \n\r", individual_1_id, individual_2_id);
				isWirelessGood = true;
			}else{
				printf("Wireless Connect %d to %d failed \n\r", individual_1_id, individual_2_id);
				isWirelessGood = false;
			}
		}
		
		if(btn_is_pressed(BTN_DOWN_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("DOWN btn_is_pressed \r\n");
			
			if(wireless_configure_device(individual_2_id, individual_1_id)){
				printf("Wireless Connect %d to %d successessfull \n\r", individual_2_id, individual_1_id);
				isWirelessGood = true;
			}else{
				printf("Wireless Connect %d to %d failed \n\r", individual_2_id, individual_1_id);
				isWirelessGood = false;
			}
		}

			
		
  };
}

int attack_handler(Pokemon *pkm, Pokemon *opp, Attack *att, Attack *def) {
  // If it's a non-damaging move, then we can just update the structs as necessary
  if (att->charCode == GROWL) {
    growl_heal_move_screen(pkm, opp, att, true);
		bite.power = bite.power + DEF_GROWL; 
    SA.power = SA.power + DEF_GROWL; 
    return 0;
  }
  if (att->charCode == HEAL) {
		growl_heal_move_screen(pkm, opp, att, true);
    pkm->hp = pkm->hp + DEF_HEAL;
    return 0; 
  }
  // If it's a damaging move, we need to see if the opponent counter-struck correctly. 
	// If they correctly counterstruck, inflict half the attack on the attacker
  if (att->charCode == def->charCode) { 
    if (att->charCode == BITE) {
			fail_move_screen(pkm, opp, att,true);
      pkm->hp = pkm->hp - .5*bite.power;
      return 0;
    }
    if (att->charCode == SPECIALTYATTACK) {
      fail_move_screen(pkm, opp, att,true);
			pkm->hp = pkm->hp - .5*SA.power; 
      return 0; 
    }
  }
	else{
  // Otherwise we need to inflict the damage on the opponent -- 
  // If it's just tackle, update local opp.hp
    if (att->charCode == BITE) {
			attack_move_screen(pkm, opp, att);
      opp->hp = opp->hp - bite.power; 
    }
    // If it's the specialty attack, dock points of hp from your pokemon as well,  
    // update local opp.hp
    else {
			attack_move_screen(pkm, opp, att);
      opp->hp = opp->hp - SA.power; 
      pkm->hp = pkm->hp - DEF_RECOIL;
    }
  }
}

int defense_handler(Pokemon *pkm, Pokemon *opp, Attack *def, Attack *att) {
  // If it's a non-damaging move, then we can just update the structs as necessary
  if (att->charCode == GROWL) {
    growl_heal_move_screen(pkm, opp, att, false);
		obite.power = obite.power + DEF_GROWL; 
    OSA.power = OSA.power + DEF_GROWL; 
    return 0;
  }
  if (att->charCode == HEAL) {
		growl_heal_move_screen(pkm, opp, att, false);
    opp->hp = opp->hp + DEF_HEAL;
    return 0; 
  }
  // If it's a damaging move, we need to see if the opponent counter-struck correctly. 
	// If they correctly counterstruck, inflict half the attack on the attacker
  if (att->charCode == def->charCode) { 
    if (att->charCode == BITE) {
			fail_move_screen(pkm, opp, att, false);
      opp->hp = opp->hp - .5*obite.power;
      return 0;
    }
    if (att->charCode == SPECIALTYATTACK) {
      fail_move_screen(pkm, opp, att, false);
			opp->hp = opp->hp - .5*OSA.power; 
      return 0; 
    }
  }
	else{
  // Otherwise we need to inflict the damage on the opponent -- 
  // If it's just tackle, update local opp.hp
    if (att->charCode == BITE) {
			defense_move_screen(pkm, opp, att);
      pkm->hp = pkm->hp - obite.power; 
    }
    // If it's the specialty attack, dock points of hp from your pokemon as well,  
    // update local opp.hp
    else {
			defense_move_screen(pkm, opp, att);
      pkm->hp = pkm->hp - OSA.power; 
      opp->hp = opp->hp - DEF_RECOIL;
    }
  }
}