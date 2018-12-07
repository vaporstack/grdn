//
//  g_particle.c
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "g_attractor.h"

#include <linalg.h>
#include <clamp/clamp.h>

#include <assert.h>

#define verbose false
#ifdef DISALLOW_WHILE_VEC3_REFACTOR

ParticleAttractor* p_attractor_create()
{
	ParticleAttractor* attr = malloc(sizeof(ParticleAttractor));
	vec3_reset(&attr->position);
	attr->mass    = 50.0f;
	attr->gravity = 1.0f;

	attr->position.z = 64;
	attr->position.x = 32;
	attr->position.y = 8;
	printf("Created an attractor with mass: %f\n", attr->mass);
	return attr;
}

void p_attractor_destroy(ParticleAttractor* attr) { free(attr); }

void p_attractor_apply(ParticleAttractor* attr, struct Particle* p)
{

	//	dumb.  override TODO
	attr->mass    = 20.0;
	attr->gravity = 1.0f;
	vec3_t pos    = p->position;
	vec3_t src    = vec3_new(pos);

	pos	= attr->position;
	vec3_t dst = vec3_new(pos);

	// assert(!isnan(dst.x));

	if (verbose)
		printf("dst    :%.2f %.2f %.2f\n", dst.x, dst.y, dst.z);

	///	dst.x = clamp(dst.x, 5, 1024);
	// dst.y = clamp(dst.y, 5, 1024);
	// dst.z = clamp(dst.z, 5, 1024);

	v3 force = v3sub(dst, src);
	if (force.x == 0.0f && force.y == 0.0f && force.y == 0.0f)
		return;

	float dist = v3len(force);
	if (verbose)
		printf("forc1  :%.2f %.2f %.2f\n", force.x, force.y, force.z);

	force = v3unit(force);
	// assert(!isnan(force.x));

	if (verbose)
		printf("forc2  :%.2f %.2f %.2f\n", force.x, force.y, force.z);

	float strength = (attr->gravity * attr->mass * p->mass) / (dist * dist);

	if (verbose)
		printf("str    :%.2f\n", strength);
	force = v3mul(force, strength);
	if (verbose)
		printf("forc3  :%.2f %.2f %.2f\n", force.x, force.y, force.z);

	//	divide by the particle's G
	force = v3div(force, p->mass);

	p->velocity.x += force.x;
	p->velocity.y += force.y;
	p->velocity[2] += force.z;

	if (verbose)
		printf("vel  :%.2f %.2f %.2f\n", p->velocity.x, p->velocity.y,
		       p->velocity[2]);

	/*
		v3 unit = v3unit(dist);


		printf("dist :%.2f %.2f %.2f\n", dist.x, dist.y, dist.z);
		printf("unit :%.2f %.2f %.2f\n", unit.x, unit.y, unit.z);

		float adist = v3dist(src, dst);
		float force = (attr->gravity * attr->mass * p->mass ) / (adist *
	   adist);

		v3 res = v3mul(force, unit);

		v3 divved = v3div(res, p->mass);


		//p->pos.x *= force;
		//v3 res = v3mult(src, )
		//
		//printf("-%f %f %f\n", dir.x, dir.y, dir.z);
		//v = p->position;

		//vec3_t dst = attr->position;
		*/
}

#endif
