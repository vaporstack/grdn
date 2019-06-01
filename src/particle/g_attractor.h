//
//  g_particle.h
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef r_attractor_h_
#define r_attractor_h_

//
//#include <r4/r4.h>
//#include "../../../wsh/wsh.h"
//#ifdef DISALLOW_WHILE_VEC3_REFACTOR

#include <gl-matrix/gl-matrix.h>

#include "g_particle.h"

typedef struct ParticleAttractor
{
	vec3_t position;
	float  mass;
	float  gravity;
} ParticleAttractor;

struct Particle;

struct ParticleAttractor* p_attractor_create(void);
void			  p_attractor_destroy(ParticleAttractor*);

void p_attractor_apply(ParticleAttractor*, struct Particle* p);

//#endif

#endif /* r_attractor_h_ */
