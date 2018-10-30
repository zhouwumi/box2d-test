#ifndef __MASS_DATA_TEST_CASE_H__
#define __MASS_DATA_TEST_CASE_H__

#include "BaseTestCase.h"
#include "L2Box2dWorld.h"


class MassDataTestCase : public BaseTestCase
{
public:
	MassDataTestCase(L2Box2dWorld* l2World);
	virtual ~MassDataTestCase();

	virtual void test() override;
	virtual void onTouchBegin(cocos2d::Vec2 position) override;
	virtual void onTouchEnd(cocos2d::Vec2 position) override;
	virtual void step() override;

private:
	void createBody();
private:
	L2Box2dWorld* _L2World;

	b2Body* _testBody;
};

#endif
