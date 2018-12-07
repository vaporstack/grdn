
//  g_serial.c
//  g_serial
//
//  Created by Andrew Macfarlane on 30/07/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_serial_h_
#define g_serial_h_

#include <grdn/grdn.h>

ParticleSystem* g_particlesystem_load_json(const char*     path,
					   ParticleSystem* sys);

#endif
