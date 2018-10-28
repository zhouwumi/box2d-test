#ifndef __BOX2D_TEST_SPRITE_H__
#define __BOX2D_TEST_SPRITE_H__

#include "cocos2d.h"
#include "L2Box2dWorld.h"

#include "BaseTestCase.h"

class Box2dTestSprite : public cocos2d::Node
{
public:
	Box2dTestSprite();
	virtual ~Box2dTestSprite();

	virtual bool init() override;
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	void update(float dt) override;

	CREATE_FUNC(Box2dTestSprite);

private:
	void initPhysics();
	void onDraw();
	
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	//测试圆形shape
	void _testCircleShape();
	//测试多边形shape
	void _testPolygonShape();
	//测试线段shape
	void _testEdgeShape();
	//测试线条shape
	void _testChainShape();

	void _testCreateFixture();
	
	//测试旋转关节
	void _testRevoluteJoint();
	void _testRevoluteJoint2();
	//跷跷板
	void _testQiaoQiaoBanRevoluteJoint();
	void _testXiaoCheRevoluteJoint();

	//测试Apply系列函数
	void _testApplyFunction();

	void _testMassData();

private:
	L2Box2dWorld _L2World;
	cocos2d::Mat4 _modelViewMV;
	cocos2d::CustomCommand _customCommand;
	b2Body* _currentBody;
	b2RevoluteJoint* _currentRevoluteJoint;

private:
	BaseTestCase* testCase;
};

#endif