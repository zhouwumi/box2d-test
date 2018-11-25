#include "b2DistanceJointTestCase.h"
#include "Box2dHelper.h"


b2DistanceJointTestCase::b2DistanceJointTestCase(L2Box2dWorld* l2World):
	_L2World(l2World)
{
	l2World->world->SetGravity(b2Vec2(0, -0.8f));
}


b2DistanceJointTestCase::~b2DistanceJointTestCase()
{
}

void b2DistanceJointTestCase::onTouchBegin(cocos2d::Vec2 position)
{
}


void b2DistanceJointTestCase::onTouchEnd(cocos2d::Vec2 position)
{

}

void b2DistanceJointTestCase::step()
{

}

void b2DistanceJointTestCase::test()
{
	this->_createJoint();
}

void b2DistanceJointTestCase::_createJoint()
{
	b2Vec2 globalCenter = Box2dHelper::GetWorldCenterPoint();
	b2Vec2 bodyA_pos = globalCenter;
	b2Vec2 bodyB_pos = globalCenter;

	bodyA_pos.y -= 5.0f;
	this->_bodyA = Box2dHelper::createStaticCircleBody(_L2World->world, bodyA_pos, 3.0f, b2_kinematicBody);
	bodyB_pos.y += 1.0f;
	this->_bodyB = Box2dHelper::createStaticBoxBody(_L2World->world, bodyB_pos, 5.0f, 0.2f, b2_dynamicBody);
	 
	b2DistanceJointDef distanceJointDef;
	distanceJointDef.bodyA = this->_bodyA;
	distanceJointDef.bodyB = this->_bodyB;
	distanceJointDef.localAnchorA = b2Vec2(-3, 0);
	distanceJointDef.localAnchorB = b2Vec2(0, 0);
	distanceJointDef.length = 6.5f;

	b2DistanceJoint* distanceJoint = (b2DistanceJoint*)_L2World->world->CreateJoint(&distanceJointDef);
	this->_distanceJoint = distanceJoint;
	
	this->_bodyA->SetAngularVelocity(-2);
	
	b2PrismaticJointDef prismaticJointDef;
	b2BodyDef emptyBodyDef;
	emptyBodyDef.position = globalCenter;

	prismaticJointDef.bodyA = _L2World->world->CreateBody(&emptyBodyDef);
	prismaticJointDef.bodyB = this->_bodyB;
	prismaticJointDef.localAnchorA = b2Vec2_zero;
	prismaticJointDef.localAnchorB = b2Vec2(0, 0);
	prismaticJointDef.localAxisA = b2Vec2(0, -1);
	_L2World->world->CreateJoint(&prismaticJointDef);
	
	//b2PrismaticJoint* prismaticJoint = 
	//Box2dHelper::createStaticBoxBody(_L2World->world, globalCenter, 0.5f, 0.5f);

}

//distance joint 的基础使用
/*
void b2DistanceJointTestCase::_createJoint()
{
	b2Vec2 globalCenter = Box2dHelper::GetWorldCenterPoint();
	b2Vec2 bodyA_pos = globalCenter;
	b2Vec2 bodyB_pos = globalCenter;
	bodyA_pos.x += 5.0f;
	//this->_bodyA = Box2dHelper::createStaticCircleBody(_L2World->world, bodyA_pos, 0.5f, b2_dynamicBody); 
	this->_bodyA = Box2dHelper::createStaticBoxBody(_L2World->world, bodyA_pos, 1.0f, 1.0f, b2_dynamicBody);
	bodyB_pos.x -= 5.0f;
	this->_bodyB = Box2dHelper::createStaticCircleBody(_L2World->world, bodyB_pos, 0.5f, b2_dynamicBody);

	b2DistanceJointDef distanceJointDef;
	distanceJointDef.bodyA = this->_bodyA;
	distanceJointDef.bodyB = this->_bodyB;
	distanceJointDef.localAnchorA = b2Vec2(-2, 0);
	distanceJointDef.localAnchorB = b2Vec2(2, 0);
	distanceJointDef.length = 5.0f;

	b2DistanceJoint* distanceJoint = (b2DistanceJoint*)_L2World->world->CreateJoint(&distanceJointDef);
	this->_distanceJoint = distanceJoint;
	
	//Box2dHelper::createStaticBoxBody(_L2World->world, globalCenter, 0.5f, 0.5f);

}*/