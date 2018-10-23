
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
	//初始化函数
	virtual bool init();

	// there's no 'id' in cpp, so we recommend to return the class instance pointer
	//静态创建函数
	static cocos2d::Scene* scene();

	// a selector callback
	//menu 菜单的一个回调函数  用于响应CCMenuItemImage
	void menuCloseCallback(cocos2d::Object* pSender);

	// preprocessor macro for "static create()" constructor ( node() deprecated )
	//备注1
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__