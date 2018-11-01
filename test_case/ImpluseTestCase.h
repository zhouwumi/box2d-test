#ifndef  __IMPLUSE_TEST_CASE_H__
#define __IMPLUSE_TEST_CASE_H__

#include "BaseTestCase.h"
#include "L2Box2dWorld.h"
#include "cocos2d.h"

class ImpluseContactListener;

class ImpluseTestCase: public BaseTestCase
{
public:
	ImpluseTestCase(L2Box2dWorld* l2World);
	virtual ~ImpluseTestCase();

	virtual void test() override;
	virtual void step() override;
	virtual void onTouchEnd(cocos2d::Vec2 position);

	inline b2Body* getBoxBody() { return _boxBody; }
	inline b2Body* getBirdBody() { return _birdBody; }
private:
	ImpluseContactListener* impluseContactListener;
	L2Box2dWorld * _L2World;
	b2Body* _birdBody;
	b2Body* _boxBody;
	bool _isreset;
	b2Vec2 _initBirdPosition;
};


#endif // ! 