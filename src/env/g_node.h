
//  g_node.c
//  g_node
//
//  Created by Andrew Macfarlane on 04/11/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_node_h_
#define g_node_h_

#include "g_transform.h"

typedef struct GNode
{

	int	   num_children;
	struct GNode* children;
	GTransform    transform;

} GNode;

GNode* g_node_create(void);
void   g_node_destroy(GNode* node);

#endif
