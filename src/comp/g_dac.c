
//  g_dac.c
//  g_dac
//
//  Created by Andrew Macfarlane on 08/10/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_dac.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_DAC_SIZE 32

GDac *g_dac_create(int num, void *target)
{
	if (num == 0)
		num = 32;

	GDac *dac   = calloc(1, sizeof(GDac));
	dac->target = target;
	dac->max    = num;
	dac->hits   = calloc(dac->max, sizeof(int));
	printf("Created dat with size %d\n", dac->max);
	return dac;
}

//	shuffle the hits towards the beginning of the array by one
static void shuffle(GDac *dac)
{
	printf("Shuffling\n");
	for (int i = dac->max; i > 0; i--) {
		// printf("i is %d\n", i);
		dac->hits[i] = dac->hits[i - 1];
	}
	printf("done\n");
}

void g_dac_add(GDac *dac, int value)
{
	if (dac->num == dac->max) {
		printf("can't add damage, at max!\n");
		return;
	}
	printf("Setting damage counter %d to %d\n", dac->num, value);
	dac->hits[dac->num] = value;
	dac->num++;
}

void g_dac_process_one(GDac *dac)
{
	if (dac->num == 0)
		return;
	printf("add the first hit to the damage accumulator\n");
	dac->damage += dac->hits[0];
	shuffle(dac);
	dac->num--;
}

void g_dac_process_all(GDac *dac)
{
	if (dac->num == 0) {
		printf("not processing all, no damage\n");
		return;
	}
	printf("doing all accum\n");
	while (dac->num == 0) {
		g_dac_process_one(dac);
	}
}

void g_dac_destroy(GDac *dac)
{
	free(dac->hits);
	free(dac);
}