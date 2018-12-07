//
//  grdn_physics.c
//  r4
//
//  Created by Andrew Macfarlane on 1/2/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "grdn_physics.h"

#include <grdn/grdn.h>

#ifdef G4_ENABLE_CHIPMUNK

#include "contrib/chipmunk/chipmunk.h"
#include "contrib/chipmunk/chipmunk_private.h"
#include "contrib/chipmunk/chipmunk_unsafe.h"
//#include <chipmunk/cpSpace.h>
#define DENSITY (1.0 / 10000.0)

/*
 #include "ChipmunkDebugDraw.h"

static void
DrawCircle(cpVect p, cpFloat a, cpFloat r, cpSpaceDebugColor outline,
cpSpaceDebugColor fill, cpDataPointer data) {ChipmunkDebugDrawCircle(p, a, r,
outline, fill);}

static void
DrawSegment(cpVect a, cpVect b, cpSpaceDebugColor color, cpDataPointer data)
{ChipmunkDebugDrawSegment(a, b, color);}

static void
DrawFatSegment(cpVect a, cpVect b, cpFloat r, cpSpaceDebugColor outline,
cpSpaceDebugColor fill, cpDataPointer data) {ChipmunkDebugDrawFatSegment(a, b,
r, outline, fill);}

static void
DrawPolygon(int count, const cpVect *verts, cpFloat r, cpSpaceDebugColor
outline, cpSpaceDebugColor fill, cpDataPointer data)
{ChipmunkDebugDrawPolygon(count, verts, r, outline, fill);}

static void
DrawDot(cpFloat size, cpVect pos, cpSpaceDebugColor color, cpDataPointer data)
{ChipmunkDebugDrawDot(size, pos, color);}


static cpSpaceDebugColor
ColorForShape(cpShape *shape, cpDataPointer data)
{
	if(cpShapeGetSensor(shape)){
		return LAColor(1.0f, 0.1f);
	} else {
		cpBody *body = cpShapeGetBody(shape);

		if(cpBodyIsSleeping(body)){
			return LAColor(0.2f, 1.0f);
		} else if(body->sleeping.idleTime >
shape->space->sleepTimeThreshold) { return LAColor(0.66f, 1.0f); } else {
			uint32_t val = (uint32_t)shape->hashid;

			// scramble the bits up using Robert Jenkins' 32 bit
integer hash function val = (val+0x7ed55d16) + (val<<12); val = (val^0xc761c23c)
^ (val>>19); val = (val+0x165667b1) + (val<<5); val = (val+0xd3a2646c) ^
(val<<9); val = (val+0xfd7046c5) + (val<<3); val = (val^0xb55a4f09) ^ (val>>16);

			//GLfloat r = (GLfloat)((val>>0) & 0xFF);
			//GLfloat g = (GLfloat)((val>>8) & 0xFF);
			//GLfloat b = (GLfloat)((val>>16) & 0xFF);

			//GLfloat max = (GLfloat)cpfmax(cpfmax(r, g), b);
			//GLfloat min = (GLfloat)cpfmin(cpfmin(r, g), b);
			//GLfloat intensity = (cpBodyGetType(body) ==
CP_BODY_TYPE_STATIC ? 0.15f : 0.75f);

			// Saturate and scale the color
			//if(min == max){
			//	return RGBAColor(intensity, 0.0f, 0.0f, 1.0f);
			//} else {
				//GLfloat coef = (GLfloat)intensity/(max - min);
				return RGBAColor(
								 .5,
								 .2,
								 .7,
								 //(r -
min)*coef,
								//(g -
min)*coef,
								 //(b -
min)*coef, 1.0f
								 );
			//}
		}
	}
}
*/

cpSpace*	space;
static cpShape* ground   = NULL;
static cpBody*  ballBody = NULL;
static cpShape* ballShape;
static cpFloat  timestep = 1;

PhysicsObject* ball = NULL;

PhysicsObject* grdn_physics_object_create()
{
	PhysicsObject* obj = malloc(sizeof(PhysicsObject));
	return obj;
}

PhysicsObject* grdn_physics_object_createfromline(WLine* line)
{

	PhysicsObject* obj       = grdn_physics_object_create();
	const int      NUM_VERTS = (int)line->num;

	printf("creating a physics object: %d\n", NUM_VERTS);

	cpVect verts[NUM_VERTS];

	for (int i = 0; i < NUM_VERTS; i++)
	{
		WPoint* p = line->data[i];
		verts[i]  = cpv(p->x, p->y);
	}
	cpFloat tolerance = 2.0;
	cpBody* body      = cpSpaceAddBody(space, cpBodyNew(0.0f, 0.0f));

	int     hullCount = cpConvexHull(NUM_VERTS, verts, verts, NULL, tolerance);
	cpVect  centroid  = cpCentroidForPoly(hullCount, verts);
	cpFloat mass      = cpAreaForPoly(hullCount, verts, 0.0f) * DENSITY;

	cpBodySetMass(body, mass);
	cpBodySetMoment(body, cpMomentForPoly(mass, hullCount, verts,
					      cpvneg(centroid), 0.0f));
	cpBodySetPosition(body, cpBodyLocalToWorld(body, centroid));

	// cpFloat mass = 2.0f;

	cpTransform offset;
	cpVect      vec;
	// offset.x = 0;
	// offset.y = 0;

	// cpMomentForPoly(mass, NUM_VERTS, verts, vec, 50.0f)));
	// cpBodySetPosition(body, cpv(0,0));
	/// cpShape* shape = cpSpaceAddShape(space, cpPolyShapeNew(body,
	/// NUM_VERTS, verts, offset, 0.0f));
	cpShape* shape =
	    cpSpaceAddShape(space, cpPolyShapeNew(body, NUM_VERTS, verts,
						  cpTransformIdentity, 0.0));
	cpPolyShapeSetVerts(shape, hullCount, verts,
			    cpTransformTranslate(cpvneg(centroid)));

	// cpShapeSetElasticity(shape, .2f);
	// cpShapeSetFriction(shape, 0.5f);
	// cpShapeSetFilter(shape, cpShapeFilterNew(CP_NO_GROUP, 1, 1));

	// test_hull = grdn_physics_object_create();

	obj->body  = body;
	obj->shape = shape;
	obj->geo   = line;
	return obj;
}
void grdn_physics_object_destroy(PhysicsObject* obj)
{
	free(obj);
}

