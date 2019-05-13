//
//  grdn_input_connector.h
//  grdn
//
//  Created by vs on 5/13/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef grdn_input_connector_h
#define grdn_input_connector_h
#include <stdbool.h>

typedef void* (*grdn_input_connection)(void*);

typedef struct
{
	bool active;
	const char* name;
	grdn_input_connection act;
	grdn_input_connection start;
	grdn_input_connection stop;
	grdn_input_connection update;
	void* target;
} GInputConnection;

typedef struct
{
	bool active;
	const char* name;
	
}GInputConnectionDirection;

typedef struct
{
	GInputConnection** connections;
	int num;
	
}GInputConnectionList;

GInputConnection* grdn_input_connection_create(const char* name, grdn_input_connection act, void* target);
void grdn_input_connection_list_add(GInputConnectionList* list, GInputConnection* conn);

#endif /* grdn_input_connector_h */
