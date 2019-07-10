//
//  grdn_ai.c
//  grdn
//
//  Created by vs on 12/22/18.
//  Copyright Â© 2018 ruminant. All rights reserved.
//

#include "grdn_ai.h"




GAi* grdn_ai_create(GEntity* ent)
{
	
	GAi* ai = calloc(1, sizeof(GAi));
	
	return ai;
	
}

void grdn_ai_destroy(GAi* ai)
{
	if ( ai->current_program )
	{
		free(ai->current_program);
		ai->current_program = NULL;
	}
	if ( ai->available_programs )
	{
		free(ai->available_programs);
		ai->available_programs = NULL;
	}
	
}

static void update_current_program(GAi* ai )
{
	
}

void grdn_ai_update(GAi* ai)
{
	
	//	todo add checks for timing here?
	//	or maybe that belongs above
	
	
	update_current_program(ai);
	
}
