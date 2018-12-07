
//  g_particle_affector.c
//  g_particle_affector
//
//  Created by Andrew Macfarlane on 11/21/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_particle_affector.h"

GParticleAffector* g_particle_affector_create(void)
{
	return calloc(1, sizeof(GParticleAffector));
}
