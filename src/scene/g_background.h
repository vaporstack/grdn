
//  g_background.c
//  g_background
//
//  Created by Andrew Macfarlane on 29/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_background_h_
#define g_background_h_

#include "../particle/g_particlesystem.h"
//#include "../particle/g_particle_presets.h"
#include <vbl/src/geo/v_block.h>

typedef struct GBackground
{
	ParticleSystem* atmos;
	ParticleSystem* dust;
	ParticleSystem* precip;
	VBlock*		haze;
	VBlock*		stars;
	float		star_brightness;
	float		star_rotation;
	RPoint		horizon;

	//	todo, add colors based on time of day?

} GBackground;

GBackground* g_background_create(void);
void	 g_background_destroy(GBackground* bg);

int  g_background_load(void); // todo, make this do stuff?
void g_background_update(GBackground* bg);
void g_background_draw(GBackground* bg);

void g_background_draw_haze(GBackground* bg);
void g_background_draw_stars(GBackground* bg);

#endif
