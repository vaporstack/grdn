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
#include <r4/src/geo/r_transform.h>
#include <stdio.h>

enum
{
	GRDN_LIGHT_TYPE_POINT,
	GRDN_LIGHT_TYPE_SPOT,
	GRDN_LIGHT_TYPE_AREA,
	GRDN_LIGHT_TYPE_BEAM,
	GRDN_LIGHT_TYPE_NONE
};

enum
{
	GRDN_LIGHT_FALLOFF_TYPE_NONE,
	GRDN_LIGHT_FALLOFF_TYPE_LINEAR,
	GRDN_LIGHT_FALLOFF_TYPE_EXP,
	GRDN_LIGHT_FALLOFF_TYPE_CUBIC
};

typedef struct GLight
{
	int	res;
	int	falloff_type;
	double     falloff;
	double     base_radius;
	double     cur_radius;
	double     frequency;
	double     intensity;
	RLine*     line;
	RTransform transform;
} GLight;

GEntity* g_light_create(unsigned int type);
void     g_light_destroy(GEntity* ent);

void g_light_update(GEntity* ent);

#endif /* g_light_h */
