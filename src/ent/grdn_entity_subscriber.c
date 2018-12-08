//
//  grdn_entity_subscriber.c
//  grdn
//
//  Created by vs on 12/7/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "grdn_entity_subscriber.h"
#include <grdn/grdn.h>

#define IDENT_MAX 64

static int* arr = NULL;

static const char** idents = NULL;
static unsigned int num    = 0;

signed int grdn_entity_subscription_create(const char* ident)
{
	if (strlen(ident) > IDENT_MAX)
	{
		grdn_log("Exceeded identifier limit!\n");
		return -1;
	}

	signed int exists = grdn_entity_subscription_query(ident);
	if (exists == -1)
	{
		num++;
		if (!idents)
		{
			idents = calloc(1 * IDENT_MAX, sizeof(char));
		}
		else
		{
			idents = realloc(idents, sizeof(char) * num * IDENT_MAX);
		}
		idents[num - 1] = ident;
	}
	return num - 1;
}

signed int grdn_entity_subscription_query(const char* uuid)
{

	for (int i = 0; i < num; i++)
	{
		if (0 == strcmp(uuid, idents[i]))
		{
			return i;
		}
	}
	return -1;
}

int  grdn_entity_subscription_add(GEntity* entity, const char* ident, subscription_fun fun)
{
	unsigned int idx = grdn_entity_subscription_query(ident);
	if (idx == -1)
	{
		grdn_log("That service does not exist!");
		return -1;
	}
#ifdef DEBUG
	grdn_log("Attempting to subscribe %s :: [%d] %s ", entity->name, idx, ident);
#endif

	if (entity->subscription_indexes == NULL)
	{
		entity->num_subscriptions++;
		entity->subscription_indexes    = calloc(1, sizeof(int));
		entity->subscription_indexes[0] = idx;
		entity->subscriptions = calloc(1, sizeof(subscription_fun));
		entity->subscriptions[0] = fun;
		return 0;
	}

	for (int i = 0; i < entity->num_subscriptions; i++)
	{
		if (idx == entity->subscription_indexes[i])
		{
			grdn_log("Already subscribed to that dawwwwg");
			return 1;
		}
	}
	
	entity->num_subscriptions++;
	entity->subscription_indexes				     = realloc(entity->subscription_indexes, entity->num_subscriptions * sizeof(int));
	entity->subscription_indexes[entity->num_subscriptions - 1] = idx;
	entity->subscriptions				     = realloc(entity->subscriptions, entity->num_subscriptions * sizeof(subscription_fun));
	entity->subscriptions[entity->num_subscriptions - 1] = fun;
	return 0;
}

signed int grdn_entity_subscription_subscribed(GEntity* entity, unsigned int idx)
{
	if (entity->num_subscriptions == 0)
		return -1;
	
	for (signed int i = 0; i < entity->num_subscriptions; i++)
	{
		if (i == idx)
			return idx;
	}
	return -1;
}
