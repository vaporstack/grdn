
//  g_camera.c
//  g_camera
//
//  Created by Andrew Macfarlane on 29/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_camera.h"

#include <drw/drw.h>

#include <stdlib.h>

//	todo: get rid of this!
#include <r4/r4.h>
#include <drw/drw.h>

static GEntity* current_cam = NULL;

GEntity* g_camera_create(void)
{
	GEntity* camera		= g_entity_create("g_camera");
	GCamera* cdata		= malloc(sizeof(GCamera));
	cdata->shake_enabled    = false;
	cdata->shake		= vec3_create(NULL);
	cdata->position		= vec3_create(NULL);
	cdata->shake_mag	= 2;
	cdata->shake_decay      = true;
	cdata->shake_decay_rate = 1 - .01;
	cdata->target		= NULL;
	camera->data		= cdata;
	current_cam		= camera;

	return camera;
}

GEntity* g_camera_get_cur()
{
	return current_cam;
}

void g_camera_destroy(GEntity* camera)
{
	free(camera->data);
	g_entity_destroy(camera);
}

void g_camera_apply(GEntity* camera)
{
	if ( !camera)
	{
		printf("No camera! %s\n", __func__);
		return;
	}
	
	drw_translate(-camera->transform.position[0], -camera->transform.position[1], -camera->transform.position[2]);
	GCamera* cdata = (GCamera*)camera->data;
	if (cdata->shake_enabled)
	{
		drw_translate_vec3(cdata->shake);
	}
	
	
}

void g_camera_deapply(GEntity* camera)
{
	if ( !camera)
	{
		printf("No camera! %s\n", __func__);
		return;
	}
	
	drw_translate(camera->transform.position[0], camera->transform.position[1], camera->transform.position[2]);
	GCamera* cdata = (GCamera*)camera->data;
	if (cdata->shake_enabled)
	{
		drw_translate(-cdata->shake[0], -cdata->shake[1], -cdata->shake[2]);
	}
}

void g_camera_set_target(GEntity* camera, vec3_t* target)
{
	GCamera* cdata = (GCamera*)camera->data;
	cdata->target  = target;
}

void g_camera_update(GEntity* camera)
{
	if ( !camera)
	{
		printf("No camera! %s\n", __func__);
		return;
	}
	
	GCamera* cdata = (GCamera*)camera->data;

	if (cdata->target)
	{
		vec3_t* b = cdata->target;
		vec3_t  a = camera->transform.position;
		//char*   buf = calloc(256, sizeof(char));
		//vec3_str(a, buf);
		// printf("a (cam) : %s\n", buf);
		//vec3_str(*b, buf);
		// printf("b (tgt) : %s\n", buf);
		// printf("ay by %f %f\n", a[1], *b[1]);
		double dx   = *b[0] - a[0];
		double dy   = *b[1] - a[1];
		double dz   = *b[2] - a[2];
		double frac = .1;
		dx *= frac;
		dy *= frac;
		dz *= frac;
		camera->transform.position[0] += dx;
		camera->transform.position[1] += dy;
		camera->transform.position[2] += dz;
		// printf("%f %f\2n", dx, dy);
	}
	if (cdata->shake_decay)
	{

		cdata->shake_mag = cdata->shake_mag * cdata->shake_decay_rate;
		//cdata->shake[1] *= cdata->shake_decay_rate;
		//cdata->shake[2] *= cdata->shake_decay_rate;
	}
	if (cdata->shake_enabled)
	{
		cdata->shake[0] = (-.5 + r_rand_double(NULL)) * cdata->shake_mag;
		cdata->shake[1] = (-.5 + r_rand_double(NULL)) * cdata->shake_mag;
		cdata->shake[2] = (-.5 + r_rand_double(NULL)) * cdata->shake_mag;
	}
	// camera->data[1] = r_rand_double(NULL) * cdata->shake_mag;
	// camera->data[2] = r_rand_double(NULL) * cdata->shake_mag;
}
