//
//  g_particle_system.c
//  grdn
//
//  Created by vs on 11/21/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#include "g_particle_system.h"
#include <r4/r4.h>

#include <drw/drw.h>


// static void g_particle_system_update_particles(GParticleSystem* sys);

void set_particle_death(GParticleSystem* sys, GParticleAffector* affect,
			Particle* p)
{
}
/*
Particle* g_particle_system_emit(GParticleSystem* sys)
{
	return NULL;
}
*/
GParticleSystem* g_particle_system_create(int _max)
{
	GParticleSystem* sys = calloc(1, sizeof(GParticleSystem));
	sys->max	     = _max;
	sys->data	    = calloc(_max, sizeof(Particle));

	sys->position = vec3_create(NULL);
	sys->bounds   = vec3_create(NULL);
	sys->gravity  = vec3_create(NULL);
	sys->wind     = vec3_create(NULL);

	sys->size  = 1;
	sys->emitting	= false;
	sys->reuse_particles = false;
	sys->bound_type = GPARTICLE_BOUND_BOX;
	
	sys->size_over_life_type = PARTICLE_SIZE_LIFE_CONST;
	sys->death = 5;
	sys->num = sys->max;
	// set up death funcs
	GParticleAffector* affect = g_particle_affector_create();
	affect->on_birth	  = set_particle_death;

	//sys->emitter = g_particle_emitter_create(sys);
	// double death = 3;
	// affect->data			    = (void*)

	// sys->particles_per_emit	  = 1;

	for (int i = 0; i < _max; i++)
	{
		// Particle* p  = g_particle_create();
		sys->data[i] = NULL;
	}

	printf("Created system with %d particles.\n", _max);

	return sys;
}

void g_particle_system_destroy(GParticleSystem* sys)
{
	if (!sys)
	{
		printf("Tried to destroy a null particle sys :(\n");
		return;
	}
	free(sys->data);
	free(sys->position);
	free(sys->bounds);
	free(sys->gravity);
	free(sys->wind);
	free(sys);
}

static int determine_particles_to_emit(GParticleSystem* sys)
{
	// return sys->emitter->particles_per_emit;

	int num = sys->emitter->particles_per_emit;
	if (sys->emitter->randomize_num_on_emit)
	{
		num +=
		    .5 + r_rand_double(NULL) * sys->emitter->randomize_num_amt;
	}
	return num;
	/*
	switch (sys->emitter->emission_periodicity_setting) {
		case G_PARTICLE_EMIT_NUM_PER_FRAME: {
			return sys->emitter->particles_per_emit;
			break;
		}
		case G_PARTICLE_EMIT_ON_TIMER: {
			return sys->emitter->particles_per_emit;
			break;
		}
		case G_PARTICLE_EMIT_RANDOMCHANCE: {
			return sys->emitter->particles_per_emit;
			break;
		}
		default:
			return 0;
			break;
	}
	 */
}

static int find_next_available_particle(GParticleSystem* sys)
{
	if ( sys->reuse_particles )
	{
		//easy, it's "the next one";
		
		if ( sys->cur+1 >= sys->max )
			return 0;
		
		return sys->cur +1;
		
	}
	
	// int res = -1;
	for (int i = 0; i < sys->max; i++)
	{
		if (sys->data[i] == NULL)
			return i;
	}
	return -1;
}

static void emit_particle(GParticleSystem* sys, Particle* p)
{
}

Particle* g_particle_system_emit(GParticleSystem* sys)
{
	int       num = determine_particles_to_emit(sys);
	int       index;
	Particle* p = NULL;

	double now = r_time();
	//printf("Emitting %d particle (%d).\n", num, sys->cur);
	for (int i = 0; i < num; i++)
	{

		index = find_next_available_particle(sys);
		/*
		if (sys->reuse_particles)
		{
			index = sys->cur;
			
			//sys->cur++;
			//if (sys->cur == sys->max)
			//{
			//	sys->cur = 0;
			//}
		}
		else
		{
			// printf("found %d\n", index);
			if (index == -1)
			{
				// printf(":(");
				return NULL;
			}
		}
		*/
		if ( index == -1 )
			continue;
		
		
		p = sys->data[index];

		if (!p)
		{
			p = g_particle_create();
		}
		else
		{
			g_particle_reset(p);
		}
		
		p->size_over_life_type = sys->size_over_life_type;
		p->size = sys->size;
		sys->emitter->place(sys->emitter, p);
		sys->emitter->aim(sys->emitter, p);

		p->birth = now;
		p->death = now + sys->death;
		p->idx   = index;

		sys->data[index] = p;
		
		sys->cur = index;
		/*
		sys->cur++;
		if (sys->cur == sys->max)
		{
			sys->cur = 0;
		}*/
		
	}
	return p;
}

void g_particle_system_update(GParticleSystem* sys)
{
	g_particle_system_update_particles(sys);

	if (sys->emitting)
	{

		switch (sys->emitter->emission_periodicity_setting)
		{
		case G_PARTICLE_EMIT_RANDOMCHANCE:
		{
			if (r_rand_double(NULL) < sys->emitter->random_chance)
			{
				g_particle_system_emit(sys);
			}
			break;
		}
		case G_PARTICLE_EMIT_NUM_PER_FRAME:
		{
			g_particle_system_emit(sys);

			break;
		}
		case G_PARTICLE_EMIT_ON_TIMER:
		{
			double now   = r_time();
			double delta = now - sys->emitter->last_emit;
			if (delta > sys->emitter->particle_timer)
			{
				g_particle_system_emit(sys);
				sys->emitter->last_emit = now;
			}
			break;
		}

		default:
			break;
		}
	}
}

