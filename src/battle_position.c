#include "game_ui_define.h"
#include "main.h"


void battle_position(Pokemon *pkm, Pokemon *opp){
	lcd_draw_image  (
                    165,                 // X Pos
                    pkm->pWidthPixels,   // Image Horizontal Width
                    250,                 // Y Pos
                    pkm->pHeightPixels,  // Image Vertical Height
                    pkm->pimage,       // Image
                    pkm->fColor,      // Foreground Color
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