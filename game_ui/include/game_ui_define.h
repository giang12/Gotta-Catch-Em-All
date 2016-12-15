#ifndef __GAME_UI_DEFINE_H__
#define __GAME_UI_DEFINE_H__

#include "lcd.h"
#include "lcd_images.h"
#include "fonts.h"

typedef enum {
  PLAYER_1,
  PLAYER_2
} player;

typedef struct Pokemon {
	  int charCode; 
		uint16_t pWidthPixels;   // Image Horizontal Width
		uint16_t pHeightPixels;  // Image Vertical Height
		const uint8_t *pimage;   // Bitmap for pokemon
		uint16_t fColor; 		     // foreground color
		uint16_t bColor;         // background color 
		char* name; 
    int hp; 
}Pokemon;
typedef struct Move{
  int charCode; 
	char *name; 
	int power; 
}Attack; 

// Pokemon Strings
#define P "Pikachu"
#define S "Squirtle"
#define C "Charmander"
// Pokemon charCodes
#define CHARMANDER 0 
#define SQUIRTLE	1	
#define PIKACHU 2
// Move charCodes
#define BITE 0
#define SPECIALTYATTACK 1
#define GROWL 2
#define HEAL 3
#define JUMP 0
#define DUCK 1
// String Library
#define B "Bite";
#define H "Heal";
#define G "Growl";
#define CA "Ember";   // Charmander 1
#define SA1 "Water";  // Squirtle 1
#define SA2 "Gun";    // Squirtle 2
#define SA3 "Water Gun"; // Squirtle 3
#define PA "Shock";   // Pikachu 1
#define U " uses";
#define M "ATTACK MISSES!";
#define SUC "SUCCESSFUL";
#define W "You Win!";
#define L "You Lose!";
#define GE "GAME OVER";

void welcome_screen(void);

void pokemon_selection_sceen(void);

void battle_position(Pokemon *pkm, Pokemon *opp);

void attack_move_screen(Pokemon *pkm, Pokemon *opp, Attack *att);

void defense_move_screen(Pokemon *pkm, Pokemon *opp, Attack *att);

void fail_move_screen(Pokemon *pkm, Pokemon *opp, Attack *att, int isTurn);

void growl_heal_move_screen(Pokemon *pkm, Pokemon *opp, Attack *att, int isTurn);

void game_over_screen(Pokemon *pkm, Pokemon *opp, int isPlayerFainted);

void choose_attack_move_screen(Pokemon *pkm, Pokemon *opp);

void choose_defense_move_screen(Pokemon *pkm, Pokemon *opp);

#endif
