#ifndef __ONE_WAY_WALL_CONTACT_LISTENER1_H__
#define __ONE_WAY_WALL_CONTACT_LISTENER1_H__

#include "L2Box2dWorld.h"
#include "test_case/OneWayWallTestCase.h"

class OneWayWallContactListener : public b2ContactListener
{
public:
	OneWayWallContactListener(OneWayWallTestCase* mainCase);
	virtual ~OneWayWallContactListener();
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

private:
	void checkPlayerOnGroundState(b2Contact* contact, bool isBeginContact);
	void checkPlayerOnPlatformState(b2Contact* contact, bool isBeginContact);
public:
	OneWayWallTestCase * _mainCase;
	bool isOnGround;
	bool isOnPlatform;
};

#endif
