#include "game_ui_define.h"

void pokemon_selection_sceen(void)
{

  char msg_out[] = "Choose your Pokemon!";
	char pika[] = P;
	char squirt[] = S; 
	char charm[] = C; 
	
  // Reach infinite loop
  while(1){
		  
	lcd_clear_screen(LCD_COLOR_BLACK );
  lcd_draw_image(
                  20,                 // X Pos
                  charmanderWidthPixels,   // Image Horizontal Width
                  60,                 // Y Pos
                  charmanderHeightPixels,  // Image Vertical Height
                  charmanderBitmaps,       // Image
                  LCD_COLOR_RED,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );
		lcd_draw_image(
                  20,                 // X Pos
                  squirtleWidthPixels,   // Image Horizontal Width
                  120,                 // Y Pos
                  squirtleHeightPixels,  // Image Vertical Height
                  squirtleBitmaps,       // Image
                  LCD_COLOR_BLUE,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );
		lcd_draw_image(
                  20,                 // X Pos
                  pikachuWidthPixels,   // Image Horizontal Width
                  180,                 // Y Pos
                  pikachuHeightPixels,  // Image Vertical Height
                  pikachuBitmaps,       // Image
                  LCD_COLOR_YELLOW,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );	
    lcd_print_string(
									msg_out, 
									19,
                  0,									
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK 
								);
    lcd_print_string(
									pika, 
									12,
                  0,									
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK 
								);
    lcd_print_string(
									squirt, 
									8,
                  0, 									
									LCD_COLOR_BLUE, 
									LCD_COLOR_BLACK 
								);								
    lcd_print_string(
									charm, 
									4,
                  0, 									
									LCD_COLOR_RED, 
									LCD_COLOR_BLACK 
								);
	}
}


