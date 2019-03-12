//
//  grdn_dialognode.h
//  grdn
//
//  Created by vs on 11/3/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef grdn_dialognode_h
#define grdn_dialognode_h

#include <stdio.h>

#include "grdn_dialog.h"

typedef struct GDialogNode
{
	unsigned int num;
	GDialog* text;
	GDialog** responses;
	struct GDialogNode** links;
	unsigned int cur;
}GDialogNode;

GDialogNode* grdn_dialognode_create(void* gui, const char** text, unsigned int num);
void grdn_dialognode_destroy(GDialogNode* node);
void grdn_dialognode_draw(GDialogNode* node);

#endif /* grdn_dialognode_h */
