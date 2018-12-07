
//  g_particle_affector.c
//  g_particle_affector
//
//  Created by Andrew Macfarlane on 11/21/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_particle_affector_h_
#define g_particle_affector_h_

#include "g_particle.h"
typedef void (*particle_affect)(void* sys, void* affector, Particle* p);

typedef struct GParticleAffector
{
	particle_affect on_birth;
	particle_affect on_update;
	particle_affect on_death;
	void*		data;
} GParticleAffector;

GParticleAffector* g_particle_affector_create(void);

#endif
