//
//  grdn_ai_thinker.h
//  grdn
//
//  Created by vs on 12/22/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef grdn_ai_thinker_h
#define grdn_ai_thinker_h


#include "../ent/g_entity.h"

typedef void(*g_think_func)(GEntity*);

typedef struct GThinker
{
	unsigned foo;
	g_think_func select_target;
	
}GThinker;



#endif /* grdn_ai_thinker_h */
