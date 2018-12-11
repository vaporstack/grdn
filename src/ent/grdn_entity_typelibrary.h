//
//  grdn_entity_typelibrary.h
//  grdn
//
//  Created by vs on 12/10/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef grdn_entity_typelibrary_h
#define grdn_entity_typelibrary_h

typedef struct GrdnTypeLibrary{
	const char** idents;
	unsigned int * data;
	unsigned int num;
}GrdnTypeLibrary;

unsigned int grdn_entity_typelibrary_register(const char* type);
unsigned int grdn_entity_typelibrary_query(const char* type);

#endif /* grdn_entity_typelibrary_h */
