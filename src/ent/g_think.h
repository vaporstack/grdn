
//  g_think.c
//  g_think
//
//  Created by Andrew Macfarlane on 23/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_think_h_
#define g_think_h_

#include "../env/g_area.h"
//#include <r4/r4.h>

typedef void (*think_fun)(void*);

typedef struct GThinkRec
{
	void* owner;
	double freq;
	double power;
	double last_thought;
	void **enemies;
	void **friends;
	void **decisions;
	void* target;
	GArea *pool;
	think_fun think;
} GThinkRec;

GThinkRec *g_think_create(GEntity* ent);
void      g_think_destroy(GThinkRec *r);
void      g_think_update(GThinkRec *r);
void      g_think_tick(GThinkRec *r);
void      g_think_decide(GThinkRec *r);

void g_think_set_area(GThinkRec *r, GArea *area);

#endif
