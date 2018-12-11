
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
	if (0 == strcmp(ent->name, "player"))
	{
		//printf("asdf");
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

void g_area_draw(GArea* area)
{

	for (int i = 0; i < area->num_entities; ++i)
	{
		GEntity* obj = area->entities[i];
		if (obj == NULL)
		{
			continue;
		}
		RObject* art = obj->art;
		if (art)
		{
			drw_robject(art);
		}
		else
		{

			drw_push();
			drw_gtransform_apply(obj->transform);
			drw_square(32);
			/*drw_translate2f(obj->transform.position[0],
				      obj->transform.position[1]);
                         			drw_square(32);
			*/
			drw_pop();
		}

		/*
		 if (app_settings.debug)
		{
			drw_line(0, 0, obj->transform.position[0], obj->transform.position[1]);

			drw_push();
			drw_gtransform_apply(obj->transform);
			drw_type_draw(obj->name);

			drw_axis();

			drw_pop();
		}
		 */

		// free(obj);
		// area->entities[i] = NULL;
	}

	//if (app_settings.debug)

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
	g_area_populate_placeholder(area);
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

void g_area_populate_placeholder(GArea* area)
{
	for (int i = 0; i < 3; ++i)
	{
		GEntity* obj = g_entity_create("placeholder");
		obj->flags |= 4;
		g_area_register_entity(area, obj);
	}
}

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

void g_area_register_entity(GArea* area, GEntity* obj)
{
	if (!obj)
	{
		printf("Cowardly refusing to add a NULL entity.");
		return;
	}

#ifdef DEBUG
	if (obj->name == NULL)
	{
		grdn_log("Sneaky bugger, trying to add an entity with NO NAME");
	}

	if (is_entity_already_in_system(area, obj))
	{
		grdn_log("Entity already in system!");
	}
	if (!obj->destroy)
	{
		grdn_log("Warning: added an entity with no destroy callback set");
	}
#endif

	unsigned int eslot = find_first_available_entity_slot(area);
	if (eslot != -1)
	{
		grdn_log("Simple reusing slot %d | %s", eslot, obj->name);
		area->entities[eslot] = obj;
	}

	grdn_log("Adding entity: %d %p %s", area->num_entities, obj, obj->name);
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
	obj->area = area;
	// area->entities = realloc(area->entities,)
	area->entities[area->num_entities - 1] = obj;
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
