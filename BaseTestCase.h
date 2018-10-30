#ifndef __BASE_TEST_CASE_H__
#define __BASE_TEST_CASE_H__

#include "Box2D/Box2D.h"
#include "cocos2d.h"


class BaseTestCase
{
public:
	BaseTestCase();
	virtual ~BaseTestCase();
	virtual void test();

	virtual void onTouchBegin(cocos2d::Vec2 position);
	virtual void onTouchEnd(cocos2d::Vec2 position);

	virtual void step();

};
#endif

