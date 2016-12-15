#ifndef __POKEMON_H__
#define __POKEMON_H__
#include "game_ui_define.h"

int setPokeStruct(Pokemon* pkm);

void init_nonch(Pokemon *pkm, Pokemon *opp, Attack *bite, Attack *obite, 
	Attack *sa, Attack *osa);

#endif

