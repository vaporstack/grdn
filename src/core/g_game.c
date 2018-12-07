
//  g_game.c
//  g_game
//
//  Created by Andrew Macfarlane on 12/17/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_game.h"

GGame* g_game_create(void)
{
	GGame* game = calloc(1, sizeof(GGame));
	return game;
}
void g_game_destroy(GGame* game) { free(game); }
