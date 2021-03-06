#ifndef __B2_DISTANCE_JOINT_TEST_CASE_H__
#define __B2_DISTANCE_JOINT_TEST_CASE_H__

#include "BaseTestCase.h"
#include "L2Box2dWorld.h"

class b2DistanceJointTestCase : public BaseTestCase
{
public:
	b2DistanceJointTestCase(L2Box2dWorld* l2World);
	virtual ~b2DistanceJointTestCase();

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
	b2DistanceJoint* _distanceJoint;
};

#endif

