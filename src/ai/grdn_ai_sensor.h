//
//  grdn_ai_sensor.h
//  grdn
//
//  Created by vs on 12/22/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef grdn_ai_sensor_h
#define grdn_ai_sensor_h

#include "../env/g_area.h"

typedef struct GEntityList
{
	GEntity** data;
	unsigned int num;
}GEntityList;

typedef GEntityList(*g_sense_func)(GEntity*);


typedef struct GSensor
{
	GEntityHnd* owner;
	GArea* area;
	g_sense_func sense;
}GSensor;

typedef struct GSensorArray
{
	unsigned int num;
	GSensor* data;
}GSensorArray;

GSensor* grdn_ai_sensor_create(GEntityHnd owner);

#endif /* grdn_ai_sensor_h */
