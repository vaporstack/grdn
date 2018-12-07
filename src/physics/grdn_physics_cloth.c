//
//  grdn_physics_cloth.c
//  grdn
//
//  Created by vs on 3/23/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "grdn_physics_cloth.h"

#include <drw/drw.h>
#include <r4/r4.h>

#ifdef R4_DEBUG
#include <stdio.h>
#endif

extern AppSettings   app_settings;
extern DebugSettings debug_settings;

#pragma mark internal

static void	  point_destroy(GCPoint* p);
static void	  grdn_physics_cloth_point_update(GCPoint* p, double d);
static void	  point_resolve_constraints(GCPoint* p);
static void	  point_remove_constraint(GCPoint* p, GCConstraint* con);
static GCConstraint* constraint_create(GCPoint* a, GCPoint* b);
static void	  constraint_resolve(GCConstraint* con);
static void	  constraint_resolve(GCConstraint* con);
static void	  constraint_draw(GCConstraint* con);
#pragma mark	 point

//	todo: integrate these into a space of some sort
static int    physics_accuracy = 5;
static double mouse_influence  = 20;
static double mouse_cut	= 5;
static double gravity	  = -2;
static double cloth_height     = 10;
static double cloth_width      = 10;
static double start_y	  = 50;
static double spacing	  = 32;
static double tear_distance    = 60;

GCPoint* grdn_physics_cloth_point_create(double x, double y)
{
	GCPoint* p     = calloc(1, sizeof(GCPoint));
	p->x	   = x;
	p->y	   = y;
	p->px	  = x;
	p->py	  = y;
	p->vx	  = 0;
	p->vy	  = 0;
	p->pin_x       = NULL;
	p->pin_y       = NULL;
	p->constraints = NULL;
	p->ncons       = 0;
	return p;
}

static void point_destroy(GCPoint* p)
{
	if (p->pin_x)
		free(p->pin_x);
	if (p->pin_y)
		free(p->pin_y);
	free(p);
}

static void point_resolve_constraints(GCPoint* p)
{
	if ((p->pin_x != NULL) && (NULL != p->pin_y))
	{
		p->x = *(p->pin_x);
		p->y = *(p->pin_y);
		return;
	}

	int i = p->ncons;
	while (i--)
		constraint_resolve(p->constraints[i]);

	double w = app_settings.framebuffer_width * .5;
	double h = app_settings.framebuffer_height * .5;

	if (p->x > w)
	{
		p->x = w - p->x;
	}
	if (p->x < -w)
	{
		p->x = -w + p->x;
	}
	if (p->y < -h)
	{
		p->y = -h + p->y;
	}
	if (p->y > h)
	{
		p->y = h - p->y;
	}

	//if ( p->x > )
	//todo: bounds check?  that would require us to define a space
	//	maybe later

	//    this.x > boundsx ? this.x = 2 * boundsx - this.x : 1 > this.x && (this.x = 2 - this.x);
	//    this.y < 1 ? this.y = 2 - this.y : this.y > boundsy && (this.y = 2 * boundsy - this.y);
}

void grdn_physics_cloth_point_attach(GCPoint* a, GCPoint* b)
{
	GCConstraint* con = constraint_create(a, b);
	a->ncons++;
	if (a->constraints == NULL)
	{
		a->constraints = calloc(1, sizeof(GCConstraint));
	}
	else
	{
		a->constraints = realloc(a->constraints, a->ncons * sizeof(GCConstraint));
	}
	a->constraints[a->ncons - 1] = con;
}

void grdn_physics_cloth_point_draw(GCPoint* p)
{
	if (p->ncons == 0)
		return;
	int i = p->ncons;
	while (i--)
	{
		constraint_draw(p->constraints[i]);
	}
}

void grdn_physics_cloth_point_update(GCPoint* p, double delta)
{

	static double pmx = 0;
	static double pmy = 0;
	static double mx  = 0;
	static double my  = 0;
	mx		  = app_settings.primary_cursor_x;
	my		  = app_settings.primary_cursor_y;

	if (app_settings.primary_cursor_down)
	{
		double dx = p->x - mx;
		double dy = p->y - my;
		double d  = sqrt(dx * dx + dy * dy);

		if (app_settings.primary_cursor_button == 0)
		{
			if (d < mouse_influence)
			{
				p->px = p->x - (mx - pmx) * 1.8;
				p->py = p->y - (my - pmy) * 1.8;
			}
		}
		else if (d < mouse_cut)
		{
			free(p->constraints);
		}
	}
	pmx = mx;
	pmy = my;

	grdn_physics_cloth_point_add_force(p, 0, gravity);

	delta *= delta;
	double nx = p->x + ((p->x - p->px) * .99) + ((p->vx / 2) * delta);
	double ny = p->y + ((p->y - p->py) * .99) + ((p->vy / 2) * delta);

	p->px = p->x;
	p->py = p->y;

	p->x  = nx;
	p->y  = ny;
	p->vx = p->vy = 0;
}

