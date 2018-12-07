
//  g_render_wsh.c
//  g_render_wsh
//
//  Created by Andrew Macfarlane on 04/12/18.
//  Copyright © 2018 vaporstack. All rights reserved.

#include "g_render_wsh.h"
#include <drw/drw.h>

//	todo: get rid of this!
#include <r4/r4.h>

GRenderWsh* g_render_wsh_create(WSequenceHnd* hnd)
{
	GRenderWsh* rec     = calloc(1, sizeof(GRenderWsh));
	rec->hnd	    = hnd;
	rec->pos	    = 0;
	rec->playing	= true;
	rec->playback_speed = 1;
	return rec;

}

void g_render_wsh_destroy(GRenderWsh* wsh)
{
	free(wsh);
}

void g_render_playback_start(GRenderWsh* wsh)
{
}
void g_render_playback_stop(GRenderWsh* wsh)
{
}
void g_render_wsh_update(GRenderWsh* wsh)
{
	if ( !wsh )
	{
		printf("Error, tried to update a null wash!\n");
		return;
	}
	wsh->pos = fmod(r_time() * wsh->playback_speed, 1);
	int cfi  = wsh->pos * wsh->hnd->src->num_frames;
	if (cfi < 0)
	{
		//printf("Illegal CFI! (lo)\n");
		cfi = 0;
	}
	if (cfi >= wsh->hnd->src->num_frames)
	{
		//printf("Illegal CFI! (hi)\n");
		cfi = wsh->hnd->src->num_frames - 1;
	}
	wsh->hnd->src->current_frame_index = cfi;
	wsh->hnd->src->current_frame       = wsh->hnd->src->frames[cfi];
}

void g_render_wsh_draw(GRenderWsh* wsh)
{
	WSequence* seq = wsh->hnd->src;
	//int num = seq->num_frames;
	//int pos = wsh->pos * num;

	WObject* frame = seq->current_frame;

	//drw_push();
	//drw_scale_u(128);

	//drw_color(0,1,1,1);
	//drw_line(0,0,seq->bounds.pos.x, seq->bounds.pos.y);
	//drw_rect_w(seq->bounds);

	//drw_color(1,0,0,1);
	//drw_rect_w(frame->bounds);

	//drw_color(1,0,1,1);
	drw_set_colorbypass(true);
	//drw_wobject_notransform(frame);
	drw_wobject(frame);
	//drw_wobject_verts(frame);
	drw_set_colorbypass(false);
	//drw_pop();
}
