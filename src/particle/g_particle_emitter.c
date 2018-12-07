//
//  g_particle_emitter.c
//  grdn
//
//  Created by vs on 11/20/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "g_particle_emitter.h"

#include <r4/r4.h>

#include "g_particle_system.h"
#include <stdlib.h>

//	fallback, box, random, bad

static void no_motion(void* emitd, Particle* p)
{
	p->velocity[0] = 0;
	p->velocity[1] = 0;
	p->velocity[2] = 0;
}

static void vertical_y_only(void* emitd, Particle* p)
{
	p->velocity[0] = 0;
	p->velocity[1] = 1;
	p->velocity[2] = 0;
	p->spin[1]     = 1;
	p->spin[0]     = .5;
}

static void point_place(void* emitd, Particle* p)
{
	GParticleEmitter* emitter = (GParticleEmitter*)emitd;
	//printf("Emitter has %f %f %f\n", emitter->position[0], emitter->position[1], emitter->position[2]);
	
	//p->position =
	vec3_set( emitter->position, p->position);
}

static void random_box_place(void* emitd, Particle* p)
{
	GParticleEmitter* emitter = (GParticleEmitter*)emitd;
	// Particle*	p       = g_particle_create();
	// double foo     = r_rand_double(NULL);
	p->position[0] = (-.5 + r_rand_double(NULL)) * emitter->bounds[0];
	p->position[1] = (-.5 + r_rand_double(NULL)) * emitter->bounds[1];
	p->position[2] = (-.5 + r_rand_double(NULL)) * emitter->bounds[2];
	p->position = vec3_add(p->position, emitter->position, NULL);
}

static void on_sphere_place(void* emitd, Particle* p)
{
	GParticleEmitter* emitter = (GParticleEmitter*)emitd;

	//	from:
	//	https://stackoverflow.com/questions/5531827/random-point-on-a-given-sphere/15048260#15048260
	bool   proceed = false;
	double x, y, z;
	x = y = z = 0;
	while (!proceed)
	{

		x = -.5 + r_rand_double(NULL);
		y = -.5 + r_rand_double(NULL);
		z = -.5 + r_rand_double(NULL);
		if (x * x + y * y + z * z <= 1)
			proceed = true;
	}

	double d = sqrt(x * x + y * y + z * z);

	x /= d;
	y /= d;
	z /= d;

	GParticleSystem* sys = emitter->sys;

	x *= sys->emitter->bounds[0];
	y *= sys->emitter->bounds[1];
	z *= sys->emitter->bounds[2];
	p->position[0] = x;
	p->position[1] = y;
	p->position[2] = z;
}

GParticleEmitter* g_particle_emitter_create_point(void* data)
{
	GParticleEmitter* emit = g_particle_emitter_create(data);
	emit->bounds[0] = emit->bounds[1] = emit->bounds[2] = 0;
	emit->place = point_place;
	
	GParticleSystem* sys = (GParticleSystem*)data;
	
	sys->emitter = emit;
	
	return emit;
}

GParticleEmitter* g_particle_emitter_create_box(void* data, double x, double y, double z)
{
	GParticleEmitter* emit = g_particle_emitter_create(data);
	emit->bounds[0] = x;
	emit->bounds[1] = y;
	emit->bounds[2] = z;
	
	emit->place = random_box_place;
	
	//GParticleSystem* sys = (GParticleSystem*)data;
	
	//sys->emitter = emit;
	return emit;
	
}

GParticleEmitter* g_particle_emitter_create_sphere(void* data, double x, double y, double z)
{
	GParticleEmitter* emit = g_particle_emitter_create(data);
	emit->bounds[0] = x;
	emit->bounds[1] = y;
	emit->bounds[2] = z;
	
	emit->place = on_sphere_place;
	
	//GParticleSystem* sys = (GParticleSystem*)data;
	
	/////sys->emitter = emit;
	return emit;
	
}

GParticleEmitter* g_particle_emitter_create(void* sys)
{
	GParticleEmitter* emitter = calloc(1, sizeof(GParticleEmitter));

	emitter->sys       = sys;
	emitter->position  = vec3_create(NULL);
	emitter->bounds    = vec3_create(NULL);
	emitter->bounds[0] = 128;
	emitter->bounds[1] = 128;
	emitter->bounds[2] = 128;

	emitter->particle_timer = .5;
	// emitter->place		= random_box_place;
	emitter->place = random_box_place;
	emitter->aim   = no_motion;

	// if (func) {
	//	emitter->place = func;
	//} else {

	//	emitter->place = random_box_place;
	//}
	// emitter->emission_periodicity_setting =
	// G_PARTICLE_EMIT_NUM_PER_FRAME;  emitter->emission_periodicity_setting
	// = G_PARTICLE_EMIT_ON_TIMER;
	// emitter->emission_periodicity_setting = G_PARTICLE_EMIT_RANDOMCHANCE;
	emitter->emission_periodicity_setting = G_PARTICLE_EMIT_ON_TIMER;

	emitter->particles_per_emit    = 1;
	emitter->random_chance	 = .02;
	emitter->randomize_num_on_emit = false;
	emitter->randomize_num_amt     = 3;

	return emitter;
}

void g_particle_emitter_destroy(GParticleEmitter* emitter)
{
	free(emitter->bounds);
}

void g_particle_emitter_set_bounds(GParticleEmitter* emit, double x, double y,
				   double z)
{
	emit->bounds[0] = x;
	emit->bounds[1] = y;
	emit->bounds[2] = z;
}
void g_particle_emitter_set_pos(GParticleEmitter* emit, double x, double y,
				double z)
{
	emit->position[0] = x;
	emit->position[1] = y;
	emit->position[2] = z;
}
