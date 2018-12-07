
//  g_overlay.c
//  g_overlay
//
//  Created by Andrew Macfarlane on 05/13/18.
//  Copyright © 2018 vaporstack. All rights reserved.

#ifndef g_overlay_h_
#define g_overlay_h_

#include <r4/r4.h>

typedef struct GOverlayRec
{
	int    foo;
	double rad;
	double thicccc;
	RLine* geo;
	void*  tess;
} GOverlayRec;

GOverlayRec* g_overlay_create(void);
void g_overlay_destroy(GOverlayRec* rec);

#endif
