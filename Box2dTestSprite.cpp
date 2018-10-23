#include "Box2dTestSprite.h"
#include "Box2dHelper.h"

#define PTM_RATIO 32

using namespace cocos2d;

Box2dTestSprite::Box2dTestSprite()
{

}

Box2dTestSprite::~Box2dTestSprite()
{
}

bool Box2dTestSprite::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->initPhysics();
	this->scheduleUpdate();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Box2dTestSprite::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Box2dTestSprite::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
	return true;
}

void Box2dTestSprite::initPhysics()
{
	_L2World.world->SetGravity(b2Vec2(0, -10.0f));
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 leftTop(visibleOrigin.x / PTM_RATIO, (visibleOrigin.y + visibleSize.height) / PTM_RATIO);
	b2Vec2 rightDown((visibleOrigin.x + visibleSize.width) / PTM_RATIO, visibleOrigin.y);
	Box2dHelper::createEdgeBody(_L2World.world, leftTop, rightDown);
	
	//b2Vec2 pos((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	//Box2dHelper::createStaticBoxBody(_L2World.world, pos, 5.0f, 0.5f);

	b2Vec2 pos((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 6) / PTM_RATIO);
	Box2dHelper::createStaticBoxBody(_L2World.world, pos, 5.0f, 0.1f);
	
	b2Vec2 circlePos((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	Box2dHelper::createStaticCircleBody(_L2World.world, circlePos, 1.0f);
	
}

bool Box2dTestSprite::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

void Box2dTestSprite::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	cocos2d::Vec2 pos = touch->getLocation();
	Box2dHelper::createDefaultDynamicBoxBody(_L2World.world, b2Vec2(pos.x / PTM_RATIO, pos.y / PTM_RATIO), 0.5f, 0.5f);
}

void Box2dTestSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	//
	// IMPORTANT:
	// This is only for debug purposes
	// It is recommend to disable it
	//
	Node::draw(renderer, transform, flags);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when setting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	_modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(Box2dTestSprite::onDraw, this);
	renderer->addCommand(&_customCommand);

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void Box2dTestSprite::onDraw()
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when setting matrix stack");

	auto oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
	_L2World.world->DrawDebugData();
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
}

void Box2dTestSprite::update(float dt)
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/

	int velocityIterations = 8;
	int positionIterations = 1;

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	_L2World.world->Step(dt, velocityIterations, positionIterations);
}
