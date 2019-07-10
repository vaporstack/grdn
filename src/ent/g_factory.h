
//  g_factory.c
//  g_factory
//
//  Created by Andrew Macfarlane on 10/10/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_factory_h_
#define g_factory_h_

#include <cmap/map.h>
#include <grdn/grdn.h>

typedef struct GFactory
{
	int	   foo;
	struct map_t* map;
} GFactory;

GFactory* g_factory_create(void);
void      g_factory_destroy(GFactory* factory);

typedef GEntity* (*factory_create_func)(void);

GEntity* g_factory_create_ident(const char* type);
GEntity* g_factory_create_type(int type);

int g_factory_register(factory_create_func);

#endif
