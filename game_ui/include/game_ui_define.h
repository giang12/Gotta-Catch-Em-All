#ifndef __GAME_UI_DEFINE_H__
#define __GAME_UI_DEFINE_H__

#include "lcd.h"
#include "lcd_images.h"
#include "fonts.h"
#include "utils.h"
#include "wireless_driver.h"

// Pokemon Strings
#define P "Pikachu"
#define S "Squirtle"
#define C "Charmander"


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

#define P "Pikachu"
#define S "Squirtle"
#define C "Charmander"

#define DEF_HP 48 			// default hit points 
#define DEF_BPOW 6      // default bite power
#define DEF_SAPOW 10     // default special attack power
#define DEF_RECOIL 2		// default recoil from special attack 
#define DEF_GROWL 4			// default power increase from growl
#define DEF_HEAL 8 			// default health increase from heal 

// Move charCodes
typedef enum {
  BITE,
  SPECIALTYATTACK,
	GROWL,
	HEAL,
	ATTACK_MOVES_COUNT
} attack_moves;

static const char *attack_names[] = {"BITE", "SPECIALTY ATTACK", "GROWL", "HEAL" };

typedef enum {
  JUMP,
  DUCK,
	DEFENSE_MOVES_COUNT
} defense_moves;

static const char *defense_names[] = {"JUMP", "DUCK ATTACK"};
typedef enum {
  PLAYER_1,
  PLAYER_2,
	PLAYER_COUNT
} player;

static const char *character_names[] = {"Ash", "Brock"};

// Pokemon charCodes
typedef enum {
	CHARMANDER,
  SQUIRTLE,
	PIKACHU,
	POKEMMON_COUNT
} pokemon;

static const char *pokemon_names[] = {
    "Charmander", "Squirtle", "Pikachu"
};


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




extern volatile player ME;
extern volatile pokemon MY_POKEMON;

extern volatile bool ALERT_NEW_ADC; //ADC flag
extern volatile bool WIRELESS_RX_ALERT; //FLAG ON NEW DATA

void waiting_room(Pokemon *pkm, Pokemon *opp);

void welcome_screen(void);

void select_player_screen(void);

void select_pokemon_screen(void);

void battle_position(Pokemon *pkm, Pokemon *opp);

void attack_move_screen(Pokemon *pkm, Pokemon *opp, Attack *att);

void defense_move_screen(Pokemon *pkm, Pokemon *opp, Attack *att);

void fail_move_screen(Pokemon *pkm, Pokemon *opp, Attack *att, int isTurn);

void growl_heal_move_screen(Pokemon *pkm, Pokemon *opp, Attack *att, int isTurn);

void choose_attack_move_screen(Pokemon *pkm, Pokemon *opp);

void choose_defense_move_screen(Pokemon *pkm, Pokemon *opp);

void game_over_screen(Pokemon *pkm, Pokemon *opp, int isPlayerFainted);



#endif
