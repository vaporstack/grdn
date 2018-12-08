//
//  grdn_action_mgr.c
//  grdn
//
//  Created by vs on 12/7/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "grdn_action_mgr.h"

#include <grdn/src/util/grdn_log.h>

GActionMgr* grdn_action_mgr_create(void)
{
	GActionMgr* mgr = calloc(1, sizeof(GActionMgr));
	
	
	return mgr;
}

void grdn_action_mgr_add(GActionMgr* mgr, entity_action action)
{
	if ( mgr->num == 0 )
	{
		mgr->num++;
		mgr->actions = calloc(1, sizeof(grdn_action_function));
		mgr->actions[0] = &action;
	}else{
		mgr->num++;
		mgr->actions = realloc(mgr->actions, mgr->num * sizeof(grdn_action_function));
		mgr->actions[mgr->num - 1] = &action;
		
	}
#ifdef DEBUG
	grdn_log("added action %d", mgr->num -1);
#endif
	
}

void grdn_action_mgr_remove(GActionMgr* mgr, entity_action action)
{
	
	for ( int i = 0; i < mgr->num; i++ )
	{
		entity_action act = *mgr->actions[i];
		if ( act == action)
		{
			grdn_log("Removing action %d", i);
			
		}
	}
}
