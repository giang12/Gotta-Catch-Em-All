#ifndef __GAME_UI_DEFINE_H__
#define __GAME_UI_DEFINE_H__

#include "lcd.h"
#include "lcd_images.h"
#include "fonts.h"

typedef enum {
  PLAYER_1,
  PLAYER_2
} player;

static const char *character_names[] = {"Ash", "Brock"};

typedef enum {
  Pikachu,
  Squirtle,
	Charmander
} pokemon;

static const char *pokemon_names[] = {
    "Pikachu", "Squirtle", "Charmander"
};

#define P "Pikachu"
#define S "Squirtle"
#define C "Charmander"

#include "ps2.h"
#include "utils.h"



extern volatile player ME;
extern volatile pokemon MY_POKEMON;

extern volatile bool ALERT_NEW_ADC; //ADC flag

void welcome_screen(void);

void select_player_screen(void);

void select_pokemon_screen(void);

#endif
