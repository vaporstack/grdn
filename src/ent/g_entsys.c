
//  g_entsys.c
//  g_entsys
//
//  Created by Andrew Macfarlane on 04/04/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_entsys.h"

#include <stdlib.h>

enum { G_ENTITYSYSTEM_INTERACTABLE, G_ENTITYSYSTEM_FOO } GEntitySystemTypesMap;

GEntSys* g_entsys_create(void)
{
	GEntSys* sys       = calloc(1, sizeof(GEntSys));
	sys->index	 = vmap_create();
	sys->interactables = vmap_create();
	return sys;
}

void g_entsys_destroy(GEntSys* sys)
{

	free(sys->interactables);
	free(sys);

}

void g_entsys_update(GEntSys* sys)
{
	
}

int g_entsys_register(GEntSys* sys, GEntity* ent, int type)
{
	//
	//	vmap_put(sys->, void* key, void* data);
	/*void* map = vmap_get(sys->index, type);
	if (map == NULL) {
		map = vmap_create();
		vmap_put(sys->index, (void*)type);
	}

	vmap_put(map, ent->id, ent);
	*/

	return 0;
}
