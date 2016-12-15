#include "game_ui_define.h"

extern volatile bool ALERT_10MS;
void attack_move_screen(Pokemon *pkm, Pokemon *opp, Attack *att){
	int x_pos = 0;
  //int count = 0;
  int hasHit = 0;
  int useX; 
  int useY; 
  char u[] = " uses";
	//char *nm; 
	battle_position(pkm, opp);
	lcd_print_string(
									pkm->name, 
									12, 
	                0,
									LCD_COLOR_YELLOW, 
									LCD_COLOR_BLACK 
								);
	if(pkm->charCode == PIKACHU){
	  useY = 12; 
	  useX = 120; 
	}
	else if(pkm->charCode == SQUIRTLE){
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

	x_pos = 165;
  //count = 0;	
	hasHit = 0; 
	while (!(x_pos == 165 && hasHit)) { 
		if (att->charCode == BITE) {
		  lcd_draw_image  (
                    x_pos,                 // X Pos
                    pkm->pWidthPixels,   // Image Horizontal Width
                    250,                 // Y Pos
                    pkm->pHeightPixels,  // Image Vertical Height
                    pkm->pimage,       // Image
                    pkm->fColor,      // Foreground Color
                    pkm->bColor      // Background Color
                  );
		}
		if(ALERT_10MS) {
		  if (x_pos > 35 && !hasHit){
		    x_pos = x_pos - 5;
				if (att->charCode == BITE) {
				lcd_draw_image  (
                    x_pos+5,                 // X Pos
                    pkm->pWidthPixels,   // Image Horizontal Width
                    250,                 // Y Pos
                    pkm->pHeightPixels,  // Image Vertical Height
                    pkm->pimage,       // Image
                    LCD_COLOR_BLACK,      // Foreground Color
                    pkm->bColor      // Background Color
                  );
				}
				else {
				lcd_draw_image  (
                    x_pos,                 // X Pos
                    bullWidthPixels,   // Image Horizontal Width
                    275,                 // Y Pos
                    bullHeightPixels,  // Image Vertical Height
                    bullBitmaps,       // Image
                    pkm->fColor,      // Foreground Color
                    pkm->bColor      // Background Color
                  );
	
				}
		  }			
		  else if(x_pos == 35) {
		    x_pos = x_pos +5; 
			  hasHit = 1; 
		  }
		  else if (x_pos < 165 && hasHit) {
		    x_pos = x_pos + 5;
        lcd_draw_image  (
                    x_pos-5,                 // X Pos
                    pkm->pWidthPixels,   // Image Horizontal Width
                    250,                 // Y Pos
                    pkm->pHeightPixels,  // Image Vertical Height
                    pkm->pimage,       // Image
                    LCD_COLOR_BLACK,      // Foreground Color
                    pkm->bColor      // Background Color
                  );		
				lcd_draw_image  (
                    35,                 // X Pos
                    opp->pWidthPixels,   // Image Horizontal Width
                    250,                 // Y Pos
                    opp->pHeightPixels,  // Image Vertical Height
                    opp->pimage,       // Image
                    opp->fColor,      // Foreground Color
                    opp->bColor      // Background Color
                  );				
		  }
		  else {
		  }
			ALERT_10MS = false;
	 }
	}
	lcd_draw_image  (
                    165,                 // X Pos
                    pkm->pWidthPixels,   // Image Horizontal Width
                    250,                 // Y Pos
                    pkm->pHeightPixels,  // Image Vertical Height
                    pkm->pimage,       // Image
                    pkm->fColor,      // Foreground Color
                    pkm->bColor      // Background Color
                  );
}



