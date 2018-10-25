#include "L2Box2dWorld.h"
#include "Box2dHelper.h"

#define PTM_RATIO 32

L2Box2dWorld::L2Box2dWorld(b2Vec2 gravity)
{
	world = Box2dHelper::createWorld();
	_debugDraw = Box2dHelper::createBox2dDebugDraw();
	world->SetDebugDraw(_debugDraw);

	emptyBody = world->CreateBody(&emptyBodyDef);
}


L2Box2dWorld::~L2Box2dWorld()
{
	CC_SAFE_DELETE(_debugDraw);
	CC_SAFE_DELETE(world);
}

//这个可以将刚体固定在某个地方
void L2Box2dWorld::fixBodyAt(b2Body* body, float px, float py, float force)
{
	b2Vec2 fixedPoint(px, py);
	b2RevoluteJointDef revoluteJoinDef;

	revoluteJoinDef.Initialize(emptyBody, body, fixedPoint);
	world->CreateJoint(&revoluteJoinDef);
}