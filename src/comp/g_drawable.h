//
//  g_drawable.h
//  grdn
//
//  Created by vs on 4/24/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef g_drawable_h
#define g_drawable_h

#include <grdn/grdn.h>

typedef int (*drawable_func)(void* data);

typedef struct GDrawable
{
	int foo;
	drawable_func draw;
}GDrawable;

GEntity* g_drawable_create(drawable_func fun);
void g_drawable_destroy(GEntity* ent);
void g_drawable_draw(GDrawable* drw);

#endif /* g_drawable_h */
