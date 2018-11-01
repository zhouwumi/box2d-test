#ifndef __IMPLUSE_CONTACT_LISTENER1_H__
#define __IMPLUSE_CONTACT_LISTENER1_H__

#include "L2Box2dWorld.h"
#include "test_case/ImpluseTestCase.h"

class ImpluseContactListener : public b2ContactListener
{
public:
	ImpluseContactListener(ImpluseTestCase* mainCase);
	virtual ~ImpluseContactListener();

	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

public:
	bool isContacted;
	ImpluseTestCase* _mainCase;
	b2Fixture* beHitBoxFixture;
};

#endif