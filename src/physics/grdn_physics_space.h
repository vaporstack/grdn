//
//  grdn_physics_space.h
//  grdn
//
//  Created by vs on 5/29/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef grdn_physics_space_h
#define grdn_physics_space_h


typedef struct GPhysicsSpace
{
	void* space;
}GPhysicsSpace;

GPhysicsSpace* grdn_physics_space_create(void);
void grdn_physics_space_destroy(GPhysicsSpace* space);

void grdn_physics_space_update(GPhysicsSpace* space);

#endif /* grdn_physics_space_h */
