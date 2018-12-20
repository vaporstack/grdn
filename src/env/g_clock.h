
//  g_clock.c
//  g_clock
//
//  Created by Andrew Macfarlane on 10/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_clock_h_
#define g_clock_h_

//#include <r4/r4.h>
#include <r4/src/core/r_random.h>
#include <r4/src/core/r_time.h>

typedef struct GClock
{
	double  start_time;
	double  cur_time;
	RRandom rng;
} GClock;

GClock* g_clock_create(unsigned long long seed);
double  g_clock_get_time(GClock* clock);
void    g_clock_update(GClock* clock);
void    g_clock_destroy(GClock* clock);

#endif
