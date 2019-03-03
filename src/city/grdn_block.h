//
//  grdn_block.h
//  grdn
//
//  Created by vs on 3/2/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef grdn_block_h
#define grdn_block_h

#include "grdn_building.h"
#include "grdn_road.h"

typedef struct GrdnBlock
{
	GrdnRoad**    boundaries;
	unsigned      num_boundaries;
	GrdnBuilding* buildings;
} GrdnBlock;

#endif /* grdn_block_h */
