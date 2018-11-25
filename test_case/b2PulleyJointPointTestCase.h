#ifndef __B2_PULLEY_JOINT_TEST_CASE_H__
#define __B2_PULLEY_JOINT_TEST_CASE_H__

#include "BaseTestCase.h"
#include "L2Box2dWorld.h"

class b2PulleyJointPointTestCase : public BaseTestCase
{
public:
	b2PulleyJointPointTestCase(L2Box2dWorld* l2World);
	virtual ~b2PulleyJointPointTestCase();

	virtual void onTouchBegin(cocos2d::Vec2 position) override;
	virtual void onTouchEnd(cocos2d::Vec2 position) override;

	virtual void step() override;
	virtual void test() override;
private:
	void _createJoint();
private:
	L2Box2dWorld * _L2World;
	b2Body* _bodyA;
	b2Body* _bodyB;
	b2PulleyJoint* _pulleyJoint;
};

#endif

