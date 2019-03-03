//
//  g_particle.c
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

//#ifdef DISABLE_WHILE_REWRITING_WHOLE_PARTICLE_SYSTEM
#include "g_particlesystem.h"

#include <drw/drw.h>
#include <string.h>

// extern AppSettings app_settings;
// extern DebugSettings debug_settings;

#define DRAG .92
#define W_VARIANCE .000005

#define BOUNDS 1024

//	todo: get rid of this!
#include <r4/r4.h>

//	private
void g_particlesystem_bounds_check(ParticleSystem* sys, Particle* p);

ParticleSystem* g_particlesystem_create(int max)
{
	ParticleSystem* sys = malloc(sizeof(ParticleSystem));
	sys->max	    = max;

	sys->kill_behavior = PARTICLE_BOUNDBEHAVIOR_KILL;

	sys->bound_type  = PARTICLE_BOUND_BOX;
	sys->emit_type   = PARTICLE_EMIT_POINT;
	sys->emit_pos    = vec3_create(NULL);
	sys->emit_pos[0] = 0;
	sys->emit_pos[1] = 0;
	sys->emit_pos[2] = 0;
	sys->cur	 = 0;
	sys->max	 = max;
	sys->wind	= vec3_create(NULL);
	sys->air_enabled = false;
	sys->air	 = vec3_create(NULL);
	sys->air[0] = sys->air[1] = sys->air[2] = .9;
	sys->wind_variance			= vec3_create(NULL);
	sys->wind_limits_low			= vec3_create(NULL);
	sys->wind_limits_high			= vec3_create(NULL);
	sys->wind				= vec3_create(NULL);
	sys->gravity				= vec3_create(NULL);
	sys->bounds				= vec3_create(NULL);
	sys->bounds[0] = sys->bounds[1] = sys->bounds[2] = BOUNDS;
	sys->bound_sphere				 = BOUNDS;
	sys->emit_pos					 = vec3_create(NULL);
	sys->emit_box					 = vec3_create(NULL);
	sys->emitter					 = NULL;

	sys->flocking     = false;
	sys->flocking_dir = vec3_create(NULL);

	sys->floor_enabled    = false;
	sys->floor_bounciness = 1;
	sys->floor_drag       = .9;
	sys->floor	    = 0.0;

	sys->kill_time	= 64;
	sys->oldkill_behavior = PARTICLE_OLDKILL_RESET;

	sys->reset_x = true;
	sys->reset_y = true;
	sys->reset_z = true;

	sys->die    = NULL;
	sys->update = NULL;

	// sys->num = 0;
	// sys->data = malloc(sizeof(Particle* )* max);
	sys->data = calloc(max, sizeof(Particle*));
	// memset(sys->data, 0, sizeof(Particle*) * max);
	// if(debug_settings.particles )
	//
	for (int i = 0; i < sys->max; ++i)
	{
		sys->data[i]      = g_particle_create();
		sys->data[i]->idx = i;
	}
	printf("Created a system with %d particles.\n", max);

	// sys->attractor_num =0;
	sys->attractors = NULL;
	sys->emitting   = true;

	return sys;
}

void g_particlesystem_destroy(ParticleSystem* sys)
{
	if (!sys)
		return;
	
	if (sys->emitter)
	{
		g_particle_emitter_destroy(sys->emitter);
	}
	free(sys->data);
	free(sys);
	sys = NULL;
}

//#include <vbl/vbl.h>
#include <vbl/src/core/vbl_rng.h>

