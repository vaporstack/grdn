
//  g_particle_presets.c
//  g_particle_presets
//
//  Created by Andrew Macfarlane on 30/09/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_particle_presets_h_
#define g_particle_presets_h_

#include "g_particlesystem.h"

void g_particlesystem_preset_rain(ParticleSystem* sys);
void g_particlesystem_preset_ambient(ParticleSystem* sys);
void g_particlesystem_preset_snow(ParticleSystem* sys);
void g_particlesystem_preset_lake(ParticleSystem* sys);
void g_particlesystem_preset_fire(ParticleSystem* sys);
void g_particlesystem_preset_trail(ParticleSystem* sys);
void g_particlesystem_preset_dust(ParticleSystem* sys);
void g_particlesystem_preset_explosion(ParticleSystem* sys);

#endif
