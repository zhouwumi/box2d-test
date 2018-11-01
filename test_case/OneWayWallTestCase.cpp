#include "OneWayWallTestCase.h"
#include "Box2dHelper.h"
#include "contact/OneWayWallContactListener.h"

OneWayWallTestCase::OneWayWallTestCase(L2Box2dWorld* l2World):
	_L2World(l2World),
	_circlePlayerBody(nullptr),
	_isOnGroup(true)
{
}


OneWayWallTestCase::~OneWayWallTestCase()
{
}

void OneWayWallTestCase::test()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 platformPos((visibleOrigin.x + visibleSize.width / 2) / Box2dHelper::getPTMRatio(), (visibleOrigin.y) / Box2dHelper::getPTMRatio() + 6.0f);
	float halfPlatformWidth = 4.0f;
	float halfPlatformHeiht = 0.2f;
	b2Body* platformBoxBody = Box2dHelper::createStaticBoxBody(_L2World->world, platformPos, halfPlatformWidth, halfPlatformHeiht);
	_platformBody = platformBoxBody;

	float halfGroupWidth = visibleSize.width / 2 / Box2dHelper::getPTMRatio() - 0.01f;
	float halfGroupHeight = 0.2f;
	b2Vec2 groundPos((visibleOrigin.x + visibleSize.width / 2) / Box2dHelper::getPTMRatio(), (visibleOrigin.y) / Box2dHelper::getPTMRatio() + halfGroupHeight);
	b2Body* groundBoxBody = Box2dHelper::createStaticBoxBody(_L2World->world, groundPos, halfGroupWidth, halfGroupHeight);
	_groundBody = groundBoxBody;

	float halfPlayerCircleWidth = 0.5f;
	b2Vec2 circlePlayerPos((visibleOrigin.x + visibleSize.width / 2) / Box2dHelper::getPTMRatio(), (visibleOrigin.y) / Box2dHelper::getPTMRatio() + halfPlayerCircleWidth + halfGroupHeight * 2);
	b2Body* circlePlayerBody = Box2dHelper::createStaticCircleBody(_L2World->world, circlePlayerPos, halfPlayerCircleWidth, b2_dynamicBody);
	_circlePlayerBody = circlePlayerBody;

	oneWayWallContactListener = new OneWayWallContactListener(this);
	_L2World->world->SetContactListener(oneWayWallContactListener);

}

void OneWayWallTestCase::step()
{

}

void OneWayWallTestCase::onTouchEnd(cocos2d::Vec2 position)
{

}

void OneWayWallTestCase::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) {
		if (oneWayWallContactListener->isOnGround || oneWayWallContactListener->isOnPlatform)
		{
			_circlePlayerBody->ApplyLinearImpulse(b2Vec2(0.0f, 30.0f), _circlePlayerBody->GetPosition(), true);
		}
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		_circlePlayerBody->ApplyLinearImpulse(b2Vec2(20.0f, 0.0f), _circlePlayerBody->GetPosition(), true);
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		_circlePlayerBody->ApplyLinearImpulse(b2Vec2(-20.0f, 0.0f), _circlePlayerBody->GetPosition(), true);
	}
	
}