void g_particlesystem_update(ParticleSystem* sys)
{
	if (!sys)
	{
		printf("Tried to update a null particle system!\n");
		return;
	}

	if (sys->wind_enabled)
	{
		// thus potentially has a bug
		if (sys->wind_varying)
		{
			if (r_rand_float(vbl_rng_get()) < sys->wind_variance_freq)
			{
				// printf("v\n");
				sys->wind[0] += (r_rand_float(vbl_rng_get()) - .5) *
						sys->wind_variance[0];
				sys->wind[1] += (r_rand_float(vbl_rng_get()) - .5) *
						sys->wind_variance[1];
				sys->wind[2] += (r_rand_float(vbl_rng_get()) - .5) *
						sys->wind_variance[2];
				// printf("new wind is %f %f %f\n",
				// sys->wind[0], sys->wind[1], sys->wind[2]);
			}

			if (sys->wind_variance[0] < sys->wind_limits_low[0])
				sys->wind_variance[0] = sys->wind_limits_low[0];
			if (sys->wind_variance[0] > sys->wind_limits_high[0])
				sys->wind_variance[0] = sys->wind_limits_high[0];
			if (sys->wind_variance[1] < sys->wind_limits_low[1])
				sys->wind_variance[1] = sys->wind_limits_low[1];
			if (sys->wind_variance[1] > sys->wind_limits_high[1])
				sys->wind_variance[1] = sys->wind_limits_high[1];
			if (sys->wind_variance[2] < sys->wind_limits_low[2])
				sys->wind_variance[2] = sys->wind_limits_low[2];
			if (sys->wind_variance[2] > sys->wind_limits_high[2])
				sys->wind_variance[2] = sys->wind_limits_high[2];
		}
	}

	if (sys->flocking)
	{
		sys->flocking_dir[0] = sys->flocking_dir[1] =
		    sys->flocking_dir[2];
	}

	int num = sys->max;
	// all presumed dead
	static bool prev_any_alive = true;
	static bool any_alive      = false;

	double now = r_time();

	any_alive = false;
	for (int i = 0; i < num; i++)
	{
		Particle* p = sys->data[i];
		g_particle_update(p);
		if (!p->alive)
		{
			continue;
		}
		else
		{
			any_alive = true;
		}
		if (p == NULL)
		{
			continue;
		}

		// p->life = now - p->birth;
		if (p->life > p->death)
		{
			if (sys->die)
			{
				sys->die(sys, p);
			}
			else
			{
				g_particlesystem_particle_kill(sys, p);
			}
		}

		//	apply forces
		g_particlesystem_particle_update(sys, p);

		///	check bounds
		int x = sys->bounds[0];
		int y = sys->bounds[1];
		int z = sys->bounds[2];

		if (sys->bound_type == PARTICLE_BOUND_NONE)
		{
			//	nada.
			// printf("n");
		}
		else if (sys->bound_type == PARTICLE_BOUND_BOX)
		{

			if (p->position[0] < -x || p->position[0] > x ||
			    p->position[1] < -y || p->position[1] > y ||
			    p->position[2] < -z || p->position[2] > z)
			{
				g_particlesystem_bounds_check(sys, p);
			}
			// printf("bax");
		}
		else if (sys->bound_type == PARTICLE_BOUND_SPHERE)
		{
			double dist = vec3_dist(p->position, sys->emit_pos);
			if (dist > sys->bound_sphere)
			{
				g_particlesystem_bounds_check(sys, p);
			}
			// printf("sp");
		}
		else
		{
			printf("Unhandled bounds checking method!\n");
		}

		//	high level
		if (sys->flocking)
		{
			sys->flocking_dir[0] += p->direction[0];
			sys->flocking_dir[1] += p->direction[1];
			sys->flocking_dir[2] += p->direction[2];
			sys->flocking_dir[1] +=
			    (-.5 + r_rand_double(NULL)) * .1;
		}
	}

	if (sys->flocking)
	{
		sys->flocking_dir[0] /= num;
		sys->flocking_dir[1] /= num;
		sys->flocking_dir[2] /= num;
		// printf("Flock dir is %f %f %f\n", sys->flocking_dir[0],
		// sys->flocking_dir[1], sys->flocking_dir[2]);
	}
	if (prev_any_alive != any_alive)
	{
		printf("Aliveness changed! %d \n", any_alive);
		prev_any_alive = any_alive;
	}
}

void g_particlesystem_particle_kill(ParticleSystem* sys, Particle* p)
{
	if (sys->oldkill_behavior == PARTICLE_OLDKILL_NONE)
	{
		return;
	}
	else if (sys->oldkill_behavior == PARTICLE_OLDKILL_KILL)
	{
		p->alive = false;
	}
	else if (sys->oldkill_behavior == PARTICLE_OLDKILL_RESET)
	{
		g_particlesystem_particle_reset(sys, p);
	}
	else
	{
		printf("Unknown kill behavior!");
	}
}

void g_particlesystem_bounds_check(ParticleSystem* sys, Particle* p)
{
	if (sys->kill_behavior == PARTICLE_BOUNDBEHAVIOR_NONE)
	{
		printf("n");
		return;
	}
	else if (sys->kill_behavior == PARTICLE_BOUNDBEHAVIOR_KILL)
	{
		g_particlesystem_particle_kill(sys, p);
	}
	else if (sys->kill_behavior == PARTICLE_BOUNDBEHAVIOR_RESET)
	{
		g_particlesystem_particle_reset(sys, p);
	}
	else
	{
		printf("Unknown type!");
	}
}

