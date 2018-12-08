//
//  grdn_log.c
//  grdn
//
//  Created by vs on 12/7/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "grdn_log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define GRDN_LOG_MAX 256

void grdn_log(char* format, ...)
{
	
	char buf[GRDN_LOG_MAX];
	sprintf(buf, "%s", format);
	va_list args;
	va_start(args, format);
	vsprintf(buf, format, args);
	va_end(args);
	
#ifdef DEBUG
	printf("[grdn]: %s\n", buf);
#else
	printf("DO NOTHING LATER: %s\n", buf);
#endif
}
