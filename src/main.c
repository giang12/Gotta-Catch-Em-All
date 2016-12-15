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

uint8_t individual_1_id[]  = { 3,5,3,3,2};
uint8_t individual_2_id[]  = { 3,5,3,3,3};


volatile player ME = PLAYER_1; //DEFAULT
volatile pokemon MY_POKEMON = PIKACHU; //DEFAULT

bool isWirelessGood = false;

extern volatile bool ALERT_10MS; //animination timer flag
extern volatile bool ALERT_NEW_ADC; //ADC flag



//*****************************************************************************
//*****************************************************************************
void initialize_hardware(void)
{
	DisableInterrupts();
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
	EnableInterrupts();
}


//*****************************************************************************
//*****************************************************************************



bool isTurn;
Attack SA;                 // Specialty Attack
Attack bite; 							 // Bite
Attack OSA;								 // Opponent's special attack
Attack obite; 						 // Opponent's bite attack 

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	bool isGameEnd; 
	bool isPlayerFainted; 
	bool isOppFainted; 
	bool stat_sent;
	int stat_rec; 
	Pokemon pkm;
  Pokemon opp; 
  
	Attack att;
  Attack def; 
	
	
	
	
  initialize_hardware();
	
	eeprom_read_team_info(); //requirement
	
	
	init_nonch(&pkm, &opp, &bite, &obite, &SA, &OSA);  
	//welcome_screen();
	
	select_player_screen();
	
	select_pokemon_screen();
	
	// gets pkm charCode 
	//pkm.charCode = MY_POKEMON;
	//opp.charCode = SQUIRTLE;

	if(ME == PLAYER_1)
	{
		isTurn = true;
		while(!wireless_configure_device(individual_1_id, individual_2_id)){
				printf("Connecting to %s @%s \n\r", character_names[PLAYER_2], individual_2_id);
			};
	}
	else
	{
		isTurn = false;
		while(!wireless_configure_device(individual_2_id, individual_1_id)){
				printf("Connecting to %s @%s \n\r", character_names[PLAYER_1], individual_1_id);
		};
	}
	
	waiting_room(&pkm, &opp);
	

	printf("My Pokemon: %s | My opp Pokemon: %s \n\r", pokemon_names[pkm.charCode], pokemon_names[opp.charCode]);
	
	// Set up the structures of the pokemon
	setPokeStruct(&pkm);
  setPokeStruct(&opp);
	
		// Turns are set, time to begin game 
	isGameEnd = false; //start game
  while(!isGameEnd) {
    // Set the pre turn vars 
		att.charCode = ATTACK_MOVES_COUNT;
    def.charCode = DEFENSE_MOVES_COUNT;
    stat_rec = DEF_HP; 
    stat_sent = false; 
		isPlayerFainted= false; 
		isOppFainted = false;
		
    // Update the LEDs
		// update_LEDs(pkm.hp, opp.hp); 
		if(isTurn){	
	    choose_attack_move_screen(&pkm, &opp); 
      while(att.charCode >= ATTACK_MOVES_COUNT) {
			   att.charCode = setAttack(ATTACK_MOVES_COUNT); // something to get the attack from the buttons
			}
			printf("%s is about to  %s \n\r", pokemon_names[pkm.charCode], attack_names[att.charCode]);
	    while(def.charCode >= DEFENSE_MOVES_COUNT) {
				  sendMyMove(att.charCode);       
					def.charCode = getOpponentMove(DEFENSE_MOVES_COUNT);// something to get the defense from comm
			}
			printf("%s is about to  %s \n\r", pokemon_names[opp.charCode], defense_names[def.charCode]);

			// Send the info to the Attack Handler  
			attack_handler(&pkm, &opp, &att, &def);
		}
		else {
		  choose_defense_move_screen(&pkm, &opp);
		  while(def.charCode >= DEFENSE_MOVES_COUNT) {
			   def.charCode = setDefense(DEFENSE_MOVES_COUNT);// something to get the defense from the buttons
			}
			printf("%s is about to  %s \n\r", pokemon_names[pkm.charCode], defense_names[def.charCode]);

			while(att.charCode >= ATTACK_MOVES_COUNT) {
				 sendMyMove(def.charCode);       
				att.charCode = getOpponentMove(ATTACK_MOVES_COUNT); //something to get the attack from comm
			}
			printf("%s is about to  %s \n\r", pokemon_names[opp.charCode], attack_names[att.charCode]);

			// Send the info to the Defense Handler
		  defense_handler(&pkm, &opp, &def, &att);
		}
		printf("wtfffff \n\r");
		// Between turns check to see if the game will continue 
		if (pkm.hp <= 0) {
		  isPlayerFainted = true; 
		}
		while(!stat_sent) {
		   stat_sent = sendMyMove(1); //send opponent isPlayerFainted var
		}
		while(stat_rec >= DEF_HP) {
		  stat_rec = getOpponentMove(DEF_HP); //get the opponent's isPlayerFainted var
			if(stat_rec == 0){
				isOppFainted = true;
			}
		}
		printf("%d  - %d\n\r" ,pkm.hp, opp.hp);
		if (isPlayerFainted) {
		  game_over_screen(&pkm, &opp, true);
			isGameEnd = true;
		}
		if (isOppFainted) {
		  game_over_screen(&pkm, &opp, false); 
			isGameEnd = true;
		}
		// Switch whose turn it is 
		isTurn = !isTurn; 
	}	
	
  while(1){

		//cuz requirement
		if(sw_is_pressed(SW2_PIN)){
			//When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 
			printf("sw2_is_pressed \r\n");
			eeprom_write_team_info(individual_1, individual_2, group);
		}
	
		
  };
}


