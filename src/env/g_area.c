
//  g_area.c
//  g_area
//
//  Created by Andrew Macfarlane on 17/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_area.h"

//#include "run_area.h"
#include <deps/gl-matrix/gl-matrix.h>
#include <drw/drw.h>
#include <grdn/grdn.h>
#include <r4/src/geo/r_object.h>
#include <stdlib.h>
//#include <grdn/src/util/grdn_sort.h>
#include <coer/src/util/coer_sort.h>

//extern AppExtensions app_extensions;
//extern AppSettings app_settings;

//static void g_area_check_grounded(GArea*)

static void g_area_bounds_check(GArea* area, GEntity* ent)
{
	//	double test = 0;
	if (ent->transform.position[0] < area->bounds.pos.x)
	{
		grdn_log("Hit boundary!\n");
		ent->transform.position[0] = area->bounds.pos.x;
		ent->vel[0]		   = 0;
	}

	if (ent->transform.position[0] > area->bounds.pos.x + area->bounds.size.x)
	{
		grdn_log("Hit boundary!\n");
		ent->transform.position[0] = area->bounds.pos.x + area->bounds.size.x;
		ent->vel[0]		   = 0;
	}

	if (ent->transform.position[1] < area->bounds.pos.y)
	{
		grdn_log("Hit boundary!\n");
		ent->transform.position[1] = area->bounds.pos.y;
		ent->vel[1]		   = 0;
	}

	if (ent->transform.position[1] > area->bounds.pos.y + area->bounds.size.y)
	{
		grdn_log("Hit boundary!\n");
		ent->transform.position[1] = area->bounds.pos.y + area->bounds.size.y;
		ent->vel[1]		   = 0;
	}
}

GEntity** g_area_get_entities_radius(GArea* area, double x, double y, double r, int* num, GEntity* exclude)
{
	GEntity** res  = NULL;
	int       rnum = 0;
	for (int i = 0; i < area->num_entities; i++)
	{
		GEntity* e = area->entities[i];
		if (e == exclude)
			continue;

		double d = dist2d(x, y, e->transform.position[0], e->transform.position[1]);
		if (d < r)
		{
			printf("entity within range\n");
			rnum++;
			if (!res)
			{
				res = calloc(1, sizeof(GEntity*));
			}
			else
			{
				res = realloc(res, rnum * sizeof(GEntity*));
			}
			res[rnum - 1] = e;
		}
	}
	*num = rnum;
	return res;
}

static void g_area_update_body(GArea* area, GEntity* ent)
{
	//	clamp velocity to maxes
	vec3_t mx   = ent->vel_max;
	double vel  = ent->vel[0];
	vel	 = clamp(ent->vel[0], -mx[0], mx[0]);
	ent->vel[0] = vel;

	vec3_add(ent->transform.position, ent->vel, NULL);

	ent->vel[1] += area->gravity;

	vec3_t pos = ent->transform.position;

	pos[0] += ent->vel[0];
	pos[1] += ent->vel[1];
	pos[2] += ent->vel[2];

	if (0 == strcmp("player", ent->name))
	{
		//printf("Player %f %f %f\n", pos[0], pos[1], pos[2]);
	}

	if (pos[1] < 0)
	{
		pos[1]		    = 0;
		ent->body->grounded = true;
	}

	if (ent->body->grounded)
	{
		ent->vel[1] = 0;
		ent->vel[0] *= area->friction;
	}
	g_area_bounds_check(area, ent);

	/*
	 //apparently I was doing this three ways in three places, lol
	 if ( ent->body )
	 {
	 g_area_update_body(area, ent);
	 }
	 ent->vel[1] -= area->gravity;

	 g_entity_update(ent);

	 if (ent->update != NULL) {
	 ent->update(ent);
	 }

	 vec3_t pos = ent->transform.position;

	 pos[0] += ent->vel[0];
	 pos[1] += ent->vel[1];
	 pos[2] += ent->vel[2];

	 ent->vel[1] += area->gravity;


	 if (ent->body) {
	 if (ent->body->grounded) {
	 ent->vel[0] *= area->friction;
	 }
	 }
	 */
}

#include "../ent/g_think.h"

