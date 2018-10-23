#include "HelloWorld.h"
#include "Box2dTestSprite.h"


using namespace cocos2d;
Scene* HelloWorld::scene()
{
	//����һ������
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();
	//����һ��HelloWorld�Ĳ�
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();
	//����ŵ�������ȥ
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{//  ���ø����ʼ������
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
	//��һ����Ƭ�����˵��� �����÷���menuCloseCallback
	MenuItemImage *pCloseItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(HelloWorld::menuCloseCallback));
	//������Ƭ��λ��
	pCloseItem->setPosition(ccp(Director::sharedDirector()->getWinSize().width - 20, 20));

	//��һ���Ѿ������õĲ˵������˵��� ������һ���˵������ʵ��
	// create menu, it's an autorelease object
	Menu* pMenu = Menu::create(pCloseItem, NULL);
	// ���ò˵���λ��
	pMenu->setPosition(cocos2d::Point::ZERO);
	// ���˵����뵱ǰ��layer��  ������z��Ϊ1
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label
	//����һ���ı����� ����������ʹ�С
	LabelTTF* pLabel = LabelTTF::create("Hello World", "Thonburi", 34);

	//    ��ȡ��ǰ�豸�ĳߴ�
	// ask director the window size
	Size size = Director::sharedDirector()->getWinSize();
	//�����ı���λ��
	// position the label on the center of the screen
	pLabel->setPosition(ccp(size.width / 2, size.height - 20));

	// add the label as a child to this layer
	//    ���ı��Ŵ�layer����  ��menu����������һ����  ����ͬһ��
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	//    ����һ������  ���ҷ���ͼƬ
	Sprite* pSprite = Sprite::create("HelloWorld.png");
	//�����λ��
	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(size.width / 2, size.height / 2));
	//�Ѿ���ŵ�layer��ȥ   �����ڵײ�
	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	*/
	return true;
}

void HelloWorld::menuCloseCallback(cocos2d::Object* pSender)
{
	Director::sharedDirector()->end();
}