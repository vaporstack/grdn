
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
	char* data = grdn_read_file_as_text_nc(path);

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


void* grdn_read_file_as_bin(const char* path, long* len)
{
	FILE* fileptr;
	// char *buffer;
	// long filelen;
	long l;
	
	fileptr = fopen(path, "rb"); // Open the file in binary mode
	if (!fileptr)
	{
		return NULL;
	}
	fseek(fileptr, 0, SEEK_END); // Jump to the end of the file
	l = ftell(fileptr); // Get the current byte offset in the file
	rewind(fileptr); // Jump back to the beginning of the file
	
	printf("%lu\n", *len);
	long  sz  = (l + 1) * sizeof(char);
	void* buf = malloc(sz); // Enough memory for file + \0
	memset(buf, 0, sz);
	fread(buf, l, 1, fileptr); // Read in the entire file
	fclose(fileptr); // Close the file
	*len = l;
	return 0;
}

const char* grdn_read_file_as_text(const char* path)
{
	FILE* f;
	
	f = fopen(path, "r");
	if (!f)
	{
		char buf[256];
		sprintf(buf, "Failed to open file: %s\n", path);
		printf("%s\n", buf);
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); // same as rewind(f);
	
	char* data = malloc(fsize + 1);
	fread(data, fsize, 1, f);
	fclose(f);
	
	data[fsize] = 0;
	
	return data;
}

char* grdn_read_file_as_text_nc(const char* path)
{
	FILE* f;
	
	f = fopen(path, "r");
	if (!f)
	{
		char buf[256];
		sprintf(buf, "Failed to open file: %s\n", path);
		printf("%s\n", buf);
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); // same as rewind(f);
	
	char* data = malloc(fsize + 1);
	fread(data, fsize, 1, f);
	fclose(f);
	
	data[fsize] = 0;
	
	return data;
}

int grdn_write_text_to_file(const char* path, const char* data)
{
	FILE* f;
	f = fopen(path, "w");
	if (!data)
	{
		printf("Data was null!\n");
		return 1;
	}
	if (!f)
	{
		char buf[256];
		sprintf(buf, "Failed to open file: %s\n", path);
		printf("%s\n", buf);
		// printf("Failed to open file: %s\n", path);
		return 1;
	}
	
	fprintf(f, "%s", data);
	fclose(f);
	
	return 0;
}

