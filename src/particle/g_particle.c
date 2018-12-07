//
//  g_particle.c
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "g_particle.h"

#include <r4/r4.h>

Particle* g_particle_create()
{
	Particle* p  = calloc(1, sizeof(Particle));
	p->idx       = -1;
	//p->origin  = vec3_create(NULL);
	p->position  = vec3_create(NULL);
	p->prev	 	=vec3_create(NULL);
	p->velocity  = vec3_create(NULL);
	p->extra     = vec3_create(NULL);
	p->direction = vec3_create(NULL);
	p->qdir      = quat_create(NULL);
	p->spin      = vec3_create(NULL);
	p->draw      = NULL;
	// p->rotation	    = vec3_create(NULL);
	p->size_over_life_type = PARTICLE_SIZE_LIFE_ENV;
	p->die		       = false;
	g_particle_reset(p);
	p->data = NULL;
	return p;
}
/*
static void zero(vec3_t* v)
{
	v[0] = v[1] = v[2] = 0;
}
*/

void g_particle_reset( Particle* p)
{
	p->alive = true;
	p->size  = 1;
	p->mass  = 1.0f;
	p->life  = 0.0f;
	p->death = 0.0f;
	p->die   = false;

	vec3_t zero = vec3_create(NULL);

	vec3_set(zero, p->prev);
	vec3_set(zero, p->position);
	vec3_set(zero, p->velocity);
	vec3_set(zero, p->extra);
	vec3_set(zero, p->spin);
	vec3_set(zero, p->direction);

	// vec3_set(p->rotation, zero);
	/*//p->position[0] = p->position[1] = p->position[2] = 0;
	zero(&p->velocity);
	zero(&p->position);
	zero(&p->extra);
	zero(&p->spin);
	zero(&p->direction);
	 
*/
	free(zero);
	p->birth = r_time();
}

void g_particle_destroy(Particle* p)
{
	
	free(p->prev);
	free(p->velocity);
	free(p->position);
	free(p->extra);
	free(p->spin);
	free(p->direction);
	free(p->qdir);
	// if ( p->data )
	//	free(p->data);
	// free(p->rotation);

	free(p);
}

static void _particle_update_size_from_life(Particle* p)
{
	switch (p->size_over_life_type) {
	case PARTICLE_LIFE_CURVE_LINEAR:
		p->size = p->life;
		break;
	case PARTICLE_LIFE_CURVE_EASE:
		break;
	case PARTICLE_LIFE_CURVE_SIN:
		break;
	default:
		break;
	}
}

void g_particle_update(Particle* p)
{
	
	// p->life = fabs( p->birth - p->death);
	if (p->size_over_life_type == PARTICLE_SIZE_LIFE_CONST) {
		return;
	} else if (p->size_over_life_type == PARTICLE_SIZE_LIFE_ENV) {

		_particle_update_size_from_life(p);
		return;

	} else {
		printf("Unhandled life size type!\n");
		return;
	}
}
