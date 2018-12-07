
//  g_serial.c
//  g_serial
//
//  Created by Andrew Macfarlane on 30/07/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_serial.h"

#include <cjson/cJSON.h>

#include <r4/src/r4_config.h>

#ifdef RPLATFORM_WIN
#define sprintf sprintf_s
#endif

ParticleSystem* g_particlesystem_load_json(const char*     path,
					   ParticleSystem* sys)
{
	char* data = w_read_file_as_text_nc(path);

	if (!data) {
		char buf[256];
		sprintf(buf, "An error occurred reading text file: %s\n", path);
		// l_warning(buf);
		free(data);
		return sys;
	}

	cJSON* root = cJSON_Parse(data);

	return sys;
}

int g_particlesystem_save_json(const char* path, ParticleSystem* sys)
{
	//	oops, do nothing.
	// cJSON* root = cJSON_create();

	// w_write_file_as_text_nc(path, root);
	return 0;
}
