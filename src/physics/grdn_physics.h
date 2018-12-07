//
//  grdn_physics.h
//  r4
//
//  Created by Andrew Macfarlane on 1/2/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef grdn_physics_h
#define grdn_physics_h

#include <grdn/grdn.h>

#ifdef G4_ENABLE_CHIPMUNK

#include "../../../wsh/wsh.h"
#include "../geo/r_vec.h"
#include <stdio.h>

typedef struct PhysicsObject
{
	void*  body;
	void*  shape;
	WLine* geo;
	Vec2   position;
	Vec2   velocity;
} PhysicsObject;

PhysicsObject* grdn_physics_object_create(void);
void	   grdn_physics_object_destroy(PhysicsObject*);

PhysicsObject* grdn_physics_object_createfromline(WLine*);

void grdn_physics_object_set_position(PhysicsObject*, float, float);
void grdn_physics_object_set_velocity(PhysicsObject*, float, float);
void grdn_physics_object_update(PhysicsObject*);
void grdn_physics_tick(void);

//void grdn_physics_init(void);
//void grdn_physics_deinit(void);

void grdn_physics_render_object(PhysicsObject*);

#endif

#endif /* grdn_physics_h */
