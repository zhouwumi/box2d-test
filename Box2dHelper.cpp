#include "Box2dHelper.h"
#include "cocos2d.h"

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
	flags += b2Draw::e_shapeBit; //显示刚体的形状
	flags += b2Draw::e_centerOfMassBit;  //显示刚体的重心
	flags += b2Draw::e_jointBit; //显示关节
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

b2Body* Box2dHelper::createStaticBoxBody(b2World* world, b2Vec2 position, float halfWidth, float halfHeight)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	b2Body* staticBody = world->CreateBody(&bodyDef);

	b2PolygonShape staticBox;
	staticBox.SetAsBox(halfWidth, halfHeight);//These are mid points for our 1m box

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	staticBody->CreateFixture(&fixtureDef);
	return staticBody;
}

b2Body* Box2dHelper::createStaticCircleBody(b2World* world, b2Vec2 position, float halfR)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	b2Body* staticBody = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = halfR;
	//circleShape.m_p.x = 0.0f / PTM_RATIO;
	//circleShape.m_p.y = 300.0f / PTM_RATIO;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	staticBody->CreateFixture(&fixtureDef);
	return staticBody;
}

b2Body* Box2dHelper::createStaticPolygonBody(b2World* world, b2Vec2 position, std::vector<b2Vec2> releativePoints)
{
	assert(releativePoints.size() > 0);
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = position;

	b2Body* staticBody = world->CreateBody(&bodyDef);
	b2PolygonShape polygonShape;
	b2Vec2* pPoints = &releativePoints[0];
	{
		float degree = 30.f;
		float angle = degree / 180 * M_PI;
		//SetAsBox(hx, hy, center, angle)：设置矩形的半宽，半高，矩形中心点，旋转角度。
		//polygonShape.SetAsBox(1.0f, 2.0f, b2Vec2(4.0f, 4.0f), angle);
	}
	{
		//SetAsBox(hx, hy)：直接设置矩形的半宽和半高。
		//polygonShape.SetAsBox(1.0f, 2.0f);
	}
	{
		//Set方法：设置多边形的所有点，点的数量。
		polygonShape.Set(pPoints, releativePoints.size()); //这里的点的坐标是本地坐标系下的。以position为参考的。
	}

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	staticBody->CreateFixture(&fixtureDef);
	return staticBody;
}

//线段shape，会和其他形状的刚体参与碰撞。不会和线段形状的刚体碰撞。
b2Body* Box2dHelper::createStaticEdgeBody(b2World* world, b2Vec2 startPoint, b2Vec2 endPoint)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	b2Body* staticBody = world->CreateBody(&bodyDef);

	b2EdgeShape edgeShape;
	edgeShape.Set(startPoint, endPoint);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &edgeShape;
	staticBody->CreateFixture(&fixtureDef);
	return staticBody;
}

b2Body* Box2dHelper::createStaticChainBody(b2World* world, b2Vec2 position, std::vector<b2Vec2> releativePoints)
{
	assert(releativePoints.size() > 0);
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = position;

	b2Body* staticBody = world->CreateBody(&bodyDef);
	b2ChainShape chainShape;
	b2Vec2* pPoints = &releativePoints[0];
	//CreateChain：顶点不会闭合
	//chainShape.CreateChain(pPoints, releativePoints.size());
	//CreateLoop：会形成封闭线条,第一个和最后一个会连接起来
	chainShape.CreateLoop(pPoints, releativePoints.size());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &chainShape;
	staticBody->CreateFixture(&fixtureDef);
	return staticBody;
}

//运动学物体，不参与碰撞。但是会运动，给一个速度，会运动起来。
b2Body* Box2dHelper::createKinematicBoxBody(b2World* world, b2Vec2 position, float halfWidth, float halfHeight)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.linearVelocity = b2Vec2(0.0f, -1.0f);
	b2Body* staticBody = world->CreateBody(&bodyDef);

	b2PolygonShape staticBox;
	staticBox.SetAsBox(halfWidth, halfHeight);//These are mid points for our 1m box

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	staticBody->CreateFixture(&fixtureDef);
	return staticBody;
}

b2Body* Box2dHelper::createDefaultDynamicBoxBody(b2World* world, b2Vec2 position, float halfWidth, float halfHeight)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	

	{
		//bodyDef.angle = (rand() % 180 - 90) / 180.0f * M_PI;  //随机角度
		//bodyDef.angularVelocity = 2;  //角速度，围绕刚体中心旋转
		//bodyDef.angularDamping = 0.1;  //角速度的阻尼系数，0-1之间，数值越大，角速度下降的越慢
	}

	{
		//int maxVelocityX = 360;
		//int maxVelocityY = 360;
		//float velocityX = (rand() % maxVelocityX - maxVelocityX / 2) / (float)PTM_RATIO;
		//float velocityY = (rand() % maxVelocityY - maxVelocityY / 2) / (float)PTM_RATIO;
		//bodyDef.linearVelocity = b2Vec2(velocityX, velocityY);  //线速度
		//bodyDef.linearDamping = 0.9; //线性速度的阻尼系数，0-1之间，数值越大，速度下降越慢
		//bodyDef.fixedRotation = true; //碰撞不改变角度
	}
	

	b2Body *body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(halfWidth, halfHeight);//These are mid points for our 1m box

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.3f;
	//fixtureDef.isSensor = true; //不参与碰撞
	body->CreateFixture(&fixtureDef);

	return body;
}


/*
b2BodyDef:
type
position
angle
angularVelocity
angularDamping
linearVelocity
linearDamping
fixedRotation

b2FixtureDef:
shape
density
friction
restitution:弹性系数，0-1之间，数值越大，弹性越大。
isSensor: 是否作为感应使用。如果为true,不会进行碰撞模拟，不会影响任何速度。
*/

/* 圆形b2CircleShape
刚体的本地坐标系统的原点就是其当前的坐标位置。
m_p：圆形的质心的本地坐标。如果设置为（0, 300），将看到圆形出现在圆位置的正上方300像素位置。
*/