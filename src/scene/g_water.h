//
//  g_water.h
//  grdn
//
//  Created by vs on 11/19/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef g_water_h
#define g_water_h

#include <stdio.h>

typedef struct GWater
{
	int foo;
} GWater;

GWater* g_water_create(void);
void    g_water_destroy(GWater* water);

#endif /* g_water_h */
