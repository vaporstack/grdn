
//  g_map.c
//  g_map
//
//  Created by Andrew Macfarlane on 08/10/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_map.h"

#include <stdlib.h>

#include <stdio.h>

static int set_bit(int data, int flag) { return data |= flag; }

static int unset_bit(int data, int bit) { return data &= ~bit; }

static int get_index(GMap* map, int x, int y) {
	int v = (map->width * y) + x;
	if ( v < 0 || v > map->width * map->height)
	{
		return -1;
	}
	return v;
}

GMap* g_map_create(int width, int height, int scale)
{
	GMap* map   = calloc(1, sizeof(GMap));
	map->width  = width;
	map->height = height;
	map->scale = scale;
	map->data   = calloc(width * height, sizeof(int));
	// printf("foo\n");
	// set_bit(map->data, 0, 0)
	return map;
}

void g_map_destroy(GMap* map)
{
	if (map->data) {
		free(map->data);
	}
	
	free(map);
}

void g_map_set(GMap* map, int x, int y, int val)
{
	int index	= get_index(map, x, y);
	if ( index != -1 )
		map->data[index] = val;
}

int g_map_get(GMap* map, int x, int y)
{
	int index = get_index(map, x, y);
	if ( index == -1 )
		return -1;
	
	return map->data[index];
}

void g_map_funset(GMap* map, int x, int y, int val)
{
	int index = get_index(map, x, y);
	int data  = map->data[index];
	unset_bit(data, val);
	map->data[index] = val;
}

void g_map_fset(GMap* map, int x, int y, int val)
{
	int index = get_index(map, x, y);
	int data  = map->data[index];
	set_bit(data, val);
	map->data[index] = val;
}

int g_map_fget(GMap* map, int x, int y, int val)
{
	int index = get_index(map, x, y);
	int data  = map->data[index];
	return (data & val);
}

void g_map_print(GMap* map)
{
	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			int v = g_map_get(map, x, y);
			printf("%d", v);
		}
		printf("\n");
	}
}
