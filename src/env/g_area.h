
//  g_area.c
//  g_area
//
//  Created by Andrew Macfarlane on 17/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_area_h_
#define g_area_h_

#include "../ent/g_entity.h"
#include <coer/coer.h>
#include <stdio.h>

typedef struct GArea
{
	double    gravity;
	double    friction;
	double    flr;
	GEntity** entities;
	int       num_entities;
	WRect     bounds;
	
	int       link_num;
	CPoint    position;
	void**    links;
	
} GArea;

GArea* g_area_create(void);
void   g_area_destroy(GArea*);

//void g_area_populate_placeholder(GArea*);

int g_area_link_add(GArea* src, GArea* dst);

void g_area_register_entity(GArea*, GEntity*);
void g_area_unregister_entity(GArea*, GEntity*);
void g_area_query_entities(GArea*, GEntity*, int*);

void g_area_service_subscription_create(GArea* area, GEntity* provider);
bool g_area_service_subscription_query(GArea);
void g_area_service_subscribe(GArea* area, GEntity*);

GEntity** g_area_get_entities_radius(GArea*, double x, double y, double r, int* num, GEntity* exclude);

void g_area_update(GArea*);
void g_area_draw(GArea*);

void g_area_draw_debug(GArea* area);
void g_area_notify_layerchanged(GArea* area);

#endif
