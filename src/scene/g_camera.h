
//  g_camera.c
//  g_camera
//
//  Created by Andrew Macfarlane on 29/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_camera_h_
#define g_camera_h_

//#include <grdn/grdn.h>

#include "../ent/g_entity.h"
#include <gl-matrix/gl-matrix.h>

typedef struct GCamera
{
	bool    shake_enabled;
	bool    shake_decay;
	double  shake_decay_rate;
	double  shake_mag;
	vec3_t  shake;
	vec3_t  position;
	vec3_t* target;
	// GEntityHnd* target;
} GCamera;

GEntity* g_camera_create(void);
void     g_camera_destroy(GEntity* cam);
void     g_camera_apply(GEntity* cam);
void     g_camera_deapply(GEntity* cam);
void     g_camera_update(GEntity* cam);
GEntity* g_camera_get_cur(void);
void     g_camera_set_target(GEntity* cam, vec3_t* target);

#endif
