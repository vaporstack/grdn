
//
//  grdn_dialognode.c
//  grdn
//
//  Created by vs on 11/3/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "grdn_dialognode.h"
#include <stdlib.h>
#include <drw/drw.h>

GDialogNode* grdn_dialognode_create(void* gui, const char** text, unsigned int num )
{
	GDialogNode* node = calloc(1, sizeof(GDialogNode));
	node->dlog = calloc(1, sizeof(GDialogNode));
	node->dlog[0] = grdn_dialog_create(gui, text, num);
	node->num = 1;
	node->cur = 0;
	return node;
}

void grdn_dialognode_destroy(GDialogNode* node)
{
	for ( int i = 0; i < node->num; i++ )
		grdn_dialog_destroy(node->dlog[i]);
	free(node);
}

void grdn_dialognode_draw(GDialogNode* node)
{
	GDialog* dlog = node->dlog[node->cur];
	if (!dlog->text)
	{
		printf("No text!\n");
		drw_text_hpvec_draw("FAiL");
		return;
	}
	const char* text = dlog->text[dlog->cur];
	
	drw_text(text);
}
