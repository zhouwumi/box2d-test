#ifndef __B2_MOUSE_JOINT_TEST_CASE_H__
#define __B2_MOUSE_JOINT_TEST_CASE_H__

#include "BaseTestCase.h"
#include "L2Box2dWorld.h"

class b2MouseJointTestCase : public BaseTestCase
{
public:
	b2MouseJointTestCase(L2Box2dWorld* l2World);
	virtual ~b2MouseJointTestCase();

	virtual void test() override;

	virtual void onTouchBegin(cocos2d::Vec2 position) override;
	virtual void onTouchMoved(cocos2d::Vec2 position) override;
	virtual void onTouchEnd(cocos2d::Vec2 position) override;

private:
	void _createMouseJoint(b2Vec2 position);
private:
	L2Box2dWorld * _L2World;
	b2Body* _dragBody;
	b2MouseJoint* _mouseJoint;
};

#endif