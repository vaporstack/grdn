//
//  g_particle.h
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef g_particle_h
#define g_particle_h

#include <deps/gl-matrix/gl-matrix.h>

//	-------	old
enum ParticleSizeLifeOptions {
	PARTICLE_SIZE_LIFE_ENV,
	PARTICLE_SIZE_LIFE_CONST
};

enum ParticleLifeCurveOptions {
	PARTICLE_LIFE_CURVE_LINEAR,
	PARTICLE_LIFE_CURVE_EASE,
	PARTICLE_LIFE_CURVE_SIN
};

typedef struct Particle
{
	int  idx;
	bool alive;
	bool die;

	float birth;
	float life;
	float nlife;
	float death;
	float mass;
	float size;

	//vec3_t origin;
	vec3_t prev;
	vec3_t position;
	vec3_t velocity;
	vec3_t extra;
	vec3_t spin;
	vec3_t direction;
	vec3_t rotation;
	quat_t qdir;

	int size_over_life_type;

	void* data;
	void (*draw)(struct Particle*);

	// Vec3Line* trail;

} Particle;

typedef void (*particle_emit_place_func)(void* emitdata, Particle* p);

void      g_particle_reset(Particle* p);
void      g_particle_update(Particle* p);
Particle* g_particle_create(void);
void      g_particle_destroy(Particle* p);

#endif /* g_particle_h */
