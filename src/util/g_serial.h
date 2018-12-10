
//  g_serial.c
//  g_serial
//
//  Created by Andrew Macfarlane on 30/07/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_serial_h_
#define g_serial_h_

#include <grdn/grdn.h>

void*       grdn_read_file_as_bin(const char* path, long* len);
const char* grdn_read_file_as_text(const char*);
char*       grdn_read_file_as_text_nc(const char*);
int	 grdn_write_text_to_file(const char*, const char*);


ParticleSystem* g_particlesystem_load_json(const char*     path,
					   ParticleSystem* sys);

#endif
