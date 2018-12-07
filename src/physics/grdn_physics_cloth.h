//
//  grdn_physics_cloth.h
//  grdn
//
//  Created by vs on 3/23/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef grdn_physics_cloth_h
#define grdn_physics_cloth_h

//port of https://codepen.io/dissimulate/pen/KrAwx?editors=0010

typedef struct GCConstraint
{
	struct GCPoint* a;
	struct GCPoint* b;
	double		length;
} GCConstraint;

typedef struct GCPoint
{
	double		      x;
	double		      y;
	double		      px;
	double		      py;
	double		      vx;
	double		      vy;
	double*		      pin_x;
	double*		      pin_y;
	int		      ncons;
	struct GCConstraint** constraints;
} GCPoint;

typedef struct GCCloth
{
	GCPoint**	  points;
	unsigned long long num;
} GCCloth;

GCPoint* grdn_physics_cloth_point_create(double x, double y);
void     grdn_physics_cloth_point_attach(GCPoint* a, GCPoint* b);
void     grdn_physics_cloth_point_pin(GCPoint* p, double x, double y);
void     grdn_physics_cloth_point_add_force(GCPoint* p, double x, double y);
GCCloth* grdn_physics_cloth_create(unsigned int w, unsigned int h);
void     grdn_physics_cloth_destroy(GCCloth* cloth);
void     grdn_physics_cloth_update(GCCloth* cloth);
void     grdn_physics_cloth_draw(GCCloth* cloth);
#endif /* grdn_physics_cloth_h */
