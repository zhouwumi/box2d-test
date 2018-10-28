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
	static b2Body* createStaticBoxBody(b2World* world, b2Vec2 position, float halfWidth, float halfHeight, b2BodyType type = b2_staticBody);
	static b2Body* createKinematicBoxBody(b2World* world, b2Vec2 position, float halfWidth, float halfHeight);
	static b2Body* createDefaultDynamicBoxBody(b2World* world, b2Vec2 position, float halfWidth, float halfHeight);

	static b2Body* createStaticCircleBody(b2World* world, b2Vec2 position, float halfR, b2BodyType type = b2_staticBody);
	static b2Body* createStaticPolygonBody(b2World* world, b2Vec2 position, std::vector<b2Vec2> releativePoints);
	static b2Body* createStaticEdgeBody(b2World* world, b2Vec2 startPoint, b2Vec2 endPoint);
	static b2Body* createStaticChainBody(b2World* world, b2Vec2 position, std::vector<b2Vec2> releativePoints);

	//¥¥Ω®Õ÷‘≤
	static b2PolygonShape createSemicircle(float width, float height);
	static float getPTMRatio();

private:
	
	static b2FixtureDef& getFixtureDef();
};