static void point_remove_constraint(GCPoint* p, GCConstraint* con)
{
	int found = -1;
	int i     = p->ncons;
	while (i--)
	{
		if (p->constraints[i] == con)
		{
			found = i;
		}
	}
	printf("found constraint at %d\n", found);

	//do something
}

void grdn_physics_cloth_point_add_force(GCPoint* p, double x, double y)
{
	p->vx += x;
	p->vy += y;
}

void grdn_physics_cloth_point_pin(GCPoint* p, double x, double y)
{
	static int count = 0;
	count++;

	printf("pin count! %d\n", count);
	if (p->pin_x)
		free(p->pin_x);
	if (p->pin_y)
		free(p->pin_y);
	p->pin_x    = calloc(1, sizeof(float));
	p->pin_y    = calloc(1, sizeof(float));
	*(p->pin_x) = x;
	*(p->pin_y) = y;
}

#pragma mark constraint

static GCConstraint* constraint_create(GCPoint* a, GCPoint* b)
{
	GCConstraint* con = calloc(1, sizeof(GCConstraint));
	con->a		  = a;
	con->b		  = b;
	con->length       = spacing;
	return con;
}

static void constraint_resolve(GCConstraint* con)
{
	GCPoint* a    = con->a;
	GCPoint* b    = con->b;
	double   dx   = a->x - b->x;
	double   dy   = a->y - b->y;
	double   dist = sqrt(dx * dx + dy * dy);
	double   diff = (con->length - dist) / dist;
	if (dist > tear_distance)
		point_remove_constraint(a, con);
	double px = dx * diff * .5;
	double py = dy * diff * .5;

	a->x += px;
	a->y += py;
	b->x -= px;
	b->y -= py;
}

static void constraint_draw(GCConstraint* con)
{
	drw_line(con->a->x, con->a->y, con->b->x, con->b->y);
}

#pragma mark cloth

GCCloth* grdn_physics_cloth_create(unsigned int w, unsigned int h)
{
	GCCloth* cloth = calloc(1, sizeof(GCCloth));

#ifdef DEBUG
	printf("Creating cloth:\n");
#endif

	//unsigned int num = 0;
	cloth->points = NULL;
	cloth->num    = 0;

	double start_x = w / 2 - cloth_width * spacing / 2;
	for (int y = 0; y < cloth_height; y++)
	{
		for (int x = 0; x <= cloth_width; x++)
		{
			cloth->num++;
			if (!cloth->points)
			{
				cloth->points = calloc(1, sizeof(GCPoint));
			}
			else
			{
				cloth->points = realloc(cloth->points, cloth->num * sizeof(GCPoint));
			}
			GCPoint* p		      = grdn_physics_cloth_point_create(start_x + x * spacing, start_y + y * spacing);
			cloth->points[cloth->num - 1] = p;

			if (x != 0)
			{
				grdn_physics_cloth_point_attach(p, cloth->points[cloth->num - 2]);

				printf("Attached point %llu to point %llu\n", cloth->num - 1, cloth->num - 2);
			}
			if (y == 0)
			{
				if (x % 4 == 0)
					grdn_physics_cloth_point_pin(p, p->x, p->y);
			}
			else
			{
				unsigned long long ix = x + (y - 1) * (cloth_width + 1);
				grdn_physics_cloth_point_attach(p, cloth->points[ix]);
				printf("Attached point %llu to point %llu\n", cloth->num - 1, ix);
			}
		}
	}

#ifdef R4_DEBUG
	printf("Created cloth with %llu points\n", cloth->num);
#endif
	//cloth->num = num;
	return cloth;
}

void grdn_physics_cloth_update(GCCloth* cloth)
{

	int i = physics_accuracy;
	while (i--)
	{
		unsigned long long p = cloth->num;
		while (p--)
		{
			if (p == 12)
			{
				//printf("creepin on 12\n");
			}
			point_resolve_constraints(cloth->points[i]);
		}
	}
	unsigned long long i2 = cloth->num;
	while (i2--)
	{
		grdn_physics_cloth_point_add_force(cloth->points[i2], (-.5 + r_rand_double(NULL)) * 4, 0);
		grdn_physics_cloth_point_update(cloth->points[i2], 0.16);
	}
}

void grdn_physics_cloth_draw(GCCloth* cloth)
{
	unsigned long long i = cloth->num;
	while (i--)
	{
		grdn_physics_cloth_point_draw(cloth->points[i]);
	}
}

void grdn_physics_cloth_destroy(GCCloth* cloth)
{
	for (int i = 0; i < cloth->num; i++)
	{
		point_destroy(cloth->points[i]);
	}
	free(cloth->points);
	//free(cloth);
}
