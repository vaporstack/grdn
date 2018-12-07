
//  g_game.c
//  g_game
//
//  Created by Andrew Macfarlane on 12/17/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_game_h_
#define g_game_h_

#include "../scene/g_background.h"

#include "../ent/g_entsys.h"

typedef struct GGame
{
	int     state;
	GEntSys entsys;
	// GBackground bg;
} GGame;

GGame* g_game_create(void);
void   g_game_destroy(GGame* game);

void g_game_update(void);

#endif
