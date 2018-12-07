
//  g_property.c
//  g_property
//
//  Created by Andrew Macfarlane on 05/13/18.
//  Copyright © 2018 vaporstack. All rights reserved.

#ifndef g_property_h_
#define g_property_h_

typedef struct GProperty
{
	int	 foo;
	const char* expression;
	double*     keyframes;
	int	 num_keyframes;
} GProperty;

GProperty* g_property_create(double* addr, int dimensions);
void g_property_destroy(GProperty* prop);
void g_property_update(GProperty* prop);

#endif
