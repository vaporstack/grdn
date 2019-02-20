
//  g_particle_presets.c
//  g_particle_presets
//
//  Created by Andrew Macfarlane on 30/09/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_particle_presets.h"

void g_particlesystem_preset_dust(ParticleSystem* sys)
{
	printf("Applying [DUST] preset.\n");
	// sys->gravity_enabled = true;
	g_particlesystem_set_gravity(sys, 0, 1, 0);

	sys->air_enabled	= false;
	sys->wind_enabled       = true;
	sys->wind_varying       = true;
	sys->wind_variance_freq = .1;
	g_particlesystem_set_wind(sys, 0, 0, 0);
	g_particlesystem_set_windvariance(sys, .01, .01, .01);
	g_particlesystem_set_windlimits(sys, .05, .025, .1);
	g_particlesystem_set_bounds(sys, 512, 512, 512);
	sys->bound_type     = PARTICLE_BOUND_SPHERE;
	sys->emit_type      = PARTICLE_EMIT_SPHERE_VOL;
	sys->bound_sphere = 512;
	sys->emit_rad       = 512;
	sys->emitting       = true;
	g_particlesystem_set_air(sys, 1, 1, 1);
}

void g_particlesystem_preset_rain(ParticleSystem* sys)
{
	printf("Applying [DUST] preset.\n");
	// sys->gravity_enabled = true;
	g_particlesystem_set_gravity(sys, 0, 6, 0);
	sys->gravity_enabled    = true;
	sys->air_enabled	= false;
	sys->wind_enabled       = true;
	sys->wind_varying       = true;
	sys->wind_variance_freq = .1;
	g_particlesystem_set_wind(sys, 0, 0, 0);
	g_particlesystem_set_windvariance(sys, .01, .01, .01);
	g_particlesystem_set_windlimits(sys, .05, .025, .1);
	g_particlesystem_set_bounds(sys, 512, 512, 512);
	sys->bound_type     = PARTICLE_BOUND_SPHERE;
	sys->emit_type      = PARTICLE_EMIT_SPHERE_VOL;
	sys->bound_sphere = 512;
	sys->emit_rad       = 512;
	sys->emitting       = true;
	g_particlesystem_set_air(sys, 1, 1, 1);
}

void g_particlesystem_preset_ambient(ParticleSystem* sys)
{
}

void g_particlesystem_preset_snow(ParticleSystem* sys)
{
}

void g_particlesystem_preset_lake(ParticleSystem* sys)
{
}

void g_particlesystem_preset_fire(ParticleSystem* sys)
{
}

void g_particlesystem_preset_trail(ParticleSystem* sys)
{
}
