#include "b2MouseJointTestCase.h"
#include "Box2dHelper.h"


b2MouseJointTestCase::b2MouseJointTestCase(L2Box2dWorld* l2World):
	_L2World(l2World),
	_mouseJoint(nullptr),
	_dragBody(nullptr)
{
}


b2MouseJointTestCase::~b2MouseJointTestCase()
{
}

void b2MouseJointTestCase::test()
{
	_L2World->world->SetGravity(b2Vec2(0, 0));
}

void b2MouseJointTestCase::onTouchBegin(cocos2d::Vec2 position)
{
	b2Vec2 mousePoint(position.x / Box2dHelper::getPTMRatio(), position.y / Box2dHelper::getPTMRatio());
	if (!_dragBody) 
	{
		float halfR = 0.5f;
		_dragBody = Box2dHelper::createStaticCircleBody(_L2World->world, mousePoint, halfR, b2_dynamicBody);
	}
	_createMouseJoint(mousePoint);
	_mouseJoint->SetTarget(mousePoint);
}

void b2MouseJointTestCase::onTouchMoved(cocos2d::Vec2 position)
{
	b2Vec2 mousePoint(position.x / Box2dHelper::getPTMRatio(), position.y / Box2dHelper::getPTMRatio());
	_mouseJoint->SetTarget(mousePoint);
}

void b2MouseJointTestCase::onTouchEnd(cocos2d::Vec2 position)
{
	if (_mouseJoint)
	{
		_L2World->world->DestroyJoint(_mouseJoint);
		_mouseJoint = nullptr;
		_L2World->world->DestroyBody(_dragBody);
		_dragBody = nullptr;
	}
}

void b2MouseJointTestCase::_createMouseJoint(b2Vec2 position)
{
	b2MouseJointDef mouseJointDef;
	mouseJointDef.bodyA = _L2World->emptyBody;
	mouseJointDef.bodyB = _dragBody;
	mouseJointDef.collideConnected = false;
	mouseJointDef.target = position;
	mouseJointDef.maxForce = _dragBody->GetMass() * 10;
	mouseJointDef.dampingRatio = 1.0f;
//	mouseJointDef.frequencyHz = 1.0f;
	b2MouseJoint* mouseJoint = (b2MouseJoint*)_L2World->world->CreateJoint(&mouseJointDef);
	_mouseJoint = mouseJoint;
}