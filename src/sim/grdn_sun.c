//
//  grdn_sun.c
//  grdn
//
//  Created by vs on 7/2/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "grdn_sun.h"
#include <drw/drw.h>

static void draw(GEntity* ent )
{
	drw_blend_set(DRW_BLEND_MODE_NORMAL);
	
	drw_push();
	drw_translate(64,64, 0);
	drw_fill_set(true);
	GSun* info = ent->data;
	double v = info->output;
	drw_color(1,1,0,v);
	drw_circle(64);
	drw_fill_pop();
	drw_pop();
	
	
	drw_blend_pop();
}


static void update(GEntity* ent)
{
	GSun* info = ent->data;
	
	double t = r_time();
	double v = .5 + (.5 * cos(t / info->period));
	
	printf("%.3f\n", v);
	
	
	info->output = v;
	//printf("+");
	
}

GEntity* grdn_sun_create(void)
{
	GEntity* sun = g_entity_create("sun");
	GSun* info = calloc(1, sizeof(GSun));
	
	info->period = 5;
	info->intensity = .5;
	
	sun->draw = draw;
	sun->data = info;
	
	sun->update = update;
	
	return sun;
}
