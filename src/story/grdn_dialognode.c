
//
//  grdn_dialognode.c
//  grdn
//
//  Created by vs on 11/3/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "grdn_dialognode.h"
#include <drw/drw.h>
#include <stdlib.h>

GDialogNode* grdn_dialognode_create(void* gui, const char** text, unsigned int num)
{
	GDialogNode* node = calloc(1, sizeof(GDialogNode));
	node->responses	= calloc(1, sizeof(GDialogNode));
	node->responses[0]     = grdn_dialog_create(gui, text, num);
	node->num	 = 1;
	node->cur	 = 0;
	return node;
}

void grdn_dialognode_destroy(GDialogNode* node)
{
	for (int i = 0; i < node->num; i++)
		grdn_dialog_destroy(node->responses[i]);
	free(node);
}

void grdn_dialognode_draw(GDialogNode* node)
{
	GDialog* dlog = node->responses[node->cur];
	if (!dlog->text)
	{
		printf("No text!\n");
		drw_type_draw("FAiL");
		return;
	}
	
	const char* text = dlog->text[dlog->cur];

	drw_type_draw(text);
}
