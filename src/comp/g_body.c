//
//  g_body.c
//  grdn
//
//  Created by Andrew Macfarlane on 9/7/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "g_body.h"

#include <stdlib.h>

GBody* g_body_create(void)
{
	GBody* rec = calloc(1, sizeof(GBody));

	rec->mass = 1.;

	return rec;
}

void g_body_destroy(GBody* bod)
{
	free(bod);
	
}
