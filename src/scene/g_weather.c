
//  g_weather.c
//  g_weather
//
//  Created by Andrew Macfarlane on 29/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "g_weather.h"

#include <stdlib.h>

GWeather* g_weather_create(void)
{
	GWeather* weather = calloc(1, sizeof(GWeather));
	weather->wind     = vec3_create(NULL);
	weather->gtemp    = vec3_create(NULL);
	weather->ltemp    = vec3_create(NULL);
	return weather;
}

void g_weather_destroy(GWeather* weather)
{
	free(weather->wind);
	free(weather->gtemp);
	free(weather->ltemp);
}

void g_weather_update(GWeather* weather) {}
