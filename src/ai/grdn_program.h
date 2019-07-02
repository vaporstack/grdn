//
//  grdn_program.h
//  grdn
//
//  Created by vs on 7/1/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef grdn_program_h
#define grdn_program_h

#include "../ent/g_entity.h"

typedef int (*grdn_directive_simple_fn)(GEntity* , void*);


typedef struct
{
	int num;
	int pos;
	grdn_directive_simple_fn ** directives;
} GProgram;

GProgram* grdn_program_create(void);


#endif /* grdn_program_h */
