//
//  grdn_dialogtree.h
//  grdn
//
//  Created by vs on 11/3/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef grdn_dialogtree_h
#define grdn_dialogtree_h

#include <stdio.h>
#include "grdn_dialognode.h"

typedef struct GDialogTree
{
	//unsigned int num;
	GDialogNode* root;
} GDialogTree;

GDialogTree* grdn_dialogtree_test(void);

GDialogTree* grdn_dialogtree_create(GDialogNode* root);
void grdn_dialogtree_destory(GDialogTree* tree);

void grdn_dialogtree_draw(GDialogTree* tree);

#endif /* grdn_dialogtree_h */
