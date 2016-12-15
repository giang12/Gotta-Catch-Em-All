#include "game_ui_define.h"


void choose_attack_move_screen(Pokemon *pkm, Pokemon *opp){
	char* sa_str; 
  char* sa_str2;
	char choose[] = "Choose your move:";
  char b[] = "Bite";
  char h[] = "Heal";
  char g[] = "Growl";
  char ca[] = "Ember";
	char sa1[] = "Water";  // Squirtle 1
  char sa2[] = "Gun";    // Squirtle 2
  char pa[] = "Shock";   // Pikachu 1
	battle_position(pkm, opp); 
	if(pkm->charCode == CHARMANDER) {
	  sa_str = ca; 
	}
	else if(pkm->charCode == SQUIRTLE) {
	  sa_str = sa1;
		sa_str2 = sa2; 
	}
	else{
	  sa_str = pa; 
	}
	lcd_print_string(
									choose, 
									12, 
	                0,
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK 
								);
  lcd_draw_image  (
                    130,                 // X Pos
                    sboxWidthPixels,   // Image Horizontal Width
                    100,                 // Y Pos
                    sboxHeightPixels,  // Image Vertical Height
                    sboxBitmaps,       // Image
                    LCD_COLOR_GRAY,      // Foreground Color
                    LCD_COLOR_BLACK      // Background Color
                  );
	lcd_draw_image  (
                    130,                 // X Pos
                    sboxWidthPixels,   // Image Horizontal Width
                    40,                 // Y Pos
                    sboxHeightPixels,  // Image Vertical Height
                    sboxBitmaps,       // Image
                    LCD_COLOR_GRAY,      // Foreground Color
                    LCD_COLOR_BLACK      // Background Color
                  );
	lcd_draw_image  (
                    20,                 // X Pos
                    sboxWidthPixels,   // Image Horizontal Width
                    100,                 // Y Pos
                    sboxHeightPixels,  // Image Vertical Height
                    sboxBitmaps,       // Image
                    LCD_COLOR_GRAY,      // Foreground Color
                    LCD_COLOR_BLACK      // Background Color
                  );
	lcd_draw_image  (
                    20,                 // X Pos
                    sboxWidthPixels,   // Image Horizontal Width
                    40,                 // Y Pos
                    sboxHeightPixels,  // Image Vertical Height
                    sboxBitmaps,       // Image
                    LCD_COLOR_GRAY,      // Foreground Color
                    LCD_COLOR_BLACK      // Background Color
                  );
  lcd_print_string(
									b, 
									7,
                  11,	
									LCD_COLOR_BLACK, 
									LCD_COLOR_GRAY 
								);
  if (pkm->charCode == SQUIRTLE){
	  lcd_print_string(
									sa_str2, 
									3,
                  11,	
									LCD_COLOR_BLACK, 
									LCD_COLOR_GRAY 
								);
	  lcd_print_string(
									sa_str, 
									4,
                  11,	
									LCD_COLOR_BLACK, 
									LCD_COLOR_GRAY 
								);
	}
	else{
	  lcd_print_string(
									sa_str, 
									3,
                  11,	
									LCD_COLOR_BLACK, 
									LCD_COLOR_GRAY 
								);
	}
  lcd_print_string(
									g, 
									7,
                  121,	
									LCD_COLOR_BLACK, 
									LCD_COLOR_GRAY 
								);
  lcd_print_string(
									h, 
									3,
                  121,	
									LCD_COLOR_BLACK, 
									LCD_COLOR_GRAY 
								);
	
	
	
}