
//  g_entsys.c
//  g_entsys
//
//  Created by Andrew Macfarlane on 04/04/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_entsys_h_
#define g_entsys_h_

#include "../lang/vmap.h"
#include "g_entity.h"

enum G_ENTITY_SYSTEM_ENTRIES
{
	G_ENTITY_SYSTEM_INTERACTABLE,
	G_ENTITY_SYSTEM_FOO
};

typedef struct GEntSys
{
	void* index;
	void* enemies;
	void* bodies;
	void* interactables;

} GEntSys;

GEntSys* g_entsys_create(void);
void     g_entsys_destroy(GEntSys* sys);
void     g_entsys_update(GEntSys* sys);

int g_entsys_register(GEntSys* sys, GEntity* ent, int type);

#endif
