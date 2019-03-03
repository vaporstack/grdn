//
//  grdn_road.h
//  grdn
//
//  Created by vs on 3/2/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef grdn_road_h
#define grdn_road_h

#include <coer/coer.h>
#include <stdio.h>

typedef struct GrdnRoad
{
	double		  len;
	double		  dir;
	CPoint		  a;
	CPoint		  b;
	struct GrdnRoad** connections;
	unsigned	  connection_num;
} GrdnRoad;

typedef struct GrdnRoadNetwork
{
	unsigned   num;
	GrdnRoad** data;
} GrdnRoadNetwork;

GrdnRoad* grdn_road_create(void);
GrdnRoad* grdn_road_create_2p(CPoint a, CPoint b);

#endif /* grdn_road_h */
