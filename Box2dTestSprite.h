#ifndef __BOX2D_TEST_SPRITE_H__
#define __BOX2D_TEST_SPRITE_H__

#include "cocos2d.h"
#include "L2Box2dWorld.h"

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

private:
	L2Box2dWorld _L2World;
	cocos2d::Mat4 _modelViewMV;
	cocos2d::CustomCommand _customCommand;
};

#endif