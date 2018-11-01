#include "MyContactListener1.h"

MyContactListener1::MyContactListener1(ContactTestCase1* main) :
	_mainCase(main),
	isBirdInSensor(false)
{

}

MyContactListener1::~MyContactListener1()
{
}

void MyContactListener1::BeginContact(b2Contact* contact)
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

void MyContactListener1::EndContact(b2Contact* contact)
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

void MyContactListener1::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	cocos2d::log("PreSolve");
}

void MyContactListener1::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	cocos2d::log("PostSolve");
}