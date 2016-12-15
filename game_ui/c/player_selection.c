#include "game_ui_define.h"

void select_player_screen(void){
	
	uint16_t y_pos;
	bool playerSelected = false;
	player curr = ME;
	lcd_clear_screen(LCD_COLOR_BLACK );
	
	lcd_print_string(
									"Choose Your Champion!", 
									18,
									20,
									LCD_COLOR_RED, 
									LCD_COLOR_BLACK 
								);
	 lcd_print_string(
									( char *)character_names[PLAYER_1], 
									11,
									90,
									LCD_COLOR_RED, 
									LCD_COLOR_BLACK 
								); //located at 180,170
    lcd_print_string(
									( char *)character_names[PLAYER_2], 
									8, 
									90,
									LCD_COLOR_BLUE, 
									LCD_COLOR_BLACK 
		
						);//located at 180,120
						
		//set initial position of pikachu based on default PLAYER
		lcd_draw_image(
                  180,                 // X Pos
                  pikachuWidthPixels,   // Image Horizontal Width
                  curr == PLAYER_1 ? 170 : 120,// Y Pos
                  pikachuHeightPixels,  // Image Vertical Height
                  pikachuBitmaps,       // Image
                  LCD_COLOR_YELLOW,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );
								
		while(!playerSelected){
			if(btn_is_pressed(BTN_DOWN_PIN)){
				ME = curr;
				printf("Player %i selected! Hello There %s \n\r", ME, ( char *)character_names[ME]);
				//go to choose pokemon
				playerSelected = true;
			}
			if(ALERT_NEW_ADC)
			{
				ALERT_NEW_ADC = false;
				y_pos = ps2_get_y();
				if(ps2_press_up(y_pos))
				{			
						lcd_draw_image(
                  180,                 // X Pos
                  pikachuWidthPixels,   // Image Horizontal Width
                  120,                 // Y Pos
                  pikachuHeightPixels,  // Image Vertical Height
                  pikachuBitmaps,       // Image
                  LCD_COLOR_BLACK,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );
							lcd_draw_image(
                  180,                 // X Pos
                  pikachuWidthPixels,   // Image Horizontal Width
                  170,                 // Y Pos
                  pikachuHeightPixels,  // Image Vertical Height
                  pikachuBitmaps,       // Image
                  LCD_COLOR_YELLOW,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );
					curr = PLAYER_1;
							
				}
				else if(ps2_press_down(y_pos))
				{	
						lcd_draw_image(
                  180,                 // X Pos
                  pikachuWidthPixels,   // Image Horizontal Width
                  170,                 // Y Pos
                  pikachuHeightPixels,  // Image Vertical Height
                  pikachuBitmaps,       // Image
                  LCD_COLOR_BLACK,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );
						lcd_draw_image(
                  180,                 // X Pos
                  pikachuWidthPixels,   // Image Horizontal Width
                  120,                 // Y Pos
                  pikachuHeightPixels,  // Image Vertical Height
                  pikachuBitmaps,       // Image
                  LCD_COLOR_YELLOW,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );
						curr = PLAYER_2;
				}
			}
			
		}
  

	select_pokemon_screen();
}

