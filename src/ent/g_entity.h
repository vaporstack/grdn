//
//  g_entity.h
//  r4
//
//  Created by Andrew Macfarlane on 1/27/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef g_entity_h
#define g_entity_h

//#include "../garden.h"
#include "../comp/g_body.h"
#include "../env/g_node.h"
#include <deps/gl-matrix/gl-matrix.h>
#include <r4/src/geo/r_object.h>
//#include "grdn_action_mgr.h"

//#include <wsh/wsh.h>

typedef void (*grdn_action_function)(void* actor, void* target);

typedef enum {
	G_ENTITY_SCENERY  = 0x01,
	G_ENTITY_ENEMY    = 0x02,
	G_ENTITY_INTERACT = 0x04,
	//DATA     = 0x08,
	GUARD,
	ALL = 0xFF
} g_entity_flags;

typedef struct GEntity
{
	int	 id;
	const char* name;

	int dir;
	// vec3_t pos;
	vec3_t vel;
	vec3_t vel_max;
	void (*draw)(struct GEntity* ent);
	void (*update)(struct GEntity* ent);
	void (*destroy)(struct GEntity* ent); //	callback for destroying any custom data

	void* think;

	RObject* art;

	//unsigned int	  num_actions;
	//grdn_action_function* available_actions;

	//unsigned int	  num_interactions;
	//grdn_action_function* available_interactions;
	signed int layer;
	double draw_priority;
	
	int	flags;
	// WSequence* seq;
	GBody* body;
	void*  brain;
	void*  data;
	void*  inventory;
	void*  weapons;
	int    num_subscriptions;
	int*   subscription_indexes;
	void (**subscriptions)(void* sender, struct GEntity* receiver);

	void* action_mgr;
	GNode node;
	// bool       grounded;
	GTransform transform;
	// int think_interval;
	void* area;
} GEntity;

typedef void (*grdn_entity_draw_function)(struct GEntity*);

typedef struct GEntityHnd
{
	GEntity* src;
} GEntityHnd;

GEntity* g_entity_create(const char* name);
void     g_entity_destroy(GEntity*);
void     g_entity_update(GEntity*);

#endif /* g_entity_h */
