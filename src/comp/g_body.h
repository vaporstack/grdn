//
//  g_body.h
//  grdn
//
//  Created by Andrew Macfarlane on 9/7/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef g_body_h
#define g_body_h

#include <stdbool.h>

typedef struct GBody
{
	bool   grounded;
	double mass;
	double inertia;
	double size;
} GBody;

GBody* g_body_create(void);
void g_body_destroy(GBody* bod);

#endif /* g_body_h */
