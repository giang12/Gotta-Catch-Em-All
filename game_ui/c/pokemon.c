#include "game_ui_define.h"


int setPokeStruct(Pokemon* pkm){
  if (pkm->charCode == CHARMANDER) {
	  pkm->pWidthPixels = charmanderWidthPixels;
		pkm->pHeightPixels = charmanderHeightPixels;
		pkm->pimage = charmanderBitmaps;
		pkm->fColor = LCD_COLOR_RED; 
		pkm->bColor = LCD_COLOR_BLACK;
		pkm->name = C;
		return 0;
	}
  else if (pkm->charCode == SQUIRTLE) {
		pkm->pWidthPixels = squirtleWidthPixels;
		pkm->pHeightPixels = squirtleHeightPixels;
		pkm->pimage = squirtleBitmaps;
		pkm->fColor = LCD_COLOR_BLUE; 
		pkm->bColor = LCD_COLOR_BLACK;
		pkm->name = S;
		return 0;
	}
	else if (pkm->charCode == PIKACHU) {
	  pkm->pWidthPixels = pikachuWidthPixels;
		pkm->pHeightPixels = pikachuHeightPixels;
		pkm->pimage = pikachuBitmaps;
		pkm->fColor = LCD_COLOR_YELLOW; 
		pkm->bColor = LCD_COLOR_BLACK;
		pkm->name = P; 
		return 0;
	}
	else {
		return -1;
	}
}

// Initialize the non-changing parts of the game
void init_nonch(Pokemon *pkm, Pokemon *opp, Attack *bite, Attack *obite, 
	Attack *sa, Attack *osa) {
  bite->name = B; 
	bite->power = DEF_BPOW;
  obite->name = B; 
	obite->power = DEF_BPOW;		 
	sa->power = DEF_SAPOW;
	osa->power = DEF_SAPOW;
  pkm->hp = DEF_HP; 
	opp->hp = DEF_HP;
}
	
