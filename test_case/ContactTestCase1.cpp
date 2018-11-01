#include "ContactTestCase1.h"
#include "Box2dHelper.h"

#include "contact/MyContactListener1.h"
ContactTestCase1::ContactTestCase1(L2Box2dWorld* l2World) :
	_L2World(l2World)
{
	l2World->world->SetGravity(b2Vec2(0, 0));
	_contactListener = new MyContactListener1(this);
	l2World->world->SetContactListener(_contactListener);
}


ContactTestCase1::~ContactTestCase1()
{
}


void ContactTestCase1::test()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 globalCenterPosition((visibleOrigin.x + visibleSize.width / 2) / Box2dHelper::getPTMRatio(), (visibleOrigin.y + visibleSize.height / 2) / Box2dHelper::getPTMRatio());
	float halfPlanetR = 0.3f;
	_centerBody = Box2dHelper::createStaticCircleBody(_L2World->world, globalCenterPosition, halfPlanetR, b2_dynamicBody);

	float halfSensorR = 5.0f;
	b2Body* sensorBody = Box2dHelper::createStaticCircleBody(_L2World->world, globalCenterPosition, halfSensorR, b2_dynamicBody);

	sensorBody->GetFixtureList()->SetSensor(true);
	_sensorBody = sensorBody;

	b2Vec2 birdPosition((visibleOrigin.x + visibleSize.width / 4) / Box2dHelper::getPTMRatio(), globalCenterPosition.y - halfSensorR + 1.0f);
	b2Body* birdBody = Box2dHelper::createStaticBoxBody(_L2World->world, birdPosition, 0.25f, 0.25f, b2_dynamicBody);
	birdBody->SetLinearVelocity(b2Vec2(6.0f, 0.0f));
	_birdBody = birdBody;
}

void ContactTestCase1::step()
{
	if (_contactListener->isBirdInSensor)
	{
		b2Vec2 centerPosition = _centerBody->GetPosition();
		b2Vec2 birdPosition = _birdBody->GetPosition();
		b2Vec2 force = centerPosition - birdPosition;
		force.Normalize();
		force *= (_birdBody->GetMass() * 10);
		_birdBody->ApplyForce(force, birdPosition, true);
		_birdBody->SetLinearDamping(0.2f);
	}
}