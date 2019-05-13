//
//  grdn_input_connector.c
//  grdn
//
//  Created by vs on 5/13/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#include "grdn_input_connector.h"

#include <stdlib.h>

GInputConnection* grdn_input_connection_create(const char* name, grdn_input_connection act, void* target)
{
	GInputConnection* con = calloc(1, sizeof(GInputConnection));
	
	
	con->name = name;
	con->act = act;
	con->target = target;
	
	return con;
}

void grdn_input_connection_list_add(GInputConnectionList* list, GInputConnection* conn)
{
	list->num++;
	list->connections = realloc(list->connections, list->num * sizeof(GInputConnection));
	list->connections[list->num - 1] = conn;
	
	
}
