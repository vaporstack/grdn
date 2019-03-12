//
//  grdn_dialogtree.c
//  grdn
//
//  Created by vs on 11/3/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "grdn_dialogtree.h"

#include <stdlib.h>


GDialogTree* grdn_dialogtree_test(void)
{
	//GDialogTree* tree = calloc(1, sizeof(GDialogTree));
	return NULL;
}

GDialogTree* grdn_dialogtree_create(GDialogNode* node)
{
	GDialogNode* root = NULL;
	if (!node)
	{
		root = grdn_dialognode_create(NULL, NULL, 0);

	}else{
		root = node;
	}
	
	GDialogTree* tree = calloc(1, sizeof(GDialogTree));
	tree->root = root;
	
	return tree;
}

void grdn_dialogtree_destory(GDialogTree* tree)
{
	
}

void grdn_dialogtree_draw(GDialogTree* tree)
{
	GDialogNode* root = tree->root;
	grdn_dialognode_draw(root);
}
