//
//  g_particle_emitter.h
//  grdn
//
//  Created by vs on 11/20/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef g_particle_emitter_h
#define g_particle_emitter_h

#include "g_particle.h"

typedef enum
{
	G_PARTICLE_EMIT_NUM_PER_FRAME,
	G_PARTICLE_EMIT_ON_TIMER,
	G_PARTICLE_EMIT_RANDOMCHANCE
} G_PARTICLE_PERIODICITY_TYPE;

typedef struct GParticleEmitter
{
	void*			 sys;
	int			 type;
	vec3_t			 position;
	vec3_t			 bounds;
	particle_emit_place_func place;
	particle_emit_place_func aim;

	// int    num_to_emit;
	int    emission_periodicity_setting;
	int    particles_per_emit;
	double particle_timer;
	double last_emit;
	double random_chance;
	bool   randomize_num_on_emit;
	int    randomize_num_amt;

} GParticleEmitter;

//	some presets that will hopefully become handier over time
GParticleEmitter* g_particle_emitter_create_point(void* sys);
GParticleEmitter* g_particle_emitter_create_box(void* sys, double x, double y, double z);
GParticleEmitter* g_particle_emitter_create_sphere(void* sys, double x, double y, double z);

GParticleEmitter* g_particle_emitter_create(void* sys);
void		  g_particle_emitter_destroy(GParticleEmitter* emit);
void		  g_particle_emitter_set_bounds(GParticleEmitter* emit, double x, double y,
						double z);
void		  g_particle_emitter_set_pos(GParticleEmitter* emit, double x, double y,
					     double z);

#endif /* g_particle_emitter_h */
