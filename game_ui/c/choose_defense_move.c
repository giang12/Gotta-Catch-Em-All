#include "game_ui_define.h"


void choose_defense_move_screen(Pokemon *pkm, Pokemon *opp) {
  char chooseD[] = "Choose your defense:";
	char j[] = "Jump";
	char d[] = "Duck";
	battle_position(pkm, opp);
	lcd_print_string(
									chooseD, 
									12,
                  0,	
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK 
								);
  lcd_draw_image  (
                    75,                 // X Pos
                    sboxWidthPixels,   // Image Horizontal Width
                    100,                 // Y Pos
                    sboxHeightPixels,  // Image Vertical Height
                    sboxBitmaps,       // Image
                    LCD_COLOR_GRAY,      // Foreground Color
                    LCD_COLOR_BLACK      // Background Color
                  );
	lcd_draw_image  (
                    75,                 // X Pos
                    sboxWidthPixels,   // Image Horizontal Width
                    40,                 // Y Pos
                    sboxHeightPixels,  // Image Vertical Height
                    sboxBitmaps,       // Image
                    LCD_COLOR_GRAY,      // Foreground Color
                    LCD_COLOR_BLACK      // Background Color
                  );
  lcd_print_string(
									j, 
									7,
                  66,	
									LCD_COLOR_BLACK, 
									LCD_COLOR_GRAY 
								);
  lcd_print_string(
									d, 
									3,
                  66,	
									LCD_COLOR_BLACK, 
									LCD_COLOR_GRAY 
								);
}


