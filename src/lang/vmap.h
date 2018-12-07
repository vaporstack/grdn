//
//  vmap.hpp
//  run
//
//  Created by vs on 11/17/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef vmap_hpp
#define vmap_hpp

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void* vmap_create(void);
void  vmap_destroy(void* map);

void  vmap_put(void* map, void* key, void* data);
void* vmap_get(void* map, void* key);

#ifdef __cplusplus
}
#endif

#endif /* vmap_hpp */