//max_count is use to check if data is valid
bool sendMyMove(uint32_t data){
	wireless_com_status_t status;

	status = wireless_send(true, true, data);
  if(status != NRF24L01_TX_SUCCESS)
   {
      printf("Error Message: %s\n\r",wireless_error_messages[status]);
			return false;
   }else{
			printf("sent \n\r");
			return true;
		}
	
}

//max_count is use to check if data is valid
uint32_t getOpponentMove(uint32_t max_valid_data){
	uint32_t data;
	wireless_com_status_t status;

	if(WIRELESS_RX_ALERT){
			
				WIRELESS_RX_ALERT = false;

				status = wireless_get(true, &data);

				printf("received data: %d\n", data);
			
				if(status == NRF24L01_RX_SUCCESS && data < max_valid_data)
        {
					return data;
				}
				
	printf("Error Message: %s\n\r",wireless_error_messages[status]);

	}
	
	return max_valid_data + 1; //return that max count as a signal that data is not valid
}


uint32_t setAttack(uint32_t max_valid_data){
	
	if(btn_is_pressed(BTN_UP_PIN)){
		return BITE;
	}else if(btn_is_pressed(BTN_DOWN_PIN)){
		return SPECIALTYATTACK;
	}else if(btn_is_pressed(BTN_LEFT_PIN)){
		return GROWL;
	}else if(btn_is_pressed(BTN_RIGHT_PIN)){
		return HEAL;
	}
	
	return max_valid_data + 1; //return that max count as a signal that data is not valid
}




uint32_t setDefense(uint32_t max_valid_data){
	
	if(btn_is_pressed(BTN_UP_PIN)){
		return JUMP;
	}else if(btn_is_pressed(BTN_DOWN_PIN)){
		return DUCK;
	}
	
	return max_valid_data + 1;
}



uint32_t attack_handler(Pokemon *pkm, Pokemon *opp, Attack *att, Attack *def) {
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
	return 1;
}

uint32_t defense_handler(Pokemon *pkm, Pokemon *opp, Attack *def, Attack *att) {
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
	return 1;
}


