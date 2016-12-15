#ifndef __GAME_UI_DEFINE_H__
#define __GAME_UI_DEFINE_H__

#include "lcd.h"
#include "lcd_images.h"
#include "fonts.h"

typedef enum {
  PLAYER_1,
  PLAYER_2
} player;


#define P "Pikachu"
#define S "Squirtle"
#define C "Charmander"


void welcome_screen(void);

void pokemon_selection_sceen(void);


#endif
