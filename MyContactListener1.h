class ContactTestCase1;
#ifndef __MY_CONTACT_LISTENER1_H__
#define __MY_CONTACT_LISTENER1_H__

#include "L2Box2dWorld.h"
#include "test_case/ContactTestCase1.h"

class MyContactListener1 : public b2ContactListener
{
public:
	MyContactListener1(ContactTestCase1* main) :
		_mainCase(main),
		isBirdInSensor(false)
	{
	};

	virtual ~MyContactListener1() {}

	/// Called when two fixtures begin to touch.
	virtual void BeginContact(b2Contact* contact)
	{
		b2Body* birdBody = _mainCase->getBirdBody();
		b2Body* sensorBody = _mainCase->getSensorBody();
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();
		if (bodyA == birdBody && bodyB == sensorBody) {
			isBirdInSensor = true;
		}
		else if (bodyB == birdBody && bodyA == sensorBody) {
			isBirdInSensor = true;
		}

		cocos2d::log("BeginContact");
	}

	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact)
	{
		b2Body* birdBody = _mainCase->getBirdBody();
		b2Body* sensorBody = _mainCase->getSensorBody();
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();
		if (bodyA == birdBody && bodyB == sensorBody) {
			isBirdInSensor = false;
		}
		else if (bodyB == birdBody && bodyA == sensorBody) {
			isBirdInSensor = false;
		}
		cocos2d::log("EndContact");
	}

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		cocos2d::log("PreSolve");
	}

	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
		cocos2d::log("PostSolve");
	}
private:
	ContactTestCase1 * _mainCase;
public:
	bool isBirdInSensor;
};

#endif