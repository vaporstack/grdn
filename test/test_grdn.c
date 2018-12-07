

#include <stdio.h>

#include <grdn/grdn.h>

#include <r4/r4.h>
AppSettings   app_settings;
DebugSettings debug_settings;

static int test_cloth(void)
{
	GCCloth* cloth = grdn_physics_cloth_create(10, 10);

	grdn_physics_cloth_destroy(cloth);
	return 0;
}

static int test_dac(void)
{

	GDac* dac = g_dac_create(32, NULL);
	g_dac_add(dac, 32);
	g_dac_process_one(dac);
	g_dac_add(dac, 16);
	g_dac_process_all(dac);

	for (int i = 0; i < 33; i++)
		g_dac_add(dac, rand() % 8);
	printf("Damage accum: %lu\n", dac->damage);
	return 0;
}

static int test_particles(void)
{
	return 0;
}

static int test_map(void)
{
	GMap* map = g_map_create(4, 4, 16);
	g_map_set(map, 0, 0, 1);
	g_map_fset(map, 0, 0, 5);

	int test = g_map_fget(map, 0, 0, 5);
	printf("does 0,0 has flag %d set? %d\n", 5, test);
	return test;
}

static int test_vmap(void)
{
	printf("testing....\n");
	double* foo = calloc(1, sizeof(double));
	double* bar = calloc(1, sizeof(double));
	*bar	= 5.1237;
	void* map   = vmap_create();
	printf("Put: %p %f\n", foo, *bar);
	vmap_put(map, foo, bar);
	void* baz = vmap_get(map, foo);

	printf("Got: %p %f\n", baz, *(double*)baz);

	vmap_destroy(map);
	return 0;
}

static int test_entsys(void)
{
	printf("Creating entsys\n");
	GEntSys* sys = g_entsys_create();
	printf("Created.\n");
	int* foo = calloc(1, sizeof(int));

	int* bar = calloc(1, sizeof(int));
	*bar     = 555;
	printf("Put %d\n", *bar);
	vmap_put(sys->interactables, foo, bar);
	void* baz = vmap_get(sys->interactables, foo);
	int*  val = (int*)baz;
	printf("Got %d\n", *val);
	return 0;
}

int main(int argc, char** argv)
{
	printf("Running grdn tests.\n");
	printf("making sure grdn header matches library.\n");

	char* compat_string_user = grdn_get_compat_string_header();
	if (grdn_check_compat_match(compat_string_user))
	{
		printf("version matches. %s\n", compat_string_user);
	}
	else
	{
		printf("Version does not match!!\n");
		return 88;
	}
	for (int i = 0; i < argc; i++)
	{
		printf("argv %d %s\n", i, argv[i]);
	}
	free(compat_string_user);

	printf("Testing dac.\n");
	test_dac();

	printf("Testing map.\n");
	test_map();

	printf("Testing Other map.\n");
	test_vmap();

	printf("Testing entsys\n");
	test_entsys();

	printf("Testing cloth.\n");
	test_cloth();

	return 0;
}
