//
//  g_dialog.c
//  r4_ios
//
//  Created by Andrew Macfarlane on 1/25/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "g_dialog.h"

#include <stdbool.h>

#include <stdlib.h>
#include <string.h>

//#include "../../../r4/src/geo/r_rect.h"

// BBox (const wchar_t *string, float &llx, float &lly, float &llz, float &urx,
// float &ury, float &urz)

DialogBox* g_dialog_create(float x, float y, char* text)
{
	DialogBox* box    = malloc(sizeof(DialogBox));
	box->position.x   = x;
	box->position.y   = y;
	box->text	 = text;
	box->verts	= NULL;
	box->needs_update = true;
	box->bounds       = NULL;
	box->pad_size     = 32;

	return box;
}

void g_dialog_destroy(DialogBox* box)
{
	if (box->verts)
	{
		free(box->verts);
	}
	// drw_rect_destroy(box->bounds);
	free(box);
	box = NULL;
}

void g_dialog_update(DialogBox* box)
{
	/*
	//float data[6];
	float* data = malloc(sizeof(float) * 6);
	int num = (int)strlen(box->text);

	float sz = box->pad_size;
	drw_text_get_bbox(box->text, num, data);
	float ax = data[0];
	float ay = data[1];
	//float az = data[2];
	float bx = data[3];
	float by = data[4];
	//float bz = data[5];

	ax -= sz;
	ay -= sz;
	bx += sz;
	by += sz;
	RRect* r = drw_rect_create(ax, ay, bx, by);
	box->bounds = r;

	float* vdata = malloc(sizeof(float) * 14);

	float dx = (bx - ax) - sz;
	float px = r_rand_double(NULL) * dx;

	//px = sz;
	printf("point delta %f\n", dx);


	vdata[0] = ax;
	vdata[1] = ay;

	vdata[2] = ax;
	vdata[3] = by;

	vdata[4] = bx;
	vdata[5] = by;

	vdata[6] = bx;
	vdata[7] = ay;

	vdata[8] = px;
	vdata[9] = ay;

	vdata[10] = px;
	vdata[11] = ay - sz;

	vdata[12] = px - sz + (.5*.375f);
	vdata[13] = ay;


	box->verts = vdata;
	box->vert_num = 14;


	box->needs_update = false;


	box->position.x = r_rand_double(NULL) * 20;
	box->position.y = r_rand_double(NULL) * 20;

	free(data);
	*/
}

//#define MY_STRINGS_NUM 2
// const char* strings[MY_STRINGS_NUM] = {"hello there","is it time","is it time
// for dialog boxes", "hello my friend"};

void g_dialog_set_text(DialogBox* box, const char* text)
{

	box->text	 = text;
	box->needs_update = true;
	// g_dialog_destroy(box);
	// box = g_dialog_create(<#float x#>, <#float y#>, <#char *text#>)
}
void g_dialog_render(DialogBox* box)
{
	/*
	CAN"T CALL A LIBRARY THAT CALLS US
	//r_scale_x(-1);
	if ( box->needs_update || !box->bounds )
		g_dialog_update(box);


	//static int counter = 0;
	if ( r_rand_double(NULL) < .01 ){

		box->needs_update = true;
	}

	//	dumb for now, good to keep motivated
	drw_push();
	//	shift to origin point
	drw_translate_vec2(&box->position);
	drw_translate_y(box->pad_size * 2);
	drw_translate_x(-box->verts[8]);
	r_rawpoly(box->verts, box->vert_num, true);
	drw_text(box->text);
	drw_pop();
	//r_scale_x(-1);

	*/
}
