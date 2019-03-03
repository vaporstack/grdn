//
//  grdn_city.h
//  grdn
//
//  Created by vs on 3/2/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef grdn_city_h
#define grdn_city_h

#include <stdio.h>

#include "grdn_feature.h"
#include "grdn_road.h"

typedef struct GrdnCity
{
	unsigned num_features;
	GrdnRoadNetwork* network;
	CPoint urban_center;
	CPoint urban_center_goal;
}GrdnCity;

#endif /* grdn_city_h */
