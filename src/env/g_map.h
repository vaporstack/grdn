
//  g_map.c
//  g_map
//
//  Created by Andrew Macfarlane on 08/10/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_map_h_
#define g_map_h_

/** @file wsh_point.h
 *  @brief simple class for "traditional" block system for collisions etc
 *  2d tilemap
 *
 *  @author Andrew Macfarlane (_ruminant on twitter dawt cawm)
 *  @bug All the bugs.
 */

/*
 *	@brief GMap
 *	struct that holds gmap attrs
 */
typedef struct GMap
{
	int  width;
	int  height;
	int  scale;
	int* data;

} GMap;

/*
 *	@param in width
 *	@param in height
 */
GMap* g_map_create(int width, int height, int scale);
void  g_map_destroy(GMap* map);
void  g_map_set(GMap* map, int x, int y, int val);
int   g_map_get(GMap* map, int x, int y);
void  g_map_fset(GMap* map, int x, int y, int val);
void  g_map_funset(GMap* map, int x, int y, int val);

int  g_map_fget(GMap* map, int x, int y, int val);
void g_map_print(GMap* map);

#endif
