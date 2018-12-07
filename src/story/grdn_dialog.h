//
//  grdn_dialog.h
//  grdn
//
//  Created by vs on 11/3/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef grdn_dialog_h
#define grdn_dialog_h

#include <stdio.h>

typedef struct GDialog
{
	const char** text;
	unsigned int num;
	unsigned int cur;
	unsigned int charpos;
	void* display;
	double start_time;
}GDialog;


GDialog* grdn_dialog_create(void* gui, const char** text, unsigned int num);
void grdn_dialog_destroy(GDialog* dlog);
void grdn_dialog_advance(double time, double speed);

#endif /* grdn_dialog_h */
