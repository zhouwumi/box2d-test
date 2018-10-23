#pragma once

#include "Box2D/Box2D.h"
#include "GLES-Render.h"

class Box2dHelper
{
public:
	Box2dHelper();
	~Box2dHelper();

	static b2World* createWorld(b2Vec2 gravity = b2Vec2(0.0f, -10.0f));
	static GLESDebugDraw* createBox2dDebugDraw();

	static b2Body* createEdgeBody(b2World* world, b2Vec2 leftTop, b2Vec2 rightDown);
};

