
//  g_weather.c
//  g_weather
//
//  Created by Andrew Macfarlane on 29/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_weather_h_
#define g_weather_h_

#include <deps/gl-matrix/gl-matrix.h>

typedef struct GWeather
{
	vec3_t wind;
	vec3_t gtemp;
	vec3_t ltemp;
} GWeather;

GWeather* g_weather_create(void);
void      g_weather_destroy(GWeather* w);

void g_weather_update(GWeather* w);

#endif
