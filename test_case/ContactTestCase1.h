#ifndef __CONTACT_TEST_CASE_H__
#define __CONTACT_TEST_CASE_H__

#include "BaseTestCase.h"
#include "L2Box2dWorld.h"
#include "cocos2d.h"

class MyContactListener1;

class ContactTestCase1 : public BaseTestCase
{
public:
	ContactTestCase1(L2Box2dWorld* l2World);
	virtual ~ContactTestCase1();

	virtual void test() override;
	virtual void step() override;

	inline b2Body* getBirdBody() { return _birdBody; };
	inline b2Body* getSensorBody() { return _sensorBody; };

private:
	L2Box2dWorld * _L2World;
	b2Body* _birdBody;
	b2Body* _sensorBody;
	b2Body* _centerBody;
	MyContactListener1* _contactListener;
};





#endif
