//
//  grdn_dialog.c
//  grdn
//
//  Created by vs on 11/3/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "grdn_dialog.h"

#include <stdlib.h>

#include <gui/gui.h>

GDialog* grdn_dialog_create(void* gui, const char** text, unsigned int num)
{
	GDialog* dlog = calloc(1, sizeof(GDialog));
	dlog->text = text;
	dlog->num = num;
	dlog->cur = 0;
	dlog->charpos = 0;
	GuiComponent* cmp = gui_component_create(gui);
	dlog->display = cmp;
	return dlog;
}

void grdn_dialog_destroy(GDialog* dlog)
{
	free(dlog);
	
}
