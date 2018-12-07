//
//  grdn_dialog.c
//  r4_ios
//
//  Created by Andrew Macfarlane on 1/25/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "g_vecfield.h"

#include <stdbool.h>

#include <grdn/grdn.h>
#include <stdlib.h>
#include <string.h>

VecField* g_vecfield_create(int width, int height)
{
	VecField* vec = malloc(sizeof(VecField));
	vec->width    = width;
	vec->height   = height;
	vec->data     = malloc(sizeof(float*) * width * height);

	for (int y = 0; y < height; ++y) {
		vec->data[y] = malloc(sizeof(float) * width);
		memset(vec->data[y], 0, sizeof(float) * width);
	}

	//'dereference of an undefined pointer value, commenting out
	// vec->data[2][2] = 1.;
	return vec;
}

void g_vecfield_destroy(VecField* vec)
{
	free(vec->data);
	vec->data = NULL;
	free(vec);
}

void g_vecfield_print(VecField* vec)
{
	for (int y = 0; y < vec->height; ++y) {
		for (int x = 0; x < vec->width; ++x) {
			printf("%.2f ", vec->data[y][x]);
		}
		printf("\n");
	}
}
void g_vecfield_add(VecField* vec, float v)
{
	for (int y = 0; y < vec->height; ++y) {
		for (int x = 0; x < vec->width; ++x) {
			vec->data[y][x] *= v;
		}
	}
}

void g_vecfield_damp(VecField* vec, float damp)
{
	for (int y = 0; y < vec->height; ++y) {
		for (int x = 0; x < vec->width; ++x) {
			vec->data[y][x] *= damp;
		}
	}
}

void g_vecfield_clamp(VecField* vec, float cl)
{
	for (int y = 0; y < vec->height; ++y) {
		for (int x = 0; x < vec->width; ++x) {
			float v = vec->data[y][x];
			if (v > cl)
				vec->data[y][x] = cl;
		}
	}
}
void g_vecfield_diffuse(VecField* vec, float div)
{
	for (int y = 0; y < vec->height; ++y) {
		for (int x = 0; x < vec->width; ++x) {

			float val = vec->data[y][x];

			if (val == 0)
				continue;

			float slice = val * div;
			vec->data[y][x] -= slice;

			for (int y2 = -1; y2 < 2; ++y2) {
				for (int x2 = -1; x2 < 2; ++x2) {
					int dx = x + x2;
					int dy = y + y2;
					if (dx >= 0 && dx < vec->width &&
					    dy >= 0 && dy < vec->height) {
						vec->data[dy][dx] +=
						    slice / 10.;
					}
				}
			}
		}
	}
}
