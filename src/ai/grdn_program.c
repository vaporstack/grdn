//
//  grdn_program.c
//  grdn
//
//  Created by vs on 7/1/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "grdn_program.h"

GProgram* grdn_program_create(void)
{
	GProgram* prog = calloc(1, sizeof(GProgram));

	prog->pos = -1;
	return prog;
}

void grdn_program_add(GProgram* prog, grdn_directive_simple_fn directive)
{
	if ( directive == 0 )
	{
		printf("wtf can't add a null function ptr\n");
		return;
		
	}
	prog->num++;
	prog->directives = realloc(prog->directives, prog->num * sizeof(grdn_directive_simple_fn));

	prog->directives[prog->num - 1] = directive;
}
