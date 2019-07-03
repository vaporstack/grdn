//
//  grdn_sun.h
//  grdn
//
//  Created by vs on 7/2/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef grdn_sun_h
#define grdn_sun_h

#include <grdn/grdn.h>


typedef struct
{
	double period;
	double intensity;
	double output;
	//	double flare
}GSun;

GEntity* grdn_sun_create(void);

#endif /* grdn_sun_h */
