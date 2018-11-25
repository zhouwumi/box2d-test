#include "b2WeldJointTestCase.h"
#include "Box2dHelper.h"
#include<cmath>

b2WeldJointTestCase::b2WeldJointTestCase(L2Box2dWorld* l2World):
	_L2World(l2World),
	_weldJoint(nullptr)
{
	_L2World->world->SetGravity(b2Vec2(0, -0.1f));
}


b2WeldJointTestCase::~b2WeldJointTestCase()
{
}

void b2WeldJointTestCase::onTouchBegin(cocos2d::Vec2 position)
{
	if (this->_weldJoint) {
		_L2World->world->DestroyJoint(this->_weldJoint);
		this->_weldJoint = nullptr;

		this->_bodyA->ApplyLinearImpulse(b2Vec2(-5 * this->_bodyA->GetMass(),  5 * this->_bodyA->GetMass()), b2Vec2_zero, true);
		this->_bodyB->ApplyLinearImpulse(b2Vec2(5 * this->_bodyB->GetMass(), 5 * this->_bodyB->GetMass()), b2Vec2_zero, true);
	} else {
		this->_createJoint();
	}
}


void b2WeldJointTestCase::onTouchEnd(cocos2d::Vec2 position)
{
}

void b2WeldJointTestCase::step()
{

}

void b2WeldJointTestCase::test()
{
	b2Vec2 globalCenter = Box2dHelper::GetWorldCenterPoint();
	int random_x_1 = rand() % 8;
	int random_y_1 = rand() % 8;
	this->_bodyA = Box2dHelper::createStaticCircleBody(_L2World->world, b2Vec2(globalCenter.x + random_x_1, globalCenter.y + random_y_1), 1.0f, b2_dynamicBody);
	
	int random_x_2 = rand() % 8;
	int random_y_2 = rand() % 8;
	this->_bodyB = Box2dHelper::createStaticBoxBody(_L2World->world, b2Vec2(globalCenter.x + random_x_2, globalCenter.y + random_y_2), 1.0f, 1.0f,  b2_dynamicBody);
	
	Box2dHelper::createStaticBoxBody(_L2World->world, globalCenter, 20.0f, 0.1f);
}

void b2WeldJointTestCase::_createJoint()
{
	b2WeldJointDef weldJointDef;
	weldJointDef.bodyA = this->_bodyA;
	weldJointDef.bodyB = this->_bodyB;
	weldJointDef.localAnchorA = b2Vec2(0, -6);
	weldJointDef.localAnchorB = b2Vec2(0, 3.0f);
	
	this->_weldJoint = (b2WeldJoint*)_L2World->world->CreateJoint(&weldJointDef);
}
