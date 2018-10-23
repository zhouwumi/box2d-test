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

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	staticBody->CreateFixture(&fixtureDef);
	return staticBody;
}

//�˶�ѧ���壬��������ײ�����ǻ��˶�����һ���ٶȣ����˶�������
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
		//bodyDef.angle = (rand() % 180 - 90) / 180.0f * M_PI;  //����Ƕ�
		//bodyDef.angularVelocity = 2;  //���ٶȣ�Χ�Ƹ���������ת
		//bodyDef.angularDamping = 0.1;  //���ٶȵ�����ϵ����0-1֮�䣬��ֵԽ�󣬽��ٶ��½���Խ��
	}

	{
		//int maxVelocityX = 360;
		//int maxVelocityY = 360;
		//float velocityX = (rand() % maxVelocityX - maxVelocityX / 2) / (float)PTM_RATIO;
		//float velocityY = (rand() % maxVelocityY - maxVelocityY / 2) / (float)PTM_RATIO;
		//bodyDef.linearVelocity = b2Vec2(velocityX, velocityY);  //���ٶ�
		//bodyDef.linearDamping = 0.9; //�����ٶȵ�����ϵ����0-1֮�䣬��ֵԽ���ٶ��½�Խ��
		//bodyDef.fixedRotation = true; //��ײ���ı�Ƕ�
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
	//fixtureDef.isSensor = true; //��������ײ
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
restitution:����ϵ����0-1֮�䣬��ֵԽ�󣬵���Խ��
isSensor: �Ƿ���Ϊ��Ӧʹ�á����Ϊtrue,���������ײģ�⣬����Ӱ���κ��ٶȡ�
*/