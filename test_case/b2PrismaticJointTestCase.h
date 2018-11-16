#ifndef __B2_PRISMATIC_JOINT_TEST_CASE_H__
#define __B2_PRISMATIC_JOINT_TEST_CASE_H__

#include "BaseTestCase.h"
#include "L2Box2dWorld.h"

class b2PrismaticJointTestCase : public BaseTestCase
{
public:
	b2PrismaticJointTestCase(L2Box2dWorld* l2World);
	~b2PrismaticJointTestCase();
	
	virtual void onTouchBegin(cocos2d::Vec2 position) override;
	virtual void onTouchEnd(cocos2d::Vec2 position) override;

	virtual void step() override;
	virtual void test() override;

private:
	void _createJoint();
private:
	L2Box2dWorld * _L2World;
	b2Body* _moveBody;
	b2PrismaticJoint* _prismaticJoint;
};

#endif

