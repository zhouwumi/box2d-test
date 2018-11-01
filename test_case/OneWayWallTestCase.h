#ifndef __ONE_WAY_WALL_TEST_CASE_H__
#define __ONE_WAY_WALL_TEST_CASE_H__

#include "BaseTestCase.h"
#include "L2Box2dWorld.h"

class OneWayWallContactListener;

class OneWayWallTestCase : public BaseTestCase
{
public:
	OneWayWallTestCase(L2Box2dWorld* l2World);
	virtual ~OneWayWallTestCase();

	virtual void test() override;
	virtual void step() override;
	virtual void onTouchEnd(cocos2d::Vec2 position);

	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);

	inline b2Body* getCirclePlayerBody() { return _circlePlayerBody; }
	inline b2Body* getGroundBody() { return _groundBody; }
	inline b2Body* getPlatformBody() { return _platformBody; }

private:
	OneWayWallContactListener * oneWayWallContactListener;
	L2Box2dWorld * _L2World;
	b2Body* _circlePlayerBody;
	b2Body* _groundBody;
	b2Body* _platformBody;
	bool _isOnGroup;
};

#endif

