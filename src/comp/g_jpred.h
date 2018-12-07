
//  g_jpred.c
//  g_jpred
//
//  Created by Andrew Macfarlane on 08/10/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef g_jpred_h_
#define g_jpred_h_

//	jump predictor mechanism to allow roadrunner and bouncy jumps

typedef struct GJPred
{
	int *frames;
	int  current_frame;
	int  tolerance;
	int  grounded_real;
	int  grounded_fake;
} GJPred;

GJPred *g_jpred_create(void);
int     g_jpred_check(void);
void    g_jpred_destroy(void);

#endif
