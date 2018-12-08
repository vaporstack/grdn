//
//  g_entity.c
//  r4
//
//  Created by Andrew Macfarlane on 1/27/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "g_entity.h"

#include <deps/gl-matrix/gl-matrix.h>

#include "g_think.h"

#include <stdlib.h>

GEntity* g_entity_create(const char* name)
{
	struct GEntity* ent = calloc(1, sizeof(GEntity));
	ent->think	  = NULL;

	//ent->think_interval = 2;
	/*
	 ent->art = NULL;
	 ent->seq = NULL;
	 ent->draw = NULL;
	 ent->update = NULL;
	 ent->weapons = NULL;
	 ent->inventory = NULL;
	 //ent->pos = vec3_create(NULL);
	 */
	ent->dir  = 1;
	ent->data = NULL;
	g_transform_create(&ent->transform);
	// ent->pos     = vec3_create(NULL);
	ent->vel     = vec3_create(NULL);
	ent->vel_max = vec3_create(NULL);
	if (!name)
	{
#ifdef DEBUG
		printf("Naming an unnamed entity!\n");
#endif
		name = "unnamed_gentity";
	}
	ent->name = name;
	ent->art  = NULL;
	// ent->grounded = true;
	//ent->available_actions      = NULL;
	//ent->num_actions	    = 0;
	//ent->available_interactions = NULL;
	//ent->num_interactions       = 0;
	
	ent->subscriptions	  = NULL;

	// g_transform_create(&ent->node.transform);
	/*vec3_t test = ent->node.transform.position;
	if (!test)
	{
		printf("Error happened. yo\n");
		return ent;
	}*/

	//char* buf = calloc(256, sizeof(char));
	//vec3_str(test, buf);
	// sprintf(buf, "%s",buf );
	//printf("%s\n", buf);

	// printf("gnode sample transform %f\n", test[0]);
	return ent;
}

void g_entity_destroy(GEntity* ent)
{
	if (ent->art)
	{
		r_object_destroy(ent->art);
	}
	if (ent->body)
	{
		g_body_destroy(ent->body);
		ent->body = NULL;
	}

	if (ent->think)
	{
		GThinkRec* thinkrec = (GThinkRec*)ent->think;
		if (thinkrec)
		{
			g_think_destroy(thinkrec);
		}
		else
		{
			printf("think cast FAILED\n");
		}
	}

	g_transform_destroy(&ent->transform);

	if ( ent->destroy )
	{
		ent->destroy(ent);
	}else
	{
		grdn_log("No destroy callback for : %s", ent->name);
	}
	// free(ent->pos);
	free(ent->vel);
	free(ent->vel_max);
	if (ent->body)
		free(ent->body);
	
	
	free(ent);
}

void g_entity_update(GEntity* ent)
{
	//internal update logic
	//	most basic, velocity add to pos
	ent->transform.position = vec3_add(ent->transform.position, ent->vel, NULL);
}
