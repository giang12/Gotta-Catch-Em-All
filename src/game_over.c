#include "game_ui_define.h"
char w[] = "You Win!";
char l[] = "You Lose!";
char ge[] = "GAME OVER";
void game_over_screen(Pokemon *pkm, Pokemon *opp, int isPlayerFainted) {
	 battle_position(pkm, opp);
	 lcd_print_string(
									ge, 
									12, 
	                40,
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK 
								);
	 if (!isPlayerFainted) {
    lcd_print_string(
	                w, 
									10, 
	                50,
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK  
								);
	 }
	 else {
    lcd_print_string(
									l, 
									10, 
	                40,
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK  
								);
	 }
}