static void g_area_update_entity(GArea* area, GEntity* ent)
{
	if (!ent->name)
	{
		printf("UNNAMED entity!\n");
	}
	else
	{
		if (0 == strcmp(ent->name, "player"))
		{
			//printf("asdf");
		}
	}
	if (ent->think)
	{
		g_think_update(ent->think);
		///printf("DO SOMETHING\n");
	}

	g_entity_update(ent);
	if (ent->update != NULL)
	{
		ent->update(ent);
	}

	if (ent->body)
		g_area_update_body(area, ent);
}

static void g_area_update_entities(GArea* area)
{
	for (int i = 0; i < area->num_entities; ++i)
	{
		GEntity* ent = area->entities[i];
		if (ent == NULL)
			continue;
		g_area_update_entity(area, ent);
	}
}

void g_area_update(GArea* area)
{
	if (area == NULL)
	{
		grdn_log("nope!");
		return;
	}
	g_area_update_entities(area);
}

void g_area_draw_entity_list(GArea* area)
{
}

void g_area_draw_debug(GArea* area)
{

	int    num = area->num_entities;
	double w   = area->bounds.size.x;
	double h   = area->bounds.size.y;

	//double w   = app_settings.framebuffer_width;
	//double h   = app_settings.framebuffer_height;
	drw_push();
	drw_translate(w * -.3333, h * .333, 0);
	//drw_type_set_size(18, 18);
	drw_type_draw("%d entities.", num);
	//drw_translate(w*.5, h * -.333,0);
	drw_pop();

	drw_rect_w(area->bounds);
}

static void g_area_draw_entity(GEntity* entity)
{

	//	someone overrode the draw routine, they know what they're doing (maybe), do it and move on
	if (entity->draw)
	{
		entity->draw(entity);
		return;
	}

	RObject* art = entity->art;
	if (art)
	{
		drw_robject(art);
	}
	else
	{

		drw_push();
		drw_gtransform_apply(entity->transform);
		drw_square(32);
		/*drw_translate2f(obj->transform.position[0],
				      obj->transform.position[1]);
                         			drw_square(32);
			*/
		drw_pop();
	}
}

//
//	this is named as such because it simply draws the entities in the order
//	they were _added_ to the system, which is kinda dumb.
//
static void g_area_draw_naive(GArea* area)
{

	for (int i = 0; i < area->num_entities; ++i)
	{
		GEntity* obj = area->entities[i];
		if (obj == NULL)
		{
			grdn_log("warning: tried to draw NULL entity?");
			continue;
		}

		g_area_draw_entity(obj);
	}
}

static void calculate_layerindex(GArea* area)
{
}


#define TMP_TEST_SORT

void g_area_draw_layered(GArea* area)
{

	//	todo: this is incredibly naive atm, count them all, sort the indexes, iterate once
	//	per index (slow!) should pack them into a single iteration maybe, or maybe that takes
	//	just as long lol

	int* layers = NULL;

	GEntity** entities = area->entities;
	int       num      = area->num_entities;

	//	store available layers in a list.
	int nlayers = 0;
	for (int i = 0; i < num; i++)
	{
		GEntity* ent   = entities[i];
		int      layer = ent->layer;
		if (!layers)
		{
			nlayers++;
			layers    = calloc(1, sizeof(int));
			layers[0] = layer;
#ifdef TMP_TEST_SORT
			printf("First layer: %d\n", layer);
#endif
			continue;
		}
		bool in_index = false;
		for (int j = 0; j < nlayers; j++)
		{
			int tl = layers[j];
			if (tl == layer)
			{
				in_index = true;
				break;
			}
		}
		if (!in_index)
		{
			nlayers++;
			layers		    = realloc(layers, sizeof(int));
			layers[nlayers - 1] = layer;
#ifdef TMP_TEST_SORT
	printf("Unique layer: %d\n", layer);
#endif
		}
	}
	coer_sort_i(layers, nlayers);

#ifdef TMP_TEST_SORT
	printf("Counted %d layers.\n", nlayers);
	for (int i = 0; i < nlayers; i++)
	{
		printf("%d, ", layers[i]);
	}
	printf("\n");
#endif

	unsigned int w, h;
	drw_screensize_get(&w, &h);
	for (int i = 0; i < nlayers; i++)
	{
		
		for (int j = 0; j < num; j++)
		{
			if (entities[j]->layer == layers[i])
			{
				g_area_draw_entity(entities[j]);
			}
		}
		drw_color(.05,.1,.2,.11);
		drw_fill_set(true);
		drw_rect(0,0, w,h);
		drw_fill_pop();
		drw_color_pop();
	}
	
	free(layers);

}

