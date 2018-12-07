//
//  g_particle.h
//  r4
//
//  Created by Andrew Macfarlane on 1/7/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef g_particlesystem_h_
#define g_particlesystem_h_

//
//#include <r4/r4.h>
//#include "../../../wsh/wsh.h"

#include <deps/vector/vector.h>

#include "g_attractor.h"

#include "g_particle.h"
#include "g_particle_emitter.h"

typedef void (*custom_particle_function)(void* sys, Particle*);

enum ParticleFloorType
{
	PARTICLE_FLOOR_NONE,
	PARTICLE_FLOOR_BOUNCE,
	PARTICLE_FLOOR_KILL
};

enum ParticleKillType
{
	PARTICLE_BOUNDBEHAVIOR_NONE, // do not kill even if out of bounds
	PARTICLE_BOUNDBEHAVIOR_KILL, // kill it
	PARTICLE_BOUNDBEHAVIOR_RESET // respawn it
};

enum ParticleKillOldType
{
	PARTICLE_OLDKILL_NONE,
	PARTICLE_OLDKILL_KILL,
	PARTICLE_OLDKILL_RESET
};

enum ParticleEmitType
{
	PARTICLE_EMIT_POINT,
	PARTICLE_EMIT_DISC,
	PARTICLE_EMIT_DISC_VOL,
	PARTICLE_EMIT_SPHERE,
	PARTICLE_EMIT_SPHERE_VOL,
	PARTICLE_EMIT_BOX
};

enum ParticleBoundingType
{
	PARTICLE_BOUND_NONE,
	PARTICLE_BOUND_BOX,
	PARTICLE_BOUND_SPHERE
};

typedef struct ParticleSystem
{
	// uint num;
	unsigned int      max;
	unsigned int      cur;
	struct Particle** data;

	bool air_enabled;
	bool gravity_enabled;
	bool wind_enabled;
	bool wind_varying;

	int kill_behavior;
	int oldkill_behavior;

	bool reset_x;
	bool reset_y;
	bool reset_z;

	float  wind_variance_freq;
	vec3_t wind;
	vec3_t wind_variance;
	vec3_t wind_limits_low;
	vec3_t wind_limits_high;
	vec3_t gravity;
	vec3_t air;

	vec3_t bounds;
	double boundrw_sphere;

	vec3_t emit_pos;
	vec3_t emit_box;

	float emit_rad;

	int bound_type;

	GParticleEmitter* emitter;
	int		  emit_type;

	float emit_chance;
	float lifespan;

	float kill_time;

	bool   floor_enabled;
	double floor;
	int    floor_behavior;
	double floor_drag;
	double floor_bounciness;

	void (*render)(struct ParticleSystem*);

	struct vector_t* attractors;
	// int attractor_num;
	bool   emitting;
	bool   debug;
	bool   flocking;
	vec3_t flocking_dir;

	custom_particle_function spawn;
	custom_particle_function die;
	custom_particle_function update;

} ParticleSystem;

typedef struct ParticleEffect
{

	int			 foo;
	void*			 data;
	custom_particle_function apply;
} ParticleEffect;

ParticleSystem* g_particlesystem_create(int);
void		g_particlesystem_destroy(ParticleSystem* sys);
void		g_particlesystem_update(ParticleSystem* sys);
void		g_particlesystem_renderdebug(ParticleSystem*);
void		g_particlesystem_destroy_particle(ParticleSystem*, Particle* p);
void		g_particlesystem_particle_kill(ParticleSystem*, Particle* p);
void		g_particlesystem_particle_update(ParticleSystem*, Particle* p);
void		g_particlesystem_particle_reset(ParticleSystem*, Particle* p);
void		g_particlesystem_particle_spawn(ParticleSystem*, Particle* p);

/*

 */
void g_particlesystem_set_emit_type(ParticleSystem*, int type);
void g_particlesystem_set_emitpos(ParticleSystem*, double x, double y,
				  double z);
void g_particlesystem_set_emitbox(ParticleSystem*, double x, double y,
				  double z);
void g_particlesystem_set_bounds(ParticleSystem*, double x, double y, double z);
void g_particlesystem_set_bounds_type(ParticleSystem* sys, int type);
void g_particlesystem_set_air(ParticleSystem* sys, double x, double y,
			      double z);
void g_particlesystem_set_windlimits(ParticleSystem*, double x, double y,
				     double z);
void g_particlesystem_set_windvariance(ParticleSystem*, double x, double y,
				       double z);
void g_particlesystem_set_wind(ParticleSystem*, double x, double y, double z);
void g_particlesystem_set_gravity(ParticleSystem*, double x, double y,
				  double z);

void g_particlesystem_set_gravity_enabled(ParticleSystem* sys, bool val);

void g_particlesystem_draw(ParticleSystem*);

/*


void 				particle_reset(ParticleSystem*, struct
Particle* );
void 				particles_init(ParticleSystem* );

struct Particle*		p_create_particle(ParticleSystem* sys);
void					p_update_particles(ParticleSystem* );
void					p_update_particle(struct
ParticleSystem*, struct Particle* );
void					particles_destroy(ParticleSystem* );
struct Particle*		p_spawn_new_particle(ParticleSystem* sys );
void					p_particle_destroy(struct
ParticleSystem*, struct Particle* p);


//void p_system_attractor_add(ParticleSystem*, struct ParticleAttractor* );
//void p_system_attractor_remove(ParticleSystem*, struct ParticleAttractor* );

*/

#endif /* g_particlesystem_h_ */
