#include "ImpluseTestCase.h"
#include "contact/ImpluseContactListener.h"
#include "Box2dHelper.h"

/*
这个例子没达到书中的效果。
主要是Split方法没有。
现在的表现方式只是：小鸟碰到了哪个fixture，哪个fixture就从body中移除。
*/

int box_count = 10;

ImpluseTestCase::ImpluseTestCase(L2Box2dWorld* l2World):
	_L2World(l2World),
	_birdBody(nullptr),
	_isreset(true),
	_initBirdPosition(b2Vec2_zero)
{
}


ImpluseTestCase::~ImpluseTestCase()
{
}

void ImpluseTestCase::test()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 globalCenterPosition((visibleOrigin.x + visibleSize.width / 2) / Box2dHelper::getPTMRatio(), (visibleOrigin.y + visibleSize.height / 2) / Box2dHelper::getPTMRatio());
	float halfBoxWidth = 0.5f;
	//b2Vec2 boxPos((visibleOrigin.x + visibleSize.width) / Box2dHelper::getPTMRatio() - 3.0f, halfBoxWidth);
	b2Vec2 boxPos((visibleOrigin.x + visibleSize.width) / Box2dHelper::getPTMRatio() - 3.0f, 0);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = boxPos;
	b2Body* boxBody = _L2World->world->CreateBody(&bodyDef);
	b2PolygonShape shape;
	b2FixtureDef fixtureDef = Box2dHelper::getFixtureDef();

	for (int idx = 0; idx < box_count; idx++)
	{
		shape.SetAsBox(halfBoxWidth, halfBoxWidth, b2Vec2(0, idx * halfBoxWidth * 2 + halfBoxWidth), 0.0f);
		fixtureDef.shape = &shape;
		boxBody->CreateFixture(&fixtureDef);
	}
	_boxBody = boxBody;

	b2Vec2 birdPosition((visibleOrigin.x + visibleSize.width / 4) / Box2dHelper::getPTMRatio(), box_count * halfBoxWidth);
	_initBirdPosition = birdPosition;
	b2Body* birdBody = Box2dHelper::createStaticCircleBody(_L2World->world, birdPosition, 0.25f, b2_staticBody);
	_birdBody = birdBody;
	_birdBody->SetBullet(true);

	impluseContactListener = new ImpluseContactListener(this);
	_L2World->world->SetContactListener(impluseContactListener);
}

void ImpluseTestCase::step()
{
	if (impluseContactListener->isContacted)
	{
		b2Fixture* fixture = _boxBody->GetFixtureList();
		while (fixture)
		{
			b2Fixture* curr_fixture = fixture;
			fixture = fixture->GetNext();
			if (curr_fixture == impluseContactListener->beHitBoxFixture)
			{
				_boxBody->DestroyFixture(curr_fixture);
				break;
			}
		}
		impluseContactListener->isContacted = false;
		impluseContactListener->beHitBoxFixture = nullptr;
	}
}

void ImpluseTestCase::onTouchEnd(cocos2d::Vec2 position)
{
	if (_isreset)
	{
		_isreset = false;
		_birdBody->SetType(b2_dynamicBody);
		b2Vec2 direction(position.x / Box2dHelper::getPTMRatio() - _birdBody->GetPosition().x, position.y / Box2dHelper::getPTMRatio() - _birdBody->GetPosition().y);
		direction.Normalize();
		direction *= 50.0f;
		_birdBody->SetLinearVelocity(direction);
	}
	else
	{
		_isreset = true;
		const_cast<b2Transform&>(_birdBody->GetTransform()).Set(_initBirdPosition, 0);
		_birdBody->SetType(b2_staticBody);
	}
}