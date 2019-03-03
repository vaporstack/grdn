//
//  g_particle_system.h
//  grdn
//
//  Created by vs on 11/21/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef g_particle_system_h
#define g_particle_system_h

#include <deps/gl-matrix/gl-matrix.h>
#include <deps/vector/vector.h>

#include "g_particle.h"

#include "g_particle_affector.h"
#include "g_particle_emitter.h"


enum GParticleFloorType
{
	GPARTICLE_FLOOR_NONE,
	GPARTICLE_FLOOR_BOUNCE,
	GPARTICLE_FLOOR_KILL
};

enum GParticleKillType
{
	GPARTICLE_BOUNDBEHAVIOR_NONE, // do not kill even if out of bounds
	GPARTICLE_BOUNDBEHAVIOR_KILL, // kill it
	GPARTICLE_BOUNDBEHAVIOR_RESET // respawn it
};

enum GParticleKillOldType
{
	GPARTICLE_OLDKILL_NONE,
	GPARTICLE_OLDKILL_KILL,
	GPARTICLE_OLDKILL_RESET
};

enum GParticleEmitType
{
	GPARTICLE_EMIT_POINT,
	GPARTICLE_EMIT_DISC,
	GPARTICLE_EMIT_DISC_VOL,
	GPARTICLE_EMIT_SPHERE,
	GPARTICLE_EMIT_SPHERE_VOL,
	GPARTICLE_EMIT_BOX
};

enum GParticleBoundingType
{
	GPARTICLE_BOUND_NONE,
	GPARTICLE_BOUND_BOX,
	GPARTICLE_BOUND_SPHERE
};


typedef struct GParticleSystem
{

	GParticleEmitter* emitter;

	struct vector_t effectors;

	vec3_t		  position;
	vec3_t		  bounds;
	vec3_t		  gravity;
	vec3_t		  wind;
	int		  cur;
	struct Particle** data;
	int		  num;
	int		  max;
	float		  death;
	float 		  size;
	
	int size_over_life_type;
	// particle_emit_func emit;

	int reuse_particles;
	int bound_type;
	int emitting;

} GParticleSystem;

GParticleSystem* g_particle_system_create(int);
void		 g_particle_system_destroy(GParticleSystem* sys);
void		 g_particle_system_update(GParticleSystem* sys);

void g_particle_system_stop(GParticleSystem* sys);
void g_particle_system_start(GParticleSystem* sys);
void g_particle_system_update_particles(GParticleSystem* sys);
void g_particle_system_update_particle(GParticleSystem* sys, Particle* p);
void g_particle_system_kill_particle(GParticleSystem* sys, Particle* p);
void g_particle_system_set_emitter(GParticleSystem* sys, void* emitter);

Particle* g_particle_system_emit(GParticleSystem* sys);

//	todo: gravity and wind should proooobably be affectors at some point?

void g_particle_system_set_gravity(GParticleSystem* sys, double x, double y,
				   double z);
void g_particle_system_set_wind(GParticleSystem* sys, double x, double y,
				double z);
void g_particle_system_set_bounds_u(GParticleSystem* sys, double v);

void g_particle_system_set_bounds(GParticleSystem* sys, double x, double y,
				  double z);
void g_particle_system_draw_debug(GParticleSystem* sys);

/*
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
	double bound_sphere;

	vec3_t emit_pos;
	vec3_t emit_box;

	float emit_rad;

	int bound_type;

	GParticleEmitter* emitter;
	int		 emit_type;

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
	*/
/*
void		g_particle_system_renderdebug(ParticleSystem*);
void		g_particlesystem_destroy_particle(ParticleSystem*, Particle* p);
void		g_particlesystem_particle_kill(ParticleSystem*, Particle* p);
void		g_particlesystem_particle_update(ParticleSystem*, Particle* p);
void		g_particlesystem_particle_reset(ParticleSystem*, Particle* p);
void		g_particlesystem_particle_spawn(ParticleSystem*, Particle* p);
*/

#endif /* g_particle_system_h */
