

#include "g_levelgen.h"

#include "g_area.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

#include <grdn/src/env/g_portal.h>
#include <r4/src/core/r_random.h>
#include <r4/src/core/r_time.h>

static RRandom rng;

GLevel* g_level_create(void)
{
	GLevel* level = calloc(1, sizeof(GLevel));
	return level;
}

static void print(int* data, int num)
{
	for (int i = 0; i < num; i++) {
		printf("%d,", data[i]);
	}
	printf("\n");
}

GLevel* g_level_exterior(GLevelGenAttr attr)
{
	//if (!rng)
	time_t seconds;

	seconds = time(NULL);

	double t = r_time();
	printf("Creating a seed for %d\n", seconds);
	rng = r_rand_create_seed(seconds);

	//printf("Generating an exterior\n");
	GLevel* level = g_level_create();
	int*    pool  = calloc(attr.limit, sizeof(int));

	for (int i = 0, n = attr.limit; i < n; i++) {
		//printf("level %d\n", i);
		GArea* area      = g_area_create();
		area->position.x = (-.5 + r_rand_double(&rng)) * attr.bounds;
		area->position.y = (-.5 + r_rand_double(&rng)) * attr.bounds;
		g_level_add(level, area);
		pool[i] = i;
	}

	int* store = calloc(attr.limit, sizeof(int));
	store      = memcpy(store, pool, attr.limit * sizeof(int));

	print(pool, attr.limit);
	int n = attr.limit;
	int a = pool[(int)(r_rand_double(&rng) * n)];

	printf("a: %d\n", a);
	for (int i = a; i < n - 1; i++) {
		pool[i] = pool[i + 1];
	}
	n--;
	print(pool, n);

	int b = pool[(int)(r_rand_double(&rng) * n)];
	printf("b: %d\n", b);
	for (int i = b; i < n - 1; i++) {
		pool[i] = pool[i + 1];
	}
	n--;
	print(pool, n);

	printf("Linking %d and %d\n", a, b);

	GEntity* ga = g_entity_create("portal_a");
	GEntity* gb = g_entity_create("portal_b");

	GPortal* p = g_portal_create(level->areas[a], level->areas[b], ga, gb, true);

	g_area_register_entity(level->areas[a], ga);

	g_area_register_entity(level->areas[b], gb);
	printf("Created link between %p %p\n", level->areas[a], level->areas[b]);
	//print(pool, n);
	free(pool);
	free(store);

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
