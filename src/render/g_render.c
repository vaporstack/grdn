//
//  g_render.c
//  grdn
//
//  Created by vs on 11/26/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "g_render.h"

#include <drw/drw.h>

void g_render_gentity(GEntity* ent)
{
	drw_push();
	drw_translate_vec3(ent->transform.position);

	drw_robject(ent->art);

	drw_pop();
}
