//
//  grdn_feature.h
//  grdn
//
//  Created by vs on 3/2/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef grdn_feature_h
#define grdn_feature_h

enum
{
	GRDN_FEATURE_RIVER,
	GRDN_FEATURE_MOUNTAIN,
	GRDN_FEATURE_LAKE
};

typedef struct GrdnFeature
{
	float** x;
	float** y;
	unsigned num;
	unsigned type;
}GrdnFeature;

typedef struct GrdnFeatureSet
{
	unsigned num;
	GrdnFeature** data;
}GrdnFeatureSet;

GrdnFeature* grdn_feature_create_river(void);
GrdnFeature* grdn_feature_create_mountains(void);

#endif /* grdn_feature_h */
