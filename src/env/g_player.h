//
//  g_player.h
//  grdn
//
//  Created by vs on 1/4/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef g_player_h
#define g_player_h

#include "../ent/g_entity.h"

typedef struct GPlayer
{
	void (*move)(void);
	const char* name;
	int	 id;
} GPlayer;

GEntity* g_player_create(const char* name);
void     g_player_destroy(GEntity* ent);

#endif /* g_player_h */