void grdn_physics_object_set_position(PhysicsObject* obj, float x, float y)
{
	cpBodySetPosition(obj->body, cpv(x, y));
	obj->position.x = x;
	obj->position.y = y;
}

void grdn_physics_object_set_velocity(PhysicsObject* obj, float x, float y)
{
	cpBodySetVelocity(obj->body, cpv(x, y));
	obj->velocity.x = x;
	obj->velocity.y = y;
}

void grdn_physics_init()
{
	timestep       = 1.0 / 60.;
	space	  = cpSpaceNew();
	cpVect gravity = cpv(0, -2);

	// Create an empty space.
	// cpSpace *space = cpSpaceNew();
	cpSpaceSetGravity(space, gravity);

	// Add a static line segment shape for the ground.
	// We'll make it slightly tilted so the ball will roll off.
	// We attach it to space->staticBody to tell Chipmunk it shouldn't be
	// movable.
	ground =
	    cpSegmentShapeNew(space->staticBody, cpv(-512, 0), cpv(512, 0), 0);
	cpShapeSetFriction(ground, 1);
	cpSpaceAddShape(space, ground);

	// Now let's make a ball that falls onto the line and rolls off.
	// First we need to make a cpBody to hold the physical properties of the
	// object. These include the mass, position, velocity, angle, etc. of
	// the object. Then we attach collision shapes to the cpBody to give it
	// a size and shape.
	ball = grdn_physics_object_create();

	cpFloat radius = 5;
	cpFloat mass   = 1;

	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);

	// The cpSpaceAdd*() functions return the thing that you are adding.
	// It's convenient to create and add an object in one line.
	ballBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
	cpBodySetPosition(ballBody, cpv(2, 15));

	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	ballShape =
	    cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
	cpShapeSetFriction(ballShape, 0.7);

	ball->body  = ballBody;
	ball->shape = ballShape;
	// Now that it's all set up, we simulate all the objects in the space by
	// stepping forward through time in small increments called steps.
	// It is *highly* recommended to use a fixed size time step.
}

void grdn_physics_deinit()
{

	// Clean up our objects and exit!
	cpShapeFree(ballShape);
	cpBodyFree(ballBody);
	cpShapeFree(ground);
	cpSpaceFree(space);

	// return 0;
}

void grdn_physics_object_update(PhysicsObject* obj)
{
	cpVect pos      = cpBodyGetPosition(obj->body);
	cpVect vel      = cpBodyGetVelocity(obj->body);
	obj->position.x = pos.x;
	obj->position.y = pos.y;
	obj->velocity.x = vel.x;
	obj->velocity.y = vel.y;
}

void grdn_physics_tick()
{
	grdn_physics_object_update(ball);
	// grdn_physics_update_object(obj);
	// for(cpFloat time = 0; time < 2; time += timeStep){
	// cpVect pos = cpv(0,0);
	// cpVect vel = cpv(0,0);
	cpVect pos = cpBodyGetPosition(ballBody);
	cpVect vel = cpBodyGetVelocity(ballBody);

	ball->position.x = pos.x;
	ball->position.y = pos.y;
	ball->velocity.x = vel.x;
	ball->velocity.y = vel.y;
	/*
	printf(
  "Time is. ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
   pos.x, pos.y, vel.x, vel.y
		   );
*/
	//}

	cpSpaceStep(space, timestep);
}

void grdn_physics_render_object(PhysicsObject* obj)
{
	cpBody*  body = obj->body;
	cpShape* sh   = obj->shape;

	/*
	cpSpaceDebugDrawOptions drawOptions = {
		DrawCircle,
		DrawSegment,
		DrawFatSegment,
		DrawPolygon,
		DrawDot,

		(cpSpaceDebugDrawFlags)(CP_SPACE_DEBUG_DRAW_SHAPES |
	CP_SPACE_DEBUG_DRAW_CONSTRAINTS | CP_SPACE_DEBUG_DRAW_COLLISION_POINTS),

		{200.0f/255.0f, 210.0f/255.0f, 230.0f/255.0f, 1.0f},
		ColorForShape,
		{0.0f, 0.75f, 0.0f, 1.0f},
		{1.0f, 0.0f, 0.0f, 1.0f},
		NULL,
	};
	cpSpaceDebugDraw(space, &drawOptions);
	*/
}

#endif
