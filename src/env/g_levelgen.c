

#include "g_levelgen.h"

#include "g_area.h"
#include <assert.h>
#include <grdn/src/env/g_portal.h>
#include <r4/src/core/r_random.h>
#include <r4/src/core/r_time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static RRandom rng;

GArea* random_area_with_no_links(GLevel* level, GArea* exclude);
GArea* any_random_area(GLevel* level, GArea* exclude);

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

static void link_two_areas(GLevel* level)
{

	GArea* a = random_area_with_no_links(level, NULL);
	GArea* b = any_random_area(level, a);
	assert(a != b);

	printf("Matched %p and %p\n", a, b);

	GEntity* ga = g_entity_create("portal_a");
	GEntity* gb = g_entity_create("portal_b");

	GPortal* p = g_portal_create(a, b, ga, gb, true);

	g_area_register_entity(a, ga);
	g_area_register_entity(b, gb);

	// g_area_link_add(a, b);
	// g_area_link_add(b, a);

	/*int n = level->num;
	int*    pool  = calloc(n, sizeof(int));


	int* store = calloc(n, sizeof(int));
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
	*/
}

GLevel* g_level_create(void)
{
	GLevel* level = calloc(1, sizeof(GLevel));
	return level;
}

static void print(int* data, int num)
{
	for (int i = 0; i < num; i++)
	{
		printf("%d,", data[i]);
	}
	printf("\n");
}

bool all_areas_linked(GLevel* level)
{
	for (int i = 0; i < level->num; i++)
	{
		GArea* area = level->areas[i];
		if (area->link_num == 0)
			return false;
	}
	return true;
}

GArea* any_random_area(GLevel* level, GArea* exclude)
{
	printf("fetching any random area that isn't %p\n", exclude);

	GArea* match = NULL;

	bool done = false;
	while (!done)
	{
		int which = r_rand_double(NULL) * level->num;
		printf("maybe %d\n", which);
		match = level->areas[which];
		printf("%p\n", match);
		if (match != exclude && match != NULL)
			return match;
	}
	// do {
	// 	match = level->areas[(int)r_rand_double(NULL) * level->num];
	// } while (match == NULL || match == exclude);

	return NULL;
	//return match;
}

GArea* random_area_with_no_links(GLevel* level, GArea* exclude)
{
	int n = level->num;

	//put all the unlinked areas into the pool

	int* orphans = NULL;
	//calloc(n, sizeof(int));
	int ct = 0;
	for (int i = 0; i < n; i++)
	{
		GArea* area = level->areas[i];
		if (area->link_num == 0)
		{
			ct++;
			orphans		= realloc(orphans, ct * sizeof(int));
			orphans[ct - 1] = i;
		}
	}
	printf("have %d orphans\n", ct);
	int    which = -1;
	GArea* match = NULL;
	do
	{
		printf("not matched yet...\n");
		which = r_rand_double(NULL) * ct;
		match = level->areas[(int)which];
		print(orphans, ct);
	} while (match == exclude || match == NULL);

	printf("finished. new match is %p\n", match);

	//GArea* area = level->areas[which];
	free(orphans);
	return match;
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

	for (int i = 0, n = attr.limit; i < n; i++)
	{
		//printf("level %d\n", i);
		GArea* area      = g_area_create();
		area->position.x = (-.5 + r_rand_double(&rng)) * attr.bounds;
		area->position.y = (-.5 + r_rand_double(&rng)) * attr.bounds;
		g_level_add(level, area);
		//pool[i] = i;
	}

	printf("let's start this potentially lock shit forever\n");
	while (!all_areas_linked(level))
	{
		link_two_areas(level);
	}

	link_two_areas(level);
	 //	ok something got lost here
	
	
	// while (!all_areas_linked(level)) {
	// 	link_two_areas(level);
	// }

	return level;
}

void g_level_destroy(GLevel* level)
{
	if (!level)
	{
		printf("Can't destroy a NULL level\n");
		return;
	}
	for (int i = 0, n = level->num; i < n; i++)
	{
		g_area_destroy(level->areas[i]);
	}
	free(level);
}
