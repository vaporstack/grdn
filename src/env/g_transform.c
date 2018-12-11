
//  g_transform.c
//  g_transform
//
//  Created by Andrew Macfarlane on 11/04/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_transform.h"

#include <stdlib.h>

void g_transform_create(GTransform* t)
{
	// GTransform* t = calloc(1, sizeof(GTransform));

	t->anchor   = vec3_create(NULL);
	t->position = vec3_create(NULL);
	t->rotation = vec3_create(NULL);
	t->scale    = vec3_create(NULL);
	t->scale[0] = t->scale[1] = t->scale[2] = 1;
	t->opacity  = 1;
	// return t;
}

void g_transform_destroy(GTransform* t)
{
	free(t->anchor);
	free(t->position);
	free(t->rotation);
	free(t->scale);
	// free(t->anchor);
}

void g_transform_reset(GTransform* t)
{
	t->anchor[0] = t->anchor[1] = t->anchor[2] =0;
	t->position[0] = t->position[1] = t->position[2] = 0;
	t->rotation[0] = t->rotation[1] = t->rotation[2] = 0;
	t->scale[0] = t->scale[1] = t->scale[2] = 1;
	t->opacity = 1;
	
}
