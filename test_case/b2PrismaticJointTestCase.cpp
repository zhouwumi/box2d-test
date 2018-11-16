#include "b2PrismaticJointTestCase.h"
#include "Box2dHelper.h"

float PTM_RATIO = Box2dHelper::getPTMRatio();


b2PrismaticJointTestCase::b2PrismaticJointTestCase(L2Box2dWorld* l2World):
	_L2World(l2World)
{

}

b2PrismaticJointTestCase::~b2PrismaticJointTestCase()
{
	
}

void b2PrismaticJointTestCase::test()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);

	b2Vec2 pos;
	pos.x = globalCenterPoint.x;
	pos.y = 5;
	//pos.y = globalCenterPoint.y - 5;

	float _halfR = 0.5f;
	_moveBody = Box2dHelper::createStaticCircleBody(_L2World->world, pos, _halfR, b2_dynamicBody);

	this->_createJoint();
}

void b2PrismaticJointTestCase::step()
{

}


void b2PrismaticJointTestCase::onTouchBegin(cocos2d::Vec2 position)
{
	b2Vec2 currPoint = _moveBody->GetWorldPoint(b2Vec2(0, 0));
	if (position.x > currPoint.x * Box2dHelper::getPTMRatio()) {
		_moveBody->ApplyLinearImpulse(b2Vec2(_moveBody->GetMass() * 15, _moveBody->GetMass() * -15), b2Vec2_zero, true);
	}
	else {
		_moveBody->ApplyLinearImpulse(b2Vec2(_moveBody->GetMass() * -15, _moveBody->GetMass() * 15), b2Vec2_zero, true);
	}
}


void b2PrismaticJointTestCase::onTouchEnd(cocos2d::Vec2 position)
{

}

//测试关节的马达属性
void b2PrismaticJointTestCase::_createJoint()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	b2Body* emptyBody = Box2dHelper::createStaticBoxBody(_L2World->world, globalCenterPoint, visibleSize.width / PTM_RATIO, 0.05f, b2_staticBody);
	/*
	b2BodyDef emptyBodyDef;
	emptyBodyDef.position = globalCenterPoint;
	b2Body* emptyBody = _L2World->world->CreateBody(&emptyBodyDef);*/
	b2PrismaticJointDef jointDef;
	jointDef.bodyA = emptyBody;
	jointDef.bodyB = _moveBody;
		
	jointDef.enableMotor = true;
	jointDef.maxMotorForce = 8 * _moveBody->GetMass(), 0;
	jointDef.motorSpeed = 8;

	//jointDef.enableLimit = true;
	//jointDef.lowerTranslation = -10;
	//jointDef.upperTranslation = 5;

	b2Vec2 axis(1, 0);
	axis.Normalize();
	jointDef.localAxisA = axis;

	_prismaticJoint = (b2PrismaticJoint*)_L2World->world->CreateJoint(&jointDef);
}

/*
//测试关节的限制，本地锚点，相对角度属性
void b2PrismaticJointTestCase::_createJoint()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	b2Body* emptyBody = Box2dHelper::createStaticBoxBody(_L2World->world, globalCenterPoint, visibleSize.width / PTM_RATIO, 0.05f, b2_staticBody);
	
	//b2BodyDef emptyBodyDef;
	//emptyBodyDef.position = globalCenterPoint;
	//b2Body* emptyBody = _L2World->world->CreateBody(&emptyBodyDef);
	b2PrismaticJointDef jointDef;
	jointDef.bodyA = emptyBody;
	jointDef.bodyB = _moveBody;
	jointDef.localAnchorA = b2Vec2(0, -3);
	jointDef.localAnchorB = b2Vec2(0, 3);

	jointDef.enableLimit = true;
	jointDef.lowerTranslation = -10;
	jointDef.upperTranslation = 5;

	jointDef.referenceAngle = M_PI_2 / 2 * -1;

	b2Vec2 axis(0.5, -0.5);
	axis.Normalize();
	jointDef.localAxisA = axis;
	jointDef.enableMotor = true;
	_prismaticJoint = (b2PrismaticJoint*)_L2World->world->CreateJoint(&jointDef);
}*/
/* 
bodyB运行的轨道是：bodyA的localAnchorA 所在全局位置的axis方向
*/