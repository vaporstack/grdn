//
//  g_light.h
//  grdn
//
//  Created by vs on 9/20/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef g_light_h
#define g_light_h

#include "../ent/g_entity.h"
#include <r4/src/geo/r_line.h>
#include <stdio.h>
#include <r4/src/geo/r_transform.h>

typedef struct GLight
{
	int    res;
	double size;
	double frequency;
	double intensity;
	RLine* line;
	RTransform transform;
} GLight;

GEntity* g_light_create(void);
void     g_light_destroy(GEntity* ent);

void g_light_update(GEntity* ent);

#endif /* g_light_h */
