#include "L2Box2dWorld.h"
#include "Box2dHelper.h"

L2Box2dWorld::L2Box2dWorld(b2Vec2 gravity)
{
	world = Box2dHelper::createWorld();
	_debugDraw = Box2dHelper::createBox2dDebugDraw();
	world->SetDebugDraw(_debugDraw);
}


L2Box2dWorld::~L2Box2dWorld()
{
	CC_SAFE_DELETE(_debugDraw);
	CC_SAFE_DELETE(world);
}
