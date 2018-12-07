
//  g_sticky.c
//  g_sticky
//
//  Created by Andrew Macfarlane on 08/10/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_sticky_h_
#define g_sticky_h_

/** @file g_sticky.h
 *  @brief testbed for making some funny stick figures that don't look like west
 * of loathing
 *  (though I LOVE west of loathing)
 *
 *  @author Andrew Macfarlane (_ruminant on twitter dawt cawm)
 *  @bug All the bugs.
 */

typedef struct GSticky
{
	int blah;

} GSticky;

/**
 *
 *@return GSticky
 *
 */
GSticky *g_sticky_create(void);

/*
 *
 *
 */
void g_sticky_update(GSticky *stick);

/**
 *
 *
 */
void g_sticky_destroy(GSticky *stick);

#endif
