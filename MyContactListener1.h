class ContactTestCase1;
#ifndef __MY_CONTACT_LISTENER1_H__
#define __MY_CONTACT_LISTENER1_H__

#include "L2Box2dWorld.h"
#include "test_case/ContactTestCase1.h"

class MyContactListener1 : public b2ContactListener
{
public:
	MyContactListener1(ContactTestCase1* main);

	virtual ~MyContactListener1();

	/// Called when two fixtures begin to touch.
	virtual void BeginContact(b2Contact* contact);

	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
private:
	ContactTestCase1 * _mainCase;
public:
	bool isBirdInSensor;
};

#endif