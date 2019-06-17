

#include "g_levelgen.h"

#include <stdio.h>
#include <stdlib.h>

#include "g_area.h"

GLevel* g_level_interior(GLevelGenAttr attr)
{
	return NULL;
}

void g_level_add(GLevel* level, void* area)
{
	level->num++;
	level->areas		     = realloc(level->areas, level->num * sizeof(GArea));
	level->areas[level->num - 1] = area;
	printf("level has %d\n", level->num);
}

static void link(GLevel* level)
{
}

GLevel* g_level_create(void)
{
	GLevel* level = calloc(1, sizeof(GLevel));
	return level;
}

GLevel* g_level_exterior(GLevelGenAttr attr)
{
	printf("Generating an exterior\n");
	GLevel* level = g_level_create();
	for (int i = 0, n = attr.limit; i < n; i++) {
		printf("level %d\n", i);
		GArea* area = g_area_create();
		g_level_add(level, area);
		//free(area);
	}
	return level;
}

void g_level_destroy(GLevel* level)
{
	if (!level) {
		printf("Can't destroy a NULL level\n");
		return;
	}
	for (int i = 0, n = level->num; i < n; i++) {
		g_area_destroy(level->areas[i]);
	}
	free(level);
}
