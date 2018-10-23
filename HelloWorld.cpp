#include "HelloWorld.h"
#include "Box2dTestSprite.h"


using namespace cocos2d;
Scene* HelloWorld::scene()
{
	//创建一个场景
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();
	//创建一个HelloWorld的层
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();
	//将层放到场景中去
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{//  调用父类初始化函数
 //////////////////////////////
 // 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto box2dTestSprite = Box2dTestSprite::create();
	this->addChild(box2dTestSprite);

	/*

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	//将一个相片创建菜单项 并调用方法menuCloseCallback
	MenuItemImage *pCloseItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(HelloWorld::menuCloseCallback));
	//开关相片的位置
	pCloseItem->setPosition(ccp(Director::sharedDirector()->getWinSize().width - 20, 20));

	//将一个已经创建好的菜单项加入菜单中 并声称一个菜单对象的实例
	// create menu, it's an autorelease object
	Menu* pMenu = Menu::create(pCloseItem, NULL);
	// 设置菜单的位置
	pMenu->setPosition(cocos2d::Point::ZERO);
	// 将菜单加入当前的layer里  并设置z轴为1
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label
	//创建一个文本对象 并设置字体和大小
	LabelTTF* pLabel = LabelTTF::create("Hello World", "Thonburi", 34);

	//    获取当前设备的尺寸
	// ask director the window size
	Size size = Director::sharedDirector()->getWinSize();
	//设置文本的位置
	// position the label on the center of the screen
	pLabel->setPosition(ccp(size.width / 2, size.height - 20));

	// add the label as a child to this layer
	//    将文本放大layer层中  和menu的设置轴是一样的  就是同一层
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	//    设置一个精灵  并且放入图片
	Sprite* pSprite = Sprite::create("HelloWorld.png");
	//精灵的位置
	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(size.width / 2, size.height / 2));
	//把精灵放到layer中去   但是在底层
	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	*/
	return true;
}

void HelloWorld::menuCloseCallback(cocos2d::Object* pSender)
{
	Director::sharedDirector()->end();
}