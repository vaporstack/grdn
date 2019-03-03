
//  grdn.c
//  grdn
//
//  Created by Andrew Macfarlane on 11/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "grdn.h"
#include <stdarg.h>

int grdn_init(void)
{
	return 1;
}

void grdn_deinit(void)
{
}

int grdn_check_version_match(const char* str)
{
	char* version =grdn_get_version_string();
	int matches = (0 == strcmp(version, str));
	free(version);
	return matches;
}

char* grdn_get_version_string(void)
{
	char* buf = calloc(256, sizeof(char));
	sprintf(buf, "%d.%d.%d", GRDN_VERSION_MAJOR, GRDN_VERSION_MINOR, GRDN_VERSION_PATCH);
	return buf;
}

int grdn_check_compat_match(const char* header_generated_version)
{
	return (0 == strcmp(grdn_get_compat_string(), header_generated_version));
}

char* grdn_get_compat_string(void)
{
	char* buf = calloc(64, sizeof(char));
	sprintf(buf, "%d.%d", GRDN_VERSION_MAJOR, GRDN_VERSION_MINOR);
	return buf;
}
