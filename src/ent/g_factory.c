
//  g_factory.c
//  g_factory
//
//  Created by Andrew Macfarlane on 10/10/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_factory.h"

static GFactory* implicit = NULL;

GFactory* g_factory_create(void)
{
	GFactory* factory = calloc(1, sizeof(GFactory));
	factory->map      = new_map();
	return factory;
}

void g_factory_destroy(GFactory* factory)
{
	destroy_map(&factory->map);
}

GEntity* g_factory_create_ident(const char* type)
{
	return NULL;
}

GEntity* g_factory_create_type(int type)
{
	return NULL;
}

int g_factory_register(factory_create_func fun)
{

	return 0;
}
