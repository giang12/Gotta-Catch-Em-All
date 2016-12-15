#include "game_ui_define.h"

extern volatile bool ALERT_10MS;
void fail_move_screen(Pokemon *pkm, Pokemon *opp, Attack *att,int isTurn){
	Pokemon *curr; 
	int useX; 
  int useY; 
  char u[] = " uses";
	//char *nm; 
	char m[] = M;
	battle_position(pkm, opp);
	if (isTurn) {
	  curr = pkm;  
	}
	else{
	  curr = opp;
	}
	lcd_print_string(
									curr->name, 
									12, 
	                0,
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK 
								);
	if(curr->charCode == PIKACHU){
	  useY = 12; 
	  useX = 120; 
	}
	else if(curr->charCode == SQUIRTLE){
	  useY = 12; 
	  useX = 135; 
	}
	else{
		useY = 11; 
	  useX = -16;
	}
	lcd_print_string(
									u, 
									useY, 
	                useX,
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK 
								);
  lcd_print_string(
									att->name, 
									10, 
	                0,
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK  
								);
  lcd_print_string(
									m, 
									6, 
	                0,
									LCD_COLOR_ORANGE, 
									LCD_COLOR_WHITE  
								);
	
}

