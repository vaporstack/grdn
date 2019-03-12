//
//  g_portal.h
//  grdn
//
//  Created by vs on 3/11/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef g_portal_h
#define g_portal_h

#include <stdio.h>
#include "g_area.h"

typedef struct GPortal
{
	GArea* a;
	GArea* b;
	bool bidirectional;
	GEntity* manifest_a;
	GEntity* manifest_b;
}GPortal;

GPortal* g_portal_create(GArea* a, GArea* b, GEntity* entry_a, GEntity* entry_b, bool bidirectional);
void g_portal_destroy(GPortal* portal);

#endif /* g_portal_h */
