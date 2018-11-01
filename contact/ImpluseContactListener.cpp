#include "ImpluseContactListener.h"



ImpluseContactListener::ImpluseContactListener(ImpluseTestCase* mainCase):
	isContacted(false),
	_mainCase(mainCase),
	beHitBoxFixture(nullptr)
{

}


ImpluseContactListener::~ImpluseContactListener()
{

}

void ImpluseContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	b2Body* boxBody = _mainCase->getBoxBody();
	b2Body* birdBody = _mainCase->getBirdBody();

	if (boxBody == bodyA && birdBody == bodyB || boxBody == bodyB && birdBody == bodyA)
	{
		isContacted = true;
		if (boxBody == bodyB)
		{
			beHitBoxFixture = contact->GetFixtureB();
		}
		else {
			beHitBoxFixture = contact->GetFixtureA();
		}
	}
}
