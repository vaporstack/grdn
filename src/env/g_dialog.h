//
//  g_dialog.h
//  r4_ios
//
//  Created by Andrew Macfarlane on 1/25/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef g_dialog_h
#define g_dialog_h

#include <r4/src/geo/r_rect.h>


#include <stdbool.h>
#include <stdio.h>

typedef struct
{
	bool	needs_update;
	const char* text;
	Vec2	position;
	Vec2	orientation;
	int	 vert_num;
	RRect*      bounds;
	float*      verts;
	float       pad_size;
} DialogBox;

DialogBox* g_dialog_create(float x, float y, char* text);
void       g_dialog_update(DialogBox*);
void       g_dialog_render(DialogBox*);
void       g_dialog_destroy(DialogBox*);
void       g_dialog_set_text(DialogBox*, const char* text);

#endif /* g_dialog_h */
