
//  g_dac.c
//  g_dac
//
//  Created by Andrew Macfarlane on 08/10/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_dac_h_
#define g_dac_h_

typedef struct GDac
{
	long  damage;
	int * hits;
	int   num;
	int   max;
	void *target;
} GDac;

GDac *g_dac_create(int num, void *target);
void  g_dac_process_one(GDac *dac);
void  g_dac_process_all(GDac *dac);
void  g_dac_destroy(GDac *dac);
void  g_dac_add(GDac *dac, int damageval);
int   g_dac_has_damage(GDac *dac);

#endif