void g_particlesystem_particle_reset(ParticleSystem* sys, Particle* p)
{
	//g_particle_reset(p);
	//vec3_set(p->position, p->origin);
	//p->position = p->origin;
	/*
	p->alive = true;
	// printf("%f %f %f\n", sys->emit_pos[0], sys->emit_pos[1],
	// sys->emit_pos[2]);
	p->velocity[0] = p->velocity[1] = p->velocity[2] = 0;

	double x, y, z;
	x = y = z = 0;

	p->life  = 0;
	p->birth = r_time();
	if (sys->emitter)
	{
		free(p);
		p = sys->emitter->emit(sys->emitter);
		return;
	}

	if (sys->emit_type == PARTICLE_EMIT_POINT) {
		x = sys->emit_pos[0];
		y = sys->emit_pos[1];
		z = sys->emit_pos[2];
	} else if (sys->emit_type == PARTICLE_EMIT_SPHERE) {
		//	from:
		//
	https://stackoverflow.com/questions/5531827/random-point-on-a-given-sphere/15048260#15048260
		bool proceed = false;
		while (!proceed) {

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

		x *= sys->emit_rad;
		y *= sys->emit_rad;
		z *= sys->emit_rad;
	} else if (sys->emit_type == PARTICLE_EMIT_SPHERE_VOL) {

		//	reference:
		//
	http://studio.sketchpad.cc/sp/pad/view/ro.9h2maqXXvC2MA/latest

		double theta = r_rand_double(NULL) * M_PI * 2;
		double v     = (-.5 + r_rand_double(NULL)) * 2;
		double phi   = acos(v);
		double r     = r_rand_double(NULL) * sys->emit_rad;
		// double n = pow(r_rand_double(NULL), 0.3333);
		x = r * cos(theta) * sin(phi);
		y = r * sin(theta) * sin(phi);
		z = r * cos(phi);


	} else if (sys->emit_type == PARTICLE_EMIT_BOX) {

		x = (r_rand_double(NULL) * sys->emit_box[0]);
		y = (r_rand_double(NULL) * sys->emit_box[1]);
		z = (r_rand_double(NULL) * sys->emit_box[2]);
		if (r_rand_double(NULL) < .5)
			x = x * -1;
		if (r_rand_double(NULL) < .5)
			y = y * -1;
		if (r_rand_double(NULL) < .5)
			z = z * -1;

		x += sys->emit_pos[0];
		y += sys->emit_pos[1];
		z += sys->emit_pos[2];
	} else {
		printf("Unknown spawn type!");
	}

	if (sys->reset_x)
		p->position[0] = x;

	if (sys->reset_y)
		p->position[1] = y;

	if (sys->reset_z)
		p->position[2] = z;

		*/
	
	
	
}

void g_particlesystem_particle_spawn(ParticleSystem* sys, Particle* p)
{
	/*
	if ( sys->emitter )
	{
		sys->emitter->emit(sys, p);
	}
	 */

	/*
	if (sys->spawn) {
		sys->spawn(sys, p);
	}
	 */
}

void g_particlesystem_destroy_particle(ParticleSystem* sys, Particle* p)
{
}

void g_particlesystem_renderdebug(ParticleSystem* sys)
{
	drw_color(1, 0, 0, 1);
	drw_push();

	drw_translate_vec3(sys->emit_pos);
	drw_line(-.5 * sys->emit_box[0], 0, .5 * sys->emit_box[0], 0);
	drw_color(0, 1, 0, 1);
	drw_line(0, -.5 * sys->emit_box[1], 0, .5 * sys->emit_box[1]);
	drw_color(0, 0, 1, 1);
	drw_line_3f(0, 0, .5 * sys->emit_box[2], 0, 0, -.5 * sys->emit_box[2]);
	drw_axis_living();
	drw_pop();
}

