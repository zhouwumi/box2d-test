#include "b2RevoluteJointTestCase.h"
#include "Box2dHelper.h"

/**
在实现的过程中，发现创建出来的小车并不会通过马达使得自身运动。
原因是：我一开始创建的刚体密度为0。后来为每个刚体都加一个有密度等属性的b2FixtureDef就解决问题了。
默认的b2FixtureDef请看：Box2dHelper.getFixtureDef

并且为了使得小车运动，还需要设置前轮（此例中是左轮）的摩檫力，如果摩擦力设置为0，同样不能运动。
motorSpeed：转速；转速越大，小车运动的越快。

还存在一个疑问：快速点击，小车的速度会越来越快？？？？？
以后来阅读源码的时候分析吧
*/
b2RevoluteJointTestCase::b2RevoluteJointTestCase(L2Box2dWorld* l2World):
	_L2World(l2World),
	_isTouching(false),
	_carBody(nullptr),
	_circleBodyA(nullptr),
	_circleBodyB(nullptr),
	_revoluteJointA(nullptr),
	_revoluteJointB(nullptr)
{
}


b2RevoluteJointTestCase::~b2RevoluteJointTestCase()
{
}


void b2RevoluteJointTestCase::test()
{
	float PTM_RATIO = Box2dHelper::getPTMRatio();
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	b2Vec2 buttomCenter((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, 0);


	float halfGroupHeight = 0.5f;
	b2Body* groundBody = Box2dHelper::createStaticBoxBody(_L2World->world, b2Vec2(buttomCenter.x, buttomCenter.y + halfGroupHeight), (float)visibleSize.width / 2 / PTM_RATIO - 0.1f, halfGroupHeight);
	groundBody->SetType(b2_dynamicBody);

	buttomCenter.y += halfGroupHeight * 2;
	float halfCircleWidth = 0.5f;
	float circleDistance = 2.0f;
	b2Vec2 leftCirclePos(buttomCenter.x - circleDistance, buttomCenter.y + halfCircleWidth);
	b2Vec2 rightCirclePos(buttomCenter.x + circleDistance, buttomCenter.y + halfCircleWidth);
	b2Body* circleBody1 = Box2dHelper::createStaticCircleBody(_L2World->world, leftCirclePos, halfCircleWidth, b2_dynamicBody);
	circleBody1->GetFixtureList()->SetFriction(100.0f);
	b2Body* circleBody2 = Box2dHelper::createStaticCircleBody(_L2World->world, rightCirclePos, halfCircleWidth, b2_dynamicBody);
	float halfBoxHeight = 0.2f;
	float halfBoxWidth = circleDistance + halfCircleWidth;
	b2Vec2 boxPos(buttomCenter.x, buttomCenter.y + halfCircleWidth * 2 + halfBoxHeight);
	b2Body* boxBody = Box2dHelper::createStaticBoxBody(_L2World->world, boxPos, halfBoxWidth, halfBoxHeight, b2_dynamicBody);

	b2Vec2 revolutePoint = circleBody1->GetPosition();
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 50.0f;
	revoluteJointDef.motorSpeed = M_PI / 6;
	revoluteJointDef.Initialize(boxBody, circleBody1, revolutePoint);
	_revoluteJointA = (b2RevoluteJoint*)_L2World->world->CreateJoint(&revoluteJointDef);

	b2RevoluteJointDef revoluteJointDef2;
	revoluteJointDef2.collideConnected = false;
	revoluteJointDef2.enableMotor = false;
	revolutePoint = circleBody2->GetPosition();
	revoluteJointDef2.Initialize(boxBody, circleBody2, revolutePoint);
	_revoluteJointB = (b2RevoluteJoint*)_L2World->world->CreateJoint(&revoluteJointDef2);

	_carBody = boxBody;
	_circleBodyA = circleBody1;
	_circleBodyB = circleBody2;

}

void b2RevoluteJointTestCase::onTouchBegin(cocos2d::Vec2 position)
{
	_isTouching = true;

	_revoluteJointA->EnableMotor(true);
	b2Vec2 currPoint = _circleBodyA->GetWorldPoint(b2Vec2(0, 0));
	if (position.x > currPoint.x * Box2dHelper::getPTMRatio()) {
		_revoluteJointA->SetMotorSpeed(-M_PI * 3);  //顺时针，向右运动
	}
	else {
		_revoluteJointA->SetMotorSpeed(M_PI * 3); //逆时针，向左运动
	}	
}

void b2RevoluteJointTestCase::onTouchEnd(cocos2d::Vec2 position)
{
	_isTouching = false;
	//开启马达，设置转速为0，表示刹车，小车马上停止。
	_revoluteJointA->EnableMotor(true);
	_revoluteJointA->SetMotorSpeed(0);

	//如果关闭马达，表示停止制动，小车随惯性运动
	//_revoluteJointA->EnableMotor(false);
}

void b2RevoluteJointTestCase::step()
{
	if (!_isTouching) {
		return;
	}
	//_revoluteJointA->EnableMotor(true);
	//_revoluteJointA->SetMotorSpeed(M_PI / 10.0f * 30.0f);

	//_circleBodyA->ApplyForce(b2Vec2(100.0f, 0.0f), _circleBodyA->GetWorldPoint(b2Vec2(-0.5f, 0.0f)), true);
}