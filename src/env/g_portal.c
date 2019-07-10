
//
//  g_portal.c
//  grdn
//
//  Created by vs on 3/11/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "g_portal.h"

static void destroy(GEntity* entity)
{
}

GPortal* g_portal_create(GArea* a, GArea* b, GEntity* entry_a, GEntity* entry_b, bool bidirectional)
{
	GPortal* port		  = calloc(1, sizeof(GPortal));
	port->a			  = a;
	port->b			  = b;
	port->manifest_a	  = entry_a;
	port->manifest_b	  = entry_b;
	port->bidirectional       = bidirectional;
	port->manifest_a->destroy = destroy;
	port->manifest_b->destroy = destroy;
	return port;
}

void g_portal_destroy(GPortal* portal)
{
	g_area_unregister_entity(portal->a, portal->manifest_a);
	g_area_unregister_entity(portal->b, portal->manifest_b);
	//g_area_remove
	free(portal);
}
