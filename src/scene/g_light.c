//
//  g_light.c
//  grdn
//
//  Created by vs on 9/20/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "g_light.h"

#include <drw/drw.h>

static void update_common(GLight* light)
{
}

#pragma mark point
static void update_point(GEntity* ent)
{
	GLight* light = ent->data;

	light->cur_radius = light->base_radius;
}

static void draw_point(GEntity* ent)
{
	drw_push();
	drw_translate(ent->transform.position[0], ent->transform.position[1], ent->transform.position[2]);
	GLight* light = ent->data;
	double  rad   = light->base_radius;
	drw_circle_precision_set(18);
	drw_fill_set(true);
	drw_circle(rad);
	drw_fill_pop();

	drw_pop();
}

#pragma mark spot
static void update_spot(GEntity* ent)
{
}

static void draw_spot(GEntity* ent)
{
	//GLight* light = ent->data;
}

#pragma mark area

static void update_area(GEntity* ent)
{
}

static void draw_area(GEntity* ent)
{
}

#pragma mark beam

static void update_beam(GEntity* ent)
{
}
static void draw_beam(GEntity* ent)
{
}
static void setup_point(GLight* light)
{
	//light->size = .25;
	light->intensity   = .8;
	light->base_radius = 25;
}

GEntity* g_light_create(unsigned int type)
{
	GEntity* ent = g_entity_create("g_light");

	GLight* light = calloc(1, sizeof(GLight));

	/*
	GRDN_LIGHT_TYPE_POINT,
	GRDN_LIGHT_TYPE_SPOT,
	GRDN_LIGHT_TYPE_AREA,
	GRDN_LIGHT_TYPE_BEAM,
	GRDN_LIGHT_TYPE_NONE
	*/
	ent->update = g_light_update;
	ent->layer = -1;
	switch (type)
	{
	case GRDN_LIGHT_TYPE_POINT:
		ent->draw   = draw_point;
		ent->update = update_point;
		setup_point(light);
		break;
	case GRDN_LIGHT_TYPE_SPOT:
		ent->draw   = draw_spot;
		ent->update = update_spot;

		break;
	case GRDN_LIGHT_TYPE_AREA:
		ent->draw = draw_area;
		break;
	case GRDN_LIGHT_TYPE_BEAM:
		ent->draw = draw_beam;
		break;
	default:
		break;
	}

	ent->data = light;
	ent->name = "uninteresting_light";
	printf("Created a light\n");
	return ent;
}

void g_light_destroy(GEntity* ent)
{
	free(ent->data);
	g_entity_destroy(ent);
}

void g_light_update(GEntity* ent)
{
	// do something pls
}
