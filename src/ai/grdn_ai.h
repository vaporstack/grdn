//
//  grdn_ai.h
//  grdn
//
//  Created by vs on 12/22/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef grdn_ai_h
#define grdn_ai_h

#include "grdn_ai_actor.h"
#include "grdn_ai_sensor.h"
#include "grdn_ai_thinker.h"

typedef struct GAi
{
	GActor* actor;
	GSensorArray* sensors;
	GThinker* thinker;
}GAi;

GAi* grdn_ai_create(GEntity* ent);
void grdn_ai_destroy(GAi* ai);

#endif /* grdn_ai_h */
