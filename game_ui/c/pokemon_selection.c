#include "game_ui_define.h"

void select_pokemon_screen_init(void){
	char msg_out[80];

	sprintf(msg_out, "Hey there %s, please choose your Pokemon!", character_names[ME]);

	lcd_clear_screen(LCD_COLOR_BLACK );
	
	lcd_print_string(
									msg_out, 
									19,
                  0,									
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK 
								);
  lcd_draw_image(
                  20,                 // X Pos
                  charmanderWidthPixels,   // Image Horizontal Width
                  180,                 // Y Pos
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
                  60,                 // Y Pos
                  pikachuHeightPixels,  // Image Vertical Height
                  pikachuBitmaps,       // Image
                  LCD_COLOR_YELLOW,      // Foreground Color
                  LCD_COLOR_BLACK      // Background Color
                );	
								
		
    lcd_print_string(
									(char *) pokemon_names[CHARMANDER], 
									12,
                  0, 									
									LCD_COLOR_RED, 
									LCD_COLOR_BLACK 
								);
    
    lcd_print_string(
									(char *) pokemon_names[SQUIRTLE], 
									8,
                  0, 									
									LCD_COLOR_BLUE, 
									LCD_COLOR_BLACK 
								);								

		lcd_print_string(
									(char *) pokemon_names[PIKACHU],
									4,
                  0,									
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK 
								);
}

void pikachu_i_choose_you(pokemon type)
{
				switch(type){
					case CHARMANDER:
						draw_line(0, 240, 110, 115, LCD_COLOR_BLACK);
						draw_line(0, 240, 50, 55, LCD_COLOR_BLACK);
						draw_line(20, 220, 170, 175, LCD_COLOR_RED);
						break;
					case SQUIRTLE:
						draw_line(0, 240, 170, 175, LCD_COLOR_BLACK);
						draw_line(0, 240, 50, 55, LCD_COLOR_BLACK);
						draw_line(20, 220, 110, 115, LCD_COLOR_BLUE);
						break;
					case PIKACHU:
						draw_line(0, 240, 170, 175, LCD_COLOR_BLACK);
						draw_line(0, 240, 110, 115, LCD_COLOR_BLACK);
						draw_line(20, 220, 50, 55, LCD_COLOR_YELLOW);
					default:
						break;
				}
	
}
void select_pokemon_screen(void)
{
	bool selected = false;
	pokemon curr = MY_POKEMON;
	uint16_t totalPokemon = (sizeof(pokemon_names) / sizeof(pokemon_names[0])) - 1; //offset by 1...
  select_pokemon_screen_init();

		
	while(!selected){
			if(btn_is_pressed(BTN_DOWN_PIN)){
				MY_POKEMON = curr;
				printf("%s selected %s ... \n\r",( char *)character_names[ME], ( char *)pokemon_names[MY_POKEMON]);
				//go to choose pokemon
				selected = true;
				//continue;
			}
			
			if(ALERT_NEW_ADC)
			{
				ALERT_NEW_ADC = false;

				if(debounce_ps_press_up())
				{			
					curr -= (curr > 0 ? 1 : 0);
					printf("current pokemon %s \n\r", ( char *)pokemon_names[curr]);
					pikachu_i_choose_you(curr);
				}
				else if(debounce_ps_press_down())
				{	
					curr += (curr < totalPokemon ? 1 : 0);
					printf("current pokemon %s \n\r", ( char *)pokemon_names[curr]);
					pikachu_i_choose_you(curr);

				}
					
			}
			
	}
	
}