void g_particlesystem_particle_update(ParticleSystem* sys, Particle* p)
{

	p->life++;

	if (sys->air_enabled)
	{
		p->velocity = vec3_multiply(p->velocity, sys->air, p->velocity);
	}

	if (sys->gravity_enabled == 0)
	{
		// vec3_t vel = p->velocity;
		// vec3_t grav = sys->gravity;
		// printf("Gravity %f %f %f\n", sys->gravity[0],
		// sys->gravity[1], sys->gravity[2]);
		//printf("grav?");
		p->velocity = vec3_add(p->velocity, sys->gravity, p->velocity);
	}
	else
	{
		//printf("nograv?");
	}

	if (sys->floor_enabled)
	{
		if (p->position[1] < sys->floor)
		{
			if (sys->floor_behavior == PARTICLE_FLOOR_KILL)
			{
				g_particlesystem_bounds_check(sys, p);
				// printf("k");
			}
			else if (sys->floor_behavior == PARTICLE_FLOOR_NONE)
			{
				// pass
				// printf("n");
			}
			else if (sys->floor_behavior ==
				 PARTICLE_FLOOR_BOUNCE)
			{
				p->position[1] = sys->floor;
				p->velocity[1] *= sys->floor_bounciness;
				p->velocity[0] *= sys->floor_drag;
				p->velocity[2] *= sys->floor_drag;
				p->velocity[1] *= -1;
				// printf("f");
			}
			else
			{
				printf("undefined floor\n");
			}

			// printf("floor!");
		}
	}

	if (sys->wind_enabled)
	{
		/*
		double m = p->mass;
		double x = 1 - m;
		vec3_t foo = vec3_create(sys->wind);
		foo[0] *= x;
		foo[1] *= x;
		foo[2] *= x;


		p->velocity = vec3_add(p->velocity, foo, p->velocity);
		*/
		p->velocity[0] += sys->wind[0];
		p->velocity[1] += sys->wind[1];
		p->velocity[2] += sys->wind[2];
	}
	p->position[0] += p->velocity[0];
	p->position[1] += p->velocity[1];
	p->position[2] += p->velocity[2];
}

void g_particlesystem_attractor_add(ParticleSystem*    sys,
				    ParticleAttractor* attr)
{

	/*
	sys->attractor_num++;
	sys->attractors = realloc(
	    sys->attractors, sizeof(ParticleAttractor) * sys->attractor_num);

	printf("%d attractors.\n", sys->attractor_num);
*/
}

void g_particlesystem_attractor_remove(ParticleSystem*    sys,
				       ParticleAttractor* attr)
{
}

void g_particlesystem_set_emit_type(ParticleSystem* sys, int type)
{
	sys->emit_type = type;
}

void g_particlesystem_set_emitpos(ParticleSystem* sys, double x, double y,
				  double z)
{
	sys->emit_pos[0] = x;
	sys->emit_pos[1] = y;
	sys->emit_pos[2] = z;
}

void g_particlesystem_set_emitbox(ParticleSystem* sys, double x, double y,
				  double z)
{
	sys->emit_box[0] = x;
	sys->emit_box[1] = y;
	sys->emit_box[2] = z;
}

void g_particlesystem_set_bounds_type(ParticleSystem* sys, int type)
{

	sys->bound_type = type;
}

void g_particlesystem_set_bounds(ParticleSystem* sys, double x, double y,
				 double z)
{
	sys->bounds[0] = x;
	sys->bounds[1] = y;
	sys->bounds[2] = z;
}

void g_particlesystem_set_wind(ParticleSystem* sys, double x, double y,
			       double z)
{
	sys->wind[0] = x;
	sys->wind[1] = y;
	sys->wind[2] = z;
}

void g_particlesystem_set_windlimits(ParticleSystem* sys, double x, double y,
				     double z)
{
	sys->wind_limits_low[0]  = -x;
	sys->wind_limits_low[1]  = -y;
	sys->wind_limits_low[2]  = -z;
	sys->wind_limits_high[0] = x;
	sys->wind_limits_high[1] = y;
	sys->wind_limits_high[2] = z;
	printf("set wind limits to %f %f %f %f %f %f\n", -x, -y, -z, x, y, z);
}

void g_particlesystem_set_windvariance(ParticleSystem* sys, double x, double y,
				       double z)
{
	sys->wind_variance[0] = -x;
	sys->wind_variance[1] = -y;
	sys->wind_variance[2] = -z;
}

void g_particlesystem_set_air(ParticleSystem* sys, double x, double y, double z)
{
	sys->air[0] = x;
	sys->air[1] = y;
	sys->air[2] = z;
}

void g_particlesystem_set_gravity(ParticleSystem* sys, double x, double y,
				  double z)
{
	sys->gravity[0] = -x;
	sys->gravity[1] = -y;
	sys->gravity[2] = -z;
}

void g_particlesystem_set_gravity_enabled(ParticleSystem* sys, bool val)
{
	sys->gravity_enabled = val;
}

void g_particlesystem_draw(ParticleSystem* sys)
{
	int num = sys->max;
	for (int i = 0; i < num; i++)
	{
		Particle* p = sys->data[i];
		drw_push();
		drw_translate_vec3(p->position);
		// printf("ps - %f\n", p->size);
		drw_scale_u(p->size);
		drw_square(1);
		drw_pop();
	}
}
//#endif
