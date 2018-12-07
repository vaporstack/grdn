
//  g_render_wsh.c
//  g_render_wsh
//
//  Created by Andrew Macfarlane on 04/12/18.
//  Copyright © 2018 vaporstack. All rights reserved.

#ifndef g_render_wsh_h_
#define g_render_wsh_h_

#include <wsh/src/geo/wsh_sequence.h>

typedef struct GRenderWsh
{
	WSequenceHnd* hnd;
	double pos;
	bool playing;
	double playback_speed;
	
} GRenderWsh;

GRenderWsh* g_render_wsh_create(WSequenceHnd* hnd);
void	g_render_wsh_destroy(GRenderWsh* wsh);

void g_render_playback_start(GRenderWsh* wsh);
void g_render_playback_stop(GRenderWsh* wsh);

void g_render_wsh_update(GRenderWsh * wsh);
void g_render_wsh_draw(GRenderWsh* wsh);

#endif
