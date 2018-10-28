#include "ApplyFunctionTestCase.h"
#include "Box2dHelper.h"
#include "cocos2d.h"
#include "Box2D/Common/b2Math.h"

ApplyFunctionTestCase::ApplyFunctionTestCase(L2Box2dWorld& l2World):
	_L2World(l2World),
	_circleBody(nullptr),
	_isTouching(false),
	_force(b2Vec2_zero),
	_impluse(b2Vec2_zero),
	_isTouchLeft(false),
	_isTouchRight(false),
	_boxBody(nullptr)
{
}


ApplyFunctionTestCase::~ApplyFunctionTestCase()
{
}
//测试 力
void ApplyFunctionTestCase::testForce()
{
	_circleBody = Box2dHelper::createStaticCircleBody(_L2World.world, b2Vec2_zero, 0.5f, b2_dynamicBody);
	_circleBody->SetLinearVelocity(b2Vec2(8.0f, 12.0f));
	_force.x = _circleBody->GetMass() * 8 * -1;
}
// 测试标量
void ApplyFunctionTestCase::testImpluse()
{
	_circleBody = Box2dHelper::createStaticCircleBody(_L2World.world, b2Vec2_zero, 0.5f, b2_dynamicBody);
	_circleBody->SetLinearVelocity(b2Vec2(8.0f, 12.0f));
	_impluse.x = _circleBody->GetMass() * 6;
	_impluse.y = _circleBody->GetMass() * 6;
}

//测试旋转力 troque
void ApplyFunctionTestCase::testTroque()
{
	
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / Box2dHelper::getPTMRatio(), (visibleOrigin.y) / Box2dHelper::getPTMRatio());
	float halfGroupHeight = 0.5f;
	b2Body* groupBody = Box2dHelper::createStaticBoxBody(_L2World.world, b2Vec2(globalCenterPoint.x, globalCenterPoint.y + halfGroupHeight), visibleSize.width / 2 - 0.1f, halfGroupHeight, b2_dynamicBody);
	groupBody->GetFixtureList()->SetFriction(1.0f);
	float halfBoxHeight = 0.5f;
	_boxBody = Box2dHelper::createStaticBoxBody(_L2World.world, b2Vec2(globalCenterPoint.x, globalCenterPoint.y + 2 * halfGroupHeight + halfBoxHeight), 0.5f, halfBoxHeight, b2_dynamicBody);
}

//测试反向重力
void ApplyFunctionTestCase::testReverseGravity()
{
	_circleBody = Box2dHelper::createStaticCircleBody(_L2World.world, b2Vec2_zero, 0.5f, b2_dynamicBody);
	_circleBody->SetLinearVelocity(b2Vec2(8.0f, 12.0f));
	
	b2Vec2 gravity = _L2World.world->GetGravity();
	b2Vec2 copyGravity(gravity.x, gravity.y * -1);
	_force = _circleBody->GetMass() * copyGravity;
}

void ApplyFunctionTestCase::test()
{
	testReverseGravity();
}

void ApplyFunctionTestCase::onTouchBegin(cocos2d::Vec2 position)
{
	_isTouching = true;

	//测试冲量,冲量是瞬间的，不需要持续。
//	_circleBody->ApplyLinearImpulse(_impluse, _circleBody->GetWorldCenter(), true);

	//测试旋转力torque
	/*
	if (_boxBody->GetWorldCenter().x * Box2dHelper::getPTMRatio() < position.x) {
		_isTouchRight = true;
	}else if (_boxBody->GetWorldCenter().x * Box2dHelper::getPTMRatio() > position.x) {
		_isTouchLeft = true;
	}*/

	/* 测试反重力，点击时加一个和运动方向一致的冲量。
	_impluse.Set(_circleBody->GetLinearVelocity().x, _circleBody->GetLinearVelocity().y);
	_impluse *= 1.2;
	_circleBody->ApplyLinearImpulse(_impluse, _circleBody->GetWorldCenter(), true);
	*/
}

void ApplyFunctionTestCase::onTouchEnd(cocos2d::Vec2 position)
{
	_isTouching = false;
	_isTouchLeft = false;
	_isTouchRight = false;
}

void ApplyFunctionTestCase::step()
{
	if (_isTouching) {
		//测试力，力需要保持持续。
	//	_circleBody->ApplyForceToCenter(_force, true);

		//测试旋转力 torque
		/*
		if (_isTouchLeft) {
			_boxBody->ApplyTorque(30 * M_PI * 30 / 180, true);
		}else if(_isTouchRight){
			_boxBody->ApplyTorque(-30 * M_PI * 30 / 180, true);
		}
		limitAngularVelocity();
		*/

		/* 测试反重力，这个力和重力大小一致，方向相反。
		_circleBody->ApplyForceToCenter(_force, true);
		*/
	}
}

void ApplyFunctionTestCase::limitAngularVelocity()
{
	float currentAngular = _boxBody->GetAngularVelocity();
	if (fabs(currentAngular) > 80) {
		float newAngular = fabs(currentAngular) / currentAngular * 80;
		_boxBody->SetAngularVelocity(newAngular);
	}
}