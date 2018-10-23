#include "Box2dHelper.h"

#define PTM_RATIO 32

Box2dHelper::Box2dHelper()
{
}


Box2dHelper::~Box2dHelper()
{
}


b2World* Box2dHelper::createWorld(b2Vec2 gravity)
{
	b2World* world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);

	return world;
}

GLESDebugDraw* Box2dHelper::createBox2dDebugDraw()
{
	GLESDebugDraw* debugDraw = new GLESDebugDraw(32);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	debugDraw->SetFlags(flags);
	return debugDraw;
}

b2Body* Box2dHelper::createEdgeBody(b2World* world, b2Vec2 leftTop, b2Vec2 rightDown)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	//down
	b2EdgeShape groundBox;
	groundBox.Set(b2Vec2(leftTop.x, rightDown.y), rightDown);
	groundBody->CreateFixture(&groundBox, 0);

	// top
	groundBox.Set(leftTop, b2Vec2(rightDown.x, leftTop.y));
	groundBody->CreateFixture(&groundBox, 0);

	// left
	groundBox.Set(leftTop, b2Vec2(leftTop.x, rightDown.y));
	groundBody->CreateFixture(&groundBox, 0);

	// right
	groundBox.Set(b2Vec2(rightDown.x, leftTop.y), rightDown);
	groundBody->CreateFixture(&groundBox, 0);

	return groundBody;
}