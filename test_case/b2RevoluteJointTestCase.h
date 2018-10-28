#ifndef __B2_REVOLUTE_JOINT_TEST_CASE_H__
#define __B2_REVOLUTE_JOINT_TEST_CASE_H__

#include "BaseTestCase.h"
#include "L2Box2dWorld.h"

class b2RevoluteJointTestCase: public BaseTestCase
{
public:
	b2RevoluteJointTestCase(L2Box2dWorld& l2World);
	~b2RevoluteJointTestCase();

	virtual void test() override;

	virtual void onTouchBegin(cocos2d::Vec2 position) override;
	virtual void onTouchEnd(cocos2d::Vec2 position) override;

	virtual void step() override;

private:
	L2Box2dWorld _L2World;
	b2Body* _carBody;
	b2Body* _circleBodyA;
	b2Body* _circleBodyB;

	b2RevoluteJoint* _revoluteJointA;
	b2RevoluteJoint* _revoluteJointB;

	bool _isTouching;
};

#endif