void g_particle_system_kill_particle(GParticleSystem* sys, Particle* p)
{
	int idx = p->idx;
	
	//printf("Killing particle %d\n", p->idx);
	g_particle_destroy(p);
	sys->data[idx] = NULL;
}

void g_particle_system_update_particle(GParticleSystem* sys, Particle* p)
{

	// p->rotation = vec3_add(p->position, p->spin, NULL);
	p->velocity = vec3_add(p->velocity, sys->gravity, NULL);
	p->velocity = vec3_add(p->velocity, sys->wind, NULL);
	p->position = vec3_add(p->position, p->velocity, NULL);
	//char* buf = calloc(128, sizeof(char));
	//vec3_str(p->velocity, buf);
	//printf("%s\n", buf);
	
	//vec3_t r = vec3_create(NULL);
	if ( p->prev[0] != p->position[0] || p->prev[1] != p->position[1] || p->prev[2] !=p->position[2])
	{
		p->direction = vec3_direction(p->position, p->prev, p->direction);

	}
	g_particle_update(p);
	//if ( p->position[0] != p->prev[0])
	//	printf("%f %f %f\n", p->direction[0], p->direction[1], p->direction[2]);
	
	vec3_set(p->position, p->prev);

}

static bool check_bounds_box(vec3_t b, vec3_t p)
{
	if (p[0] <= b[0] && p[0] >= -b[0] && p[1] <= b[1] && p[1] >= -b[1] && p[2] <= b[2] && p[2] >= -b[2])
	{
		return true;
	}
	return false;
}

static bool check_bounds(struct GParticleSystem* sys, vec3_t b, vec3_t p)
{
	//double px = p[0];
	//double py = p[1];
	//double pz = p[2];
	//	horrible.
	sys->bound_type = GPARTICLE_BOUND_BOX;
	
	switch (sys->bound_type) {
		case GPARTICLE_BOUND_BOX:
			return check_bounds_box(b, p);
			break;
			
		default:
			printf("Unknown bound type! %d\n", sys->bound_type);
			break;
	}

	return false;
}
void g_particle_system_update_particles(GParticleSystem* sys)
{
	if (!sys)
	{
		printf("Can't update a NULL particle system!\n");
		return;
	}
	double now = r_time();

	for (int i = 0; i < sys->max; i++)
	{
		Particle* p = sys->data[i];
		if (!p)
			continue;

		if (p->die)
		{
			g_particle_system_kill_particle(sys, p);
			continue;
		}
		// double d = now - p->birth;
		p->life = now - p->birth;
		if (sys->death != 0)
		{
			
			p->nlife = -1;
			p->nlife = p->life / sys->death;
			
			double delta = now - p->birth;
			if (delta > sys->death)
			{
				p->die = true;
			}
		}
		g_particle_system_update_particle(sys, p);
		vec3_t pos = p->position;
		if (!check_bounds(sys, sys->bounds, p->position))
		{
			//printf("Outta here!\n");
			g_particle_system_kill_particle(sys, p);
		}
		//	loop through effectors
	}
}

void g_particle_system_set_emitter(GParticleSystem* sys, void* emitter)
{
	sys->emitter = emitter;
	// sys->particle_emit_func = emitt
}

void g_particle_system_start(GParticleSystem* sys)
{
	sys->emitting = true;
}

void g_particle_system_stop(GParticleSystem* sys)
{
	sys->emitting = false;
}

void g_particle_system_set_gravity(GParticleSystem* sys, double x, double y,
				   double z)
{
	sys->gravity[0] = x;
	sys->gravity[1] = y;
	sys->gravity[2] = z;
}
void g_particle_system_set_wind(GParticleSystem* sys, double x, double y,
				double z)
{
	sys->wind[0] = x;
	sys->wind[1] = y;
	sys->wind[2] = z;
}

void g_particle_system_set_bounds_u(GParticleSystem* sys, double v)
{
	g_particle_system_set_bounds(sys, v, v, v);
}

void g_particle_system_set_bounds(GParticleSystem* sys, double x, double y,
				  double z)
{
	//	boundaries are always positive and we compare against negatived invert
	sys->bounds[0] = fabs(x);
	sys->bounds[1] = fabs(y);
	sys->bounds[2] = fabs(z);
}

static void draw_box(vec3_t pos, vec3_t bounds)
{
}

static void draw_circles(vec3_t pos, vec3_t bounds)
{
	drw_push();
	drw_translate_vec3(pos);

	drw_color(1, 0, 0, 1);

	drw_circle(bounds[0]);
	drw_rotate_x(90);
	drw_color(1, 0, 0, 1);
	drw_circle(bounds[1]);
	drw_rotate_x(-90);
	drw_circle(bounds[2]);

	drw_pop();
}

void g_particle_system_draw_debug(GParticleSystem* sys)
{
	if ( !sys->emitter)
	{
		printf("No emitter!\n");
	}else{
//		drw_color_push();
		drw_color_save();
		draw_circles(sys->emitter->position, sys->emitter->bounds);
//		drw_color_pop();
		drw_color_restore();
	}
	
	for (int i = 0; i < sys->max; i++)
	{
		Particle* p = sys->data[i];
		if (!p)
			continue;
		//drw_push();
		drw_color_save();
		drw_translate_vec3(p->position);

		drw_square(10);
		drw_pop();
		drw_color_restore();
	}

	/*
	 drw_push();
	drw_translate_vec3(sys->emitter->position);
	drw_color(1,0,0,1);


	drw_circle(sys->emitter->bounds[0]);

	drw_rotate_x(90);
	drw_color(0,1,0,1);
	drw_circle(sys->emitter->bounds[1]);

	drw_translate_vec3(sys->emitter->position);
	drw_rotate_y(90);
	drw_color(0,.5,1,1);
	drw_circle(sys->emitter->bounds[2]);
	 drw_pop();

	*/
}
