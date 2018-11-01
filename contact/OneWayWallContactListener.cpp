#include "OneWayWallContactListener.h"



OneWayWallContactListener::OneWayWallContactListener(OneWayWallTestCase* mainCase):
	_mainCase(mainCase),
	isOnGround(true),
	isOnPlatform(false)
{
}


OneWayWallContactListener::~OneWayWallContactListener()
{
}

void OneWayWallContactListener::BeginContact(b2Contact* contact)
{
	checkPlayerOnGroundState(contact, true);
	checkPlayerOnPlatformState(contact, true);
}

void OneWayWallContactListener::EndContact(b2Contact* contact)
{
	checkPlayerOnGroundState(contact, false);
	checkPlayerOnPlatformState(contact, false);
}

void OneWayWallContactListener::checkPlayerOnGroundState(b2Contact* contact, bool isBeginContact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	b2Body* playerCircleBody = _mainCase->getCirclePlayerBody();
	b2Body* groundBody = _mainCase->getGroundBody();

	if (groundBody != bodyA && groundBody != bodyB)
	{
		return;
	}

	b2WorldManifold worldMainFold;
	contact->GetWorldManifold(&worldMainFold);
	b2Vec2 firstContactPoint = worldMainFold.points[0];
	b2Vec2 localInGroundBody = groundBody->GetLocalPoint(firstContactPoint);
	if (isBeginContact){
		if (localInGroundBody.y > 0)
		{
			isOnGround = true;
		}
	}else {
		isOnGround = false;
	}
}

void OneWayWallContactListener::checkPlayerOnPlatformState(b2Contact* contact, bool isBeginContact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	b2Body* playerCircleBody = _mainCase->getCirclePlayerBody();
	b2Body* platformBody = _mainCase->getPlatformBody();

	if (platformBody != bodyA && platformBody != bodyB)
	{
		return;
	}

	b2WorldManifold worldMainFold;
	contact->GetWorldManifold(&worldMainFold);
	b2Vec2 firstContactPoint = worldMainFold.points[0];
	b2Vec2 localInPlatformBody = platformBody->GetLocalPoint(firstContactPoint);

	if (isBeginContact) {
		if (localInPlatformBody.y > 0) {
			isOnPlatform = true;
		} else {
			isOnPlatform = false;
			contact->SetEnabled(false);
		}
	} else {
		isOnPlatform = false;
		contact->SetEnabled(true);
	}
}