void g_area_draw(GArea* area)
{

	g_area_draw_layered(area);
	//g_area_draw_naive(area);
	g_area_draw_debug(area);
}

#define DEFAULT_AREA_RECT 1024

GArea* g_area_create()
{
	GArea* area	= malloc(sizeof(GArea));
	area->entities     = NULL;
	area->num_entities = 0;
	area->friction     = 1. - .01;
	area->gravity      = -.1;
	area->flr	  = -.5;
	//g_area_populate_placeholder(area);
	wsh_rect_reset(&area->bounds);
	area->bounds.pos.x  = -DEFAULT_AREA_RECT * .5;
	area->bounds.pos.y  = -DEFAULT_AREA_RECT * .5;
	area->bounds.size.x = DEFAULT_AREA_RECT;
	area->bounds.size.y = DEFAULT_AREA_RECT;

	return area;
}

void g_area_destroy(GArea* area)
{
	//	TODO
	//	destroy entities
	for (int i = 0; i < area->num_entities; ++i)
	{
		GEntity* ent = area->entities[i];
		if (!ent)
		{
			printf("Something went wrong, null ent");
		}
		else
		{
			g_entity_destroy(ent);
		}
		// free(ent);
		area->entities[i] = NULL;
	}
	free(area);
}
/*
void g_area_populate_placeholder(GArea* area)
{
	for (int i = 0; i < 3; ++i)
	{
		GEntity* obj = g_entity_create("placeholder");
		obj->flags |= 4;
		g_area_register_entity(area, obj);
	}
}
*/
#ifdef DEBUG
static bool is_entity_already_in_system(GArea* area, GEntity* entity)
{
	for (unsigned int i = 0; i < area->num_entities; i++)
		if (area->entities[i] == entity)
			return true;

	return false;
}
#endif

static unsigned int find_first_available_entity_slot(GArea* area)
{
	for (unsigned int i = 0; i < area->num_entities; i++)
	{
		GEntity* ent = area->entities[i];
		if (ent == NULL)
			return i;
	}
	return -1;
}

void g_area_register_entity(GArea* area, GEntity* ent)
{
	if (!ent)
	{
		printf("Cowardly refusing to add a NULL entity.");
		return;
	}

#ifdef DEBUG
	if (ent->name == NULL)
	{
		grdn_log("Sneaky bugger, trying to add an entity with NO NAME");
	}

	if (is_entity_already_in_system(area, ent))
	{
		grdn_log("Entity already in system!");
	}
	if (!ent->destroy)
	{
		grdn_log("Warning: added an entity with no destroy callback set [%s]", ent->name);
	}
#endif

	unsigned int eslot = find_first_available_entity_slot(area);
	if (eslot != -1)
	{
		grdn_log("Simple reusing slot %d | %s", eslot, ent->name);
		area->entities[eslot] = ent;
	}

	grdn_log("Adding entity: %d %p %s", area->num_entities, ent, ent->name);
	area->num_entities++;

	if (area->entities == NULL)
	{
		//printf("No entities, mallocing...\n");
		area->entities = (GEntity**)calloc(1, sizeof(GEntity*));
	}
	else
	{
		area->entities = realloc(area->entities, sizeof(GEntity*) * (area->num_entities + 1));
	}
	grdn_log("realloc'd");
	ent->area = area;
	// area->entities = realloc(area->entities,)
	area->entities[area->num_entities - 1] = ent;
}

void g_area_unregister_entity(GArea* area, GEntity* obj)
{
	if (obj == NULL)
	{
#ifdef DEBUG
		grdn_log("Not removing a NULL object duh");
#endif
		return;
	}

	for (int i = 0; i < area->num_entities; i++)
	{
		GEntity* ent = area->entities[i];
		if (ent == obj)
		{
#ifdef DEBUG
			grdn_log("Match! removing: %s", obj->name);
#endif
			area->entities[i] = NULL;
		}
	}
}

void g_area_query_entities(GArea* area, GEntity* obj, int* query_type)
{
}
