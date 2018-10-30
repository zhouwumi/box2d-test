#include "b2RevoluteJointTestCase.h"
#include "Box2dHelper.h"

/**
��ʵ�ֵĹ����У����ִ���������С��������ͨ�����ʹ�������˶���
ԭ���ǣ���һ��ʼ�����ĸ����ܶ�Ϊ0������Ϊÿ�����嶼��һ�����ܶȵ����Ե�b2FixtureDef�ͽ�������ˡ�
Ĭ�ϵ�b2FixtureDef�뿴��Box2dHelper.getFixtureDef

����Ϊ��ʹ��С���˶�������Ҫ����ǰ�֣������������֣���Ħ���������Ħ��������Ϊ0��ͬ�������˶���
motorSpeed��ת�٣�ת��Խ��С���˶���Խ�졣

������һ�����ʣ����ٵ����С�����ٶȻ�Խ��Խ�죿��������
�Ժ����Ķ�Դ���ʱ�������
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
		_revoluteJointA->SetMotorSpeed(-M_PI * 3);  //˳ʱ�룬�����˶�
	}
	else {
		_revoluteJointA->SetMotorSpeed(M_PI * 3); //��ʱ�룬�����˶�
	}	
}

void b2RevoluteJointTestCase::onTouchEnd(cocos2d::Vec2 position)
{
	_isTouching = false;
	//����������ת��Ϊ0����ʾɲ����С������ֹͣ��
	_revoluteJointA->EnableMotor(true);
	_revoluteJointA->SetMotorSpeed(0);

	//����ر�����ʾֹͣ�ƶ���С��������˶�
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