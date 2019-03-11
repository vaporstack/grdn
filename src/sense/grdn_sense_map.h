//
//  grdn_sense_map.h
//  grdn
//
//  Created by vs on 3/11/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef grdn_sense_map_h
#define grdn_sense_map_h

#include "../ent/g_entity.h"
enum {
	GRDN_SENSE_TYPE_VISION,
	GRDN_SENSE_TYPE_AUDIO,
	GRDN_SENSE_TYPE_SMELL,
	GRDN_SENSE_TYPE_SOUND,
	GRDN_SENSE_TYPE_TOUCH,
	GRDN_SENSE_TYPE_NONE
};

void grdn_sense_registry_add(GEntity* ent);
void grdn_sense_registry_remove(GEntity* ent);
void grdn_sense_post_event(GEntity* ent, unsigned type, double mag, unsigned inttype);


#endif /* grdn_sense_map_h */
