//
//  g_light.c
//  grdn
//
//  Created by vs on 9/20/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "g_light.h"

GEntity* g_light_create(void) {
	GEntity* ent = g_entity_create("g_light");
	
	GLight* light = calloc(1, sizeof(GLight));
	
	ent->data = light;
	ent->name = "uninteresting_light";
	return ent;
}

void g_light_destroy(GEntity* ent) {
	free(ent->data);
	g_entity_destroy(ent);
}

void g_light_update(GEntity* ent) {
	// do something pls
}
