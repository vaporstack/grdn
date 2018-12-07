//
//  vmap.cpp
//  run
//
//  Created by vs on 11/17/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "vmap.h"

#include <map>
typedef std::map<void*, void*> Map;

#ifdef __cplusplus
extern "C" {
#endif

void* vmap_create()
{
	return reinterpret_cast<void*>(new Map);
}

void vmap_put(void* map, void* key, void* data)
{
	Map* m = reinterpret_cast<Map*>(map);
	m->insert(std::pair<void*, void*>(key, data));
}

void* vmap_get(void* map, void* key)
{
	Map* m = reinterpret_cast<Map*>(map);
	return m->find(key)->second;
}

void vmap_destroy(void* map)
{
	Map* m = reinterpret_cast<Map*>(map);
	delete (m);
} // extern "C"

#ifdef __cplusplus
}
#endif
