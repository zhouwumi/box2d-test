#ifndef __APPLY_FUNCTION_TEST_CASE_H__
#define __APPLY_FUNCTION_TEST_CASE_H__

#include "BaseTestCase.h"
#include "L2Box2dWorld.h"

class ApplyFunctionTestCase : public BaseTestCase
{
public:
	ApplyFunctionTestCase(L2Box2dWorld* l2World);
	virtual ~ApplyFunctionTestCase();

	virtual void test() override;
	virtual void onTouchBegin(cocos2d::Vec2 position) override;
	virtual void onTouchEnd(cocos2d::Vec2 position) override;
	virtual void step() override;

private:
	void testForce();
	void testImpluse();
	void testTroque();
	void testReverseGravity();
	void limitAngularVelocity();

private:
	L2Box2dWorld* _L2World;
	b2Body* _circleBody;
	bool _isTouching;
	b2Vec2 _force;
	b2Vec2 _impluse;
	bool _isTouchLeft;
	bool _isTouchRight;
	b2Body* _boxBody;
};

#endif
