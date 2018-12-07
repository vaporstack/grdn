//
//  g_drawable.c
//  grdn
//
//  Created by vs on 4/24/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "g_drawable.h"

GEntity* g_drawable_create(drawable_func fun)
{
	GEntity* ent = g_entity_create("Unknown drawable");
	
	GDrawable * draw = calloc(1, sizeof(GDrawable));
	draw->draw = fun;
	ent->data = draw;

	return ent;
}

void g_drawable_destroy(GEntity* ent)
{
	GDrawable* bored_finally = ent->data;
	free(bored_finally);
	free(ent);
	
	return;

}
