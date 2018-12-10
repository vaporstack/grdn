//
//  grdn_action_mgr.h
//  grdn
//
//  Created by vs on 12/7/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef grdn_action_mgr_h
#define grdn_action_mgr_h

#include  "g_entity.h"

#include <stdio.h>

typedef void (*entity_action)( GEntity* ent, GEntity* subject);

typedef struct GActionMgr
{
	int num;
	entity_action** actions;
	int active_num;
	entity_action** active;
}GActionMgr;

GActionMgr* grdn_action_mgr_create(void);
void grdn_action_mgr_destroy(GActionMgr* mgr);

void grdn_action_mgr_add(GActionMgr* mgr, entity_action action);
void grdn_action_mgr_remove(GActionMgr* mgr, entity_action action);

void grdn_action_mgr_activate(GActionMgr* mgr, entity_action action);
void grdn_action_mgr_deactivate(GActionMgr* mgr, entity_action action);

#endif /* grdn_action_mgr_h */
