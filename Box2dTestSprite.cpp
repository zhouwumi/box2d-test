#include "Box2dTestSprite.h"

#define PTM_RATIO 32

using namespace cocos2d;

Box2dTestSprite::Box2dTestSprite():
	world(nullptr)
{

}

Box2dTestSprite::~Box2dTestSprite()
{
	CC_SAFE_DELETE(_debugDraw);
	CC_SAFE_DELETE(world);
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
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);

	_debugDraw = new GLESDebugDraw(32);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	_debugDraw->SetFlags(flags);

	world->SetDebugDraw(_debugDraw);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	b2EdgeShape groundBox;
	groundBox.Set(b2Vec2(visibleOrigin.x / PTM_RATIO, visibleOrigin.y / PTM_RATIO), b2Vec2((visibleOrigin.x + visibleSize.width) / PTM_RATIO, (visibleOrigin.y) / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	// top
	groundBox.Set(b2Vec2(visibleOrigin.x / PTM_RATIO, (visibleOrigin.y + visibleSize.height) / PTM_RATIO), b2Vec2((visibleOrigin.x + visibleSize.width) / PTM_RATIO, (visibleOrigin.y + visibleSize.height) / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	// left
	groundBox.Set(b2Vec2(visibleOrigin.x / PTM_RATIO, (visibleOrigin.y + visibleSize.height) / PTM_RATIO), b2Vec2(visibleOrigin.x / PTM_RATIO, (visibleOrigin.y) / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	// right
	groundBox.Set(b2Vec2((visibleOrigin.x + visibleSize.width) / PTM_RATIO, visibleOrigin.y / PTM_RATIO), b2Vec2((visibleOrigin.x + visibleSize.width) / PTM_RATIO, (visibleOrigin.y + visibleSize.height) / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);


	
}

bool Box2dTestSprite::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

void Box2dTestSprite::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	cocos2d::Vec2 pos = touch->getLocation();
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x / PTM_RATIO, pos.y / PTM_RATIO);

	b2Body *body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box

								  // Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.3f;
	body->CreateFixture(&fixtureDef);
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
	world->DrawDebugData();
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
	world->Step(dt, velocityIterations, positionIterations);
}
