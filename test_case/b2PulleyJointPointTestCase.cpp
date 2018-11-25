#include "b2PulleyJointPointTestCase.h"
#include "Box2dHelper.h"


b2PulleyJointPointTestCase::b2PulleyJointPointTestCase(L2Box2dWorld* l2World):
	_L2World(l2World)
{
}


b2PulleyJointPointTestCase::~b2PulleyJointPointTestCase()
{
}

void b2PulleyJointPointTestCase::onTouchBegin(cocos2d::Vec2 position)
{
	_bodyA->ApplyLinearImpulse(b2Vec2(0, 10.0f * this->_bodyA->GetMass()), _bodyA->GetWorldCenter(), true);
}

void b2PulleyJointPointTestCase::onTouchEnd(cocos2d::Vec2 position)
{

}

void b2PulleyJointPointTestCase::step()
{
	int cur_len_A = this->_pulleyJoint->GetCurrentLengthA();
	int cur_len_B = this->_pulleyJoint->GetCurrentLengthB();

	int temp = 1;
}

void b2PulleyJointPointTestCase::test()
{
	b2Vec2 globalCenter = Box2dHelper::GetWorldCenterPoint();

	b2Vec2 bodyAPosition(globalCenter.x - 6, globalCenter.y - 3);
	_bodyA = Box2dHelper::createStaticCircleBody(_L2World->world, bodyAPosition, 1.0f, b2_dynamicBody);
	this->_bodyA->GetFixtureList()->SetDensity(10.0f);
	this->_bodyA->ResetMassData();
	b2Vec2 bodyBPosition(globalCenter.x + 6, globalCenter.y - 6);
	_bodyB = Box2dHelper::createStaticCircleBody(_L2World->world, bodyBPosition, 0.5f, b2_dynamicBody);
	this->_bodyB->GetFixtureList()->SetDensity(5.0f);
	this->_bodyB->ResetMassData();
	this->_createJoint();
}

void b2PulleyJointPointTestCase::_createJoint()
{
	b2Vec2 globalCenter = Box2dHelper::GetWorldCenterPoint();
	b2PulleyJointDef jointDef;

	jointDef.Initialize(_bodyA, _bodyB, b2Vec2(globalCenter.x - 6, globalCenter.y), b2Vec2(globalCenter.x + 6, globalCenter.y), b2Vec2(_bodyA->GetPosition().x, _bodyA->GetPosition().y + 1.0f), b2Vec2(_bodyB->GetPosition().x, _bodyB->GetPosition().y + 0.5f),1.0f);
	this->_pulleyJoint = (b2PulleyJoint*)_L2World->world->CreateJoint(&jointDef);
	int cur_len_A = this->_pulleyJoint->GetCurrentLengthA();
	int cur_len_B = this->_pulleyJoint->GetCurrentLengthB();

	int max_len_A = this->_pulleyJoint->GetLengthA();
	int max_len_B = this->_pulleyJoint->GetLengthB();
	int temp = 1;
}