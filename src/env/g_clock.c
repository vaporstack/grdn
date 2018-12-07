
//  g_clock.c
//  g_clock
//
//  Created by Andrew Macfarlane on 10/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_clock.h"

#include <stdlib.h>

GClock* g_clock_create(unsigned long long seed)
{
	GClock* clock     = (GClock*)calloc(1, sizeof(GClock));
	clock->start_time = r_time();
	clock->cur_time   = clock->start_time;
	clock->rng	= r_rand_create_seed(seed);
	return clock;
}

double g_clock_get_time(GClock* clock)
{
	return clock->cur_time;
}

void g_clock_update(GClock* clock)
{
	clock->cur_time = r_time() - clock->start_time;
}

void g_clock_destroy(GClock* rec)
{

	free(rec);
}
