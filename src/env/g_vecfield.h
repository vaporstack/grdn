//
//  grdn_dialog.h
//  r4_ios
//
//  Created by Andrew Macfarlane on 1/25/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef g_vecfield_h_
#define g_vecfield_h_

#include <stdbool.h>
#include <stdio.h>

typedef struct
{
	int     width;
	int     height;
	float** data;
} VecField;

VecField* g_vecfield_create(int, int);
void      g_vecfield_destroy(VecField*);
void      g_vecfield_reset(VecField*);
void      g_vecfieldrw_populate(VecField*, int, int, float);
void      g_vecfield_print(VecField*);
void      g_vecfield_diffuse(VecField*, float);
void      g_vecfield_damp(VecField*, float);
void      g_vecfield_add(VecField*, float);
void      g_vecfield_clamp(VecField*, float);

#endif /* g_vecfield_h_ */
