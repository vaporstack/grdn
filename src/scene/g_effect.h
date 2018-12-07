
//  g_effect.c
//  g_effect
//
//  Created by Andrew Macfarlane on 03/11/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_effect_h_
#define g_effect_h_

typedef struct GEffect
{
	int foo;
	void (*effect_update_func)(void);
	void (*effect_render_func)(void);
	void* data;
} GEffect;

GEffect* g_effect_create(void);
void     g_effect_destroy(GEffect* effect);

GEffect* g_effect_create_light(void);
GEffect* g_effect_create_smoke(void);

#endif
