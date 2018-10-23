#ifndef __L2_BOX2DWORLD_H__
#define __L2_BOX2DWORLD_H__

#include "Box2D/Box2D.h"
#include "GLES-Render.h"

class L2Box2dWorld
{
public:
	L2Box2dWorld(b2Vec2 gravity = b2Vec2(0.0f, -10.0f));
	~L2Box2dWorld();
public:
	b2World * world;
private:
	GLESDebugDraw *_debugDraw;
};

#endif

