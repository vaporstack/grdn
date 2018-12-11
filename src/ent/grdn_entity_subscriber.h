//
//  grdn_entity_subscriber.h
//  grdn
//
//  Created by vs on 12/7/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef grdn_entity_subscriber_h
#define grdn_entity_subscriber_h

#include "g_entity.h"
#include <stdbool.h>

//	this is more or less for direct (consensual) transactions between entity types.

//#include <stdio.h>

/*
typedef struct GEntitySubscription
{
	int id;

};
*/

typedef void (*subscription_fun)(void* sender, GEntity* receiver);


//	todo add "provider" or something to these two to make it more clear
signed int grdn_entity_subscription_create(const char* ident);
signed int grdn_entity_subscription_query(const char* ident);

signed int grdn_entity_subscription_add(GEntity* entity, const char* ident, subscription_fun fun);
signed int grdn_entity_subscription_subscribed(GEntity* entity, unsigned int idx);

#endif /* grdn_entity_subscriber_h */
