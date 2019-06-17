

#ifndef g_levelgen_h
#define g_levelgen_h

typedef struct
{
	void** areas;
	int    num;
} GLevel;

typedef struct
{
	int complexity;
	int limit;
} GLevelGenAttr;

void g_level_add(GLevel* level, void* area);

GLevel* g_level_interior(GLevelGenAttr attr);
GLevel* g_level_exterior(GLevelGenAttr attr);
void g_level_destroy(GLevel* level);

#endif
