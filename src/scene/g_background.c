
//  g_background.c
//  g_background
//
//  Created by Andrew Macfarlane on 29/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_background.h"

#include <drw/drw.h>

//	todo: get rid of this!
#include <r4/r4.h>

#define STAR_BLOCK_WIDTH 8
#define HAZE_WIDTH 8
#define DUST_NUM 16
#define ATMOS_NUM 16

static double* star_raw = NULL;
//extern AppSettings app_settings;

#define ARBITRARY_NUMBER_TO_REPLACE_APP_WIDTH_AND_HEIGHT 256

GBackground* g_background_create(void)

{

	GBackground* bg = calloc(1, sizeof(GBackground));

	{
		// star stuff
		bg->stars	   = v_block_create(STAR_BLOCK_WIDTH);
		bg->star_brightness = 1.;
		bg->star_rotation   = 0;

		v_block_dist_sphere(bg->stars, 4096 * 8);

		star_raw = calloc(STAR_BLOCK_WIDTH * 3, sizeof(double));

		for (int i = 0, j = 0, k = 0; i < bg->stars->width;
		     i++, j += 2, k += 2)
		{
			//vec3_t point = bg->stars->data[i];
			VVec* point = &bg->stars->data[i];
			star_raw[i] = point->x;
			star_raw[j] = point->y;
			star_raw[k] = point->z;
		}
	}

	{
		// haze stuff
		bg->haze = v_block_create(HAZE_WIDTH);
	}

	bg->horizon.x = 0;
	//	TODO:
	//	grdn can't see the app any more
	bg->horizon.y = ARBITRARY_NUMBER_TO_REPLACE_APP_WIDTH_AND_HEIGHT; //app_settings.framebuffer_height;

	//g_particlesystem_preset_snow(bg->atmos);

	bg->precip = g_particlesystem_create(ATMOS_NUM);
	bg->atmos  = g_particlesystem_create(ATMOS_NUM);

	bg->dust = g_particlesystem_create(DUST_NUM);
	//g_particlesystem_preset_dust(bg->dust);
	//g_particlesystem_preset_rain(bg->precip);

	return bg;
}

void g_background_destroy(GBackground* bg)
{
	g_particlesystem_destroy(bg->dust);
	g_particlesystem_destroy(bg->atmos);
	g_particlesystem_destroy(bg->precip);
	v_block_destroy(bg->stars);
	v_block_destroy(bg->haze);
	free(bg);
}

int g_background_load(void)
{
	return 0;
}

static void _update_stars(GBackground* bg)
{
	bg->star_rotation += .1;
}

static void _update_haze(GBackground* bg)
{
	//TODO:
	//	grdn can't see the app any more.

	//double w = app_settings.framebuffer_width;
	// double h = w * .33;
	double w  = ARBITRARY_NUMBER_TO_REPLACE_APP_WIDTH_AND_HEIGHT;
	double xw = w / bg->haze->width;
	for (int z = 0; z < bg->haze->width; z++)
	{
		for (int x = 0; x < bg->haze->width; x++)
		{
			// double y = 0;
			double ax = (x * xw) + (w * -.5);
			double ay = 10 * (z + 1);
			double az = z * xw;
			if (z > 0)
			{
				VVec* prev =
				    v_block_get(bg->haze, x, 1, z - 1);
				double py = prev->y;
				ay += r_rand_double(NULL) * py;
			}
			v_block_set(bg->haze, x, 0, z, ax, 0, az);
			v_block_set(bg->haze, x, 1, z, ax, ay, az);
			// printf("hz point %d of layer %d is %f %f %f\n", x, z,
			// ax, ay, az); printf("bz point %d of layer %d is %f %f
			// %f\n", x, z, ax, 0.0, az);
		}
	}
}

void g_background_update(GBackground* bg)
{

	_update_stars(bg);
	_update_haze(bg);
	g_particlesystem_update(bg->atmos);
	g_particlesystem_update(bg->dust);
	g_particlesystem_update(bg->precip);
}

void g_background_draw_stars(GBackground* bg)
{
	static double r = 0;
	r += .1;
	drw_push();
	drw_rotate_y(45);
	drw_rotate_x(bg->star_rotation);

	for (int i = 0; i < bg->stars->len; ++i)
	{
		//vec3_t v = bg->stars->data[i];
		VVec* v = bg->stars->data[i];
		// drw_push();

		// drw_translate_vec3(v);
		// drw_rotate_x(90);
		// drw_rotate_x(r);
		// drw_rotate_y(r);
		// drw_square(256);
		//drw_point3f(v[0], v[1], v[2]);
		drw_point3f(v->x, v->y, v->z);
		// drw_pop();
	}

	drw_pop();

	// drw_rawpoints_3d(star_raw, bg->stars->len);
}

void g_background_draw_haze(GBackground* bg)
{
	drw_color(0, 1, 1, .3);
	/*
	 int w = bg->haze->width;

	for (int z = 0; z < bg->haze->width; z++)
	{
		RLine3* l = r_line3_create();

		for (int x = 0; x < w; x++)
		{
			vec3_t* b = v_block_get(bg->haze, x, 1, z);
			r_line3_add_point3f(l, *b[0], *b[1], *b[2]);
		}
		for (int x = w; x < 0; x--)
		{
			vec3_t* b = v_block_get(bg->haze, x, 0, z);
			r_line3_add_point3f(l, *b[0], *b[1], *b[2]);
		}

		drw_line3_r(l);
	}
*/

	/*

	//	todo? rewrite this to use arrays?

	//WLine* line = wsh_line_create();
	//r_set_fill(true);
	for ( int z = 0; z < bg->haze->width; z++ )
	{
		//double* arr = NULL;
		double* arr = calloc(w * 6, sizeof(double));
		for( int x = 0, i = 0; x < bg->haze->width; x++, i+=6 )
		{
			vec3_t *b = v_block_get(bg->haze, x, 0, z);
			vec3_t *v = v_block_get(bg->haze, x, 1, z);
			arr[i+0] = *b[0];
			arr[i+1] = *b[1];
			arr[i+2] = *b[2];
			arr[i+3] = *v[0];
			arr[i+4] = *v[1];
			arr[i+5] = *v[2];

		}
		drw_tris_3d(arr, w, true);

	}
	drw_fill_pop();
	*/
}

void g_background_draw(GBackground* bg)
{

	drw_color_u(1.);

	g_background_draw_stars(bg);

	g_particlesystem_draw(bg->atmos);
	g_particlesystem_draw(bg->dust);
	g_particlesystem_draw(bg->precip);
	// g_area_draw(_game->default_area);
}
