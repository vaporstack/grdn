
//  g_think.c
//  g_think
//
//  Created by Andrew Macfarlane on 23/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_think.h"
#include <r4/r4.h>

GThinkRec* g_think_create(GEntity* ent)
{
	GThinkRec* rec = calloc(1, sizeof(GThinkRec));
	rec->owner = ent;
	rec->last_thought = 0;
	rec->freq = 1;
	ent->think = rec;
	return rec;
}

void g_think_destroy(GThinkRec* rec)
{
	if (!rec)
	{
		printf("tried to kill a think rec that did not exist\n");
		return;
		
	}
	free(rec);
}

void g_think_update(GThinkRec* rec)
{
	double now	     = r_time();
	double time_since_last = now - rec->last_thought;
	if (time_since_last > rec->freq)
	{
		g_think_tick(rec);
	}
}

void g_think_tick(GThinkRec* r)
{
	if ( r->think )
	{
		r->think(r);
		r->last_thought = r_time();
	}else{
		printf("Doing default think!\n");
	}
}

void g_think_decide(GThinkRec* r)
{
}

void g_think_set_area(GThinkRec* r, GArea* area)
{
}
