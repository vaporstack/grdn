//
//  g_player.c
//  grdn
//
//  Created by vs on 1/4/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "g_player.h"

GEntity* g_player_create(const char* name)
{
	GPlayer* rec = calloc(1, sizeof(GPlayer));
	GEntity* ent = g_entity_create(name);
	ent->layer   = 0;
	ent->data    = rec;
	return ent;
}

void g_player_destroy(GEntity* ent)
{
	free(ent->data);
	free(ent);
}
