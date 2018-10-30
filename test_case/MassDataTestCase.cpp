#include "MassDataTestCase.h"
#include "Box2dHelper.h"
#include "cocos2d.h"


MassDataTestCase::MassDataTestCase(L2Box2dWorld* l2World):
	_L2World(l2World)
{
}


MassDataTestCase::~MassDataTestCase()
{
}


void MassDataTestCase::createBody()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	
	float width = 100;
	float height = 50;
	b2Vec2 semCirclePosition((visibleOrigin.x + visibleSize.width / 2) / Box2dHelper::getPTMRatio(), (visibleOrigin.y + height) / Box2dHelper::getPTMRatio());
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = semCirclePosition;

	b2Body* testBody = _L2World->world->CreateBody(&bodyDef);

	b2PolygonShape semiCircleShape = Box2dHelper::createSemicircle(width, height);
	
	std::vector<b2Vec2> boxVertices;
	b2Vec2 left_buttom(-width / 2 / Box2dHelper::getPTMRatio(), 0);
	b2Vec2 right_buttom(width / 2 / Box2dHelper::getPTMRatio(), 0);
	b2Vec2 top(0, 200.0f / Box2dHelper::getPTMRatio());
	boxVertices.emplace_back(left_buttom);
	boxVertices.emplace_back(right_buttom);
	boxVertices.emplace_back(top);

	b2PolygonShape boxShape;
	boxShape.Set(&boxVertices[0], boxVertices.size());


	testBody->CreateFixture(&boxShape, 1.0f);
	testBody->CreateFixture(&semiCircleShape, 1.0f);

	//注定设置重心
	b2MassData massData;
	testBody->GetMassData(&massData);

	massData.center.Set(0, -(height / 2) / Box2dHelper::getPTMRatio());
	massData.I = massData.mass * massData.center.LengthSquared() + 20;
	testBody->SetMassData(&massData);
	
	_testBody = testBody;
}

void MassDataTestCase::test()
{
	createBody();
}

void MassDataTestCase::onTouchBegin(cocos2d::Vec2 position)
{
	b2Vec2 impulse(_testBody->GetMass() * 2.0f, 0);
	if (position.x / Box2dHelper::getPTMRatio() < _testBody->GetWorldCenter().x) {
		impulse.x *= -1;
	}
	_testBody->ApplyLinearImpulse(impulse, _testBody->GetWorldPoint(b2Vec2(0, 20.0f / Box2dHelper::getPTMRatio())), true);
}

void MassDataTestCase::onTouchEnd(cocos2d::Vec2 position)
{

}

void MassDataTestCase::step()
{

}