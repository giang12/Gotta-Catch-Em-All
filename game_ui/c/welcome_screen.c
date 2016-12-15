#include "game_ui_define.h"

void welcome_screen(void)
{
	
	uint32_t count; 

  // Reach infinite loop
	lcd_clear_screen(LCD_COLOR_BLACK );
	
	lcd_print_string(
									"Hey there trainer!", 
									19,//y
									25,//x
									LCD_COLOR_RED, 
									LCD_COLOR_BLACK 
								);
	
	lcd_print_string(
									"Are you ready to prove yourself on the ultimate   Pokemon  battle field?", 
									16,
									5,
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK 
								);
	
	
  lcd_draw_image(
                  180,                 // X Pos
                  charmanderWidthPixels,   // Image Horizontal Width
                  80,                 // Y Pos
                  charmanderHeightPixels,  // Image Vertical Height
                  charmanderBitmaps,       // Image
                  LCD_COLOR_RED,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );
	lcd_draw_image(
                  100,                 // X Pos
                  pikachuWidthPixels,   // Image Horizontal Width
                  100,                 // Y Pos
                  pikachuHeightPixels,  // Image Vertical Height
                  pikachuBitmaps,       // Image
                  LCD_COLOR_YELLOW,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );								
							
		lcd_draw_image(
                  20,                 // X Pos
                  squirtleWidthPixels,   // Image Horizontal Width
                  80,                 // Y Pos
                  squirtleHeightPixels,  // Image Vertical Height
                  squirtleBitmaps,       // Image
                  LCD_COLOR_BLUE,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );
		
		count = 0;
		while(count < 9999999*3){
			
			count++;
		}
		
		select_player_screen();
}




