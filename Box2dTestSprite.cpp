#include "Box2dTestSprite.h"
#include "Box2dHelper.h"
#include "test_case/b2RevoluteJointTestCase.h"
#include "test_case/ApplyFunctionTestCase.h"
#include "test_case/MassDataTestCase.h"
#include "test_case/ContactTestCase1.h"

#define PTM_RATIO 32

using namespace cocos2d;

Box2dTestSprite::Box2dTestSprite():
	testCase(nullptr)
{

}

Box2dTestSprite::~Box2dTestSprite()
{
	CC_SAFE_DELETE(testCase);
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

void Box2dTestSprite::_testCircleShape()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	//����Բ�ξ�̬����
	b2Vec2 circlePos((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	Box2dHelper::createStaticCircleBody(_L2World.world, circlePos, 1.0f);
}

void Box2dTestSprite::_testPolygonShape()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	b2Vec2 center = globalCenterPoint;
	//left_top
	b2Vec2 point1(-50 / PTM_RATIO, 50 / PTM_RATIO);
	//right_top
	b2Vec2 point2(50 / PTM_RATIO, 50 / PTM_RATIO);
	//left
	b2Vec2 point3(-75 / PTM_RATIO, 0);
	//right
	b2Vec2 point4( 75 / PTM_RATIO, 0);
	//left_down
	b2Vec2 point5(-50 / PTM_RATIO, -50 / PTM_RATIO);
	//right_down
	b2Vec2 point6(50 / PTM_RATIO, -50 / PTM_RATIO);
	std::vector<b2Vec2> points;
	points.emplace_back(point1);
	points.emplace_back(point2);
	points.emplace_back(point3);
	points.emplace_back(point4);
	points.emplace_back(point5);
	points.emplace_back(point6);
	Box2dHelper::createStaticPolygonBody(_L2World.world, globalCenterPoint, points);
}

void Box2dTestSprite::_testEdgeShape()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	b2Vec2 startPoint((visibleOrigin.x + visibleSize.width / 2 - 100) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	b2Vec2 endPoint((visibleOrigin.x + visibleSize.width / 2 + 100) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	Box2dHelper::createEdgeBody(_L2World.world, startPoint, endPoint);

	startPoint = b2Vec2((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2 - 100) / PTM_RATIO);
	endPoint = b2Vec2((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2 + 100) / PTM_RATIO);
	Box2dHelper::createEdgeBody(_L2World.world, startPoint, endPoint);
}

void Box2dTestSprite::_testChainShape()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	float height = 50.0f;
	b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	b2Vec2 point0((-250.0f) / PTM_RATIO, (100.0f) / PTM_RATIO);
	b2Vec2 point1((-200.0f) / PTM_RATIO, (0.0f) / PTM_RATIO);
	b2Vec2 point2((-150.0f) / PTM_RATIO, (height) / PTM_RATIO);
	b2Vec2 point3((-100.0f) / PTM_RATIO, (0.0f) / PTM_RATIO);
	b2Vec2 point4((-50.0f) / PTM_RATIO, (-height) / PTM_RATIO);
	b2Vec2 point5((0.0f) / PTM_RATIO, (0.0f) / PTM_RATIO);
	b2Vec2 point6((50.0f) / PTM_RATIO, (height) / PTM_RATIO);
	b2Vec2 point7((100.0f) / PTM_RATIO, (0.0f) / PTM_RATIO);
	b2Vec2 point8((150.0f) / PTM_RATIO, (-height) / PTM_RATIO);
	b2Vec2 point9((200.0f) / PTM_RATIO, (0.0f) / PTM_RATIO);
	b2Vec2 point10((250.0f) / PTM_RATIO, (100.0f) / PTM_RATIO);

	std::vector<b2Vec2> points;
	points.emplace_back(point0);
	points.emplace_back(point1);
	points.emplace_back(point2);
	points.emplace_back(point3);
	points.emplace_back(point4);
	points.emplace_back(point5);
	points.emplace_back(point6);
	points.emplace_back(point7);
	points.emplace_back(point8);
	points.emplace_back(point9);
	points.emplace_back(point10);

	Box2dHelper::createStaticChainBody(_L2World.world, globalCenterPoint, points);
}

//���Զ�ε���CreateFixtureΪ���������״
void Box2dTestSprite::_testCreateFixture()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = globalCenterPoint;
	b2Body* staticBody = _L2World.world->CreateBody(&bodyDef);

	float halfWidth = 2.0f;
	float halfHeight = 0.5f;
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(halfWidth, halfHeight);//These are mid points for our 1m box

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.restitution = 0.1f;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	staticBody->CreateFixture(&fixtureDef);

	polygonShape.SetAsBox(halfHeight, halfWidth);//These are mid points for our 1m box
	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &polygonShape;
	staticBody->CreateFixture(&fixtureDef2);
	
	polygonShape.SetAsBox(halfWidth, halfHeight, b2Vec2(0, halfWidth + halfHeight / 2), 0);
	//���ַ�ʽ��ǰ�ߵ��������ڣ��˺���ֻ���޸��ܶȺ���״����Ħ�������������޸Ĳ��ˡ�
	staticBody->CreateFixture(&polygonShape, 1.0f);

	_currentBody = staticBody;
}

void Box2dTestSprite::_testRevoluteJoint()
{
	float halfBodyWidth = 1.0f;
	float halfBodyHeight = 1.0f;
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	b2Vec2 pos(globalCenterPoint.x + halfBodyWidth, globalCenterPoint.y + halfBodyHeight);
	b2Body* body = Box2dHelper::createStaticBoxBody(_L2World.world, globalCenterPoint, halfBodyWidth, halfBodyHeight);
	_L2World.fixBodyAt(body, pos.x, pos.y, 100.0f);  //�����Χ��pos��ת����Ϊpos���ڸ�������Ͻǣ�����Χ����������Ͻ���ת��
	body->SetType(b2_dynamicBody); //ֻ�ж�̬���壬���ý��ٶȲ������á�����Ĭ��Ϊ��̬����
	//body->SetAngularVelocity(M_PI / 3);

	_currentBody = body;
}

void Box2dTestSprite::_testRevoluteJoint2()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);

	//body and fixture defs - the common parts
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;

	float halfBoxWidth = 1.0f;
	float halfBoxHeight = 1.0f;
	//two shapes
	b2PolygonShape boxShape;
	boxShape.SetAsBox(halfBoxWidth, halfBoxHeight);
	b2CircleShape circleShape;
	circleShape.m_radius = 1;

	bodyDef.position.Set(globalCenterPoint.x, globalCenterPoint.y);
	fixtureDef.shape = &boxShape;
	b2Body* m_bodyA = _L2World.world->CreateBody(&bodyDef);
	m_bodyA->CreateFixture(&fixtureDef);

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(globalCenterPoint.x - 5.0f, globalCenterPoint.y);
	
	fixtureDef.shape = &circleShape;
	fixtureDef.restitution = 0.7f;
	b2Body* m_bodyB = _L2World.world->CreateBody(&bodyDef);
	m_bodyB->CreateFixture(&fixtureDef);

	b2Vec2 globalPoint = m_bodyA->GetWorldPoint(b2Vec2(0, 0));
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.Initialize(m_bodyA, m_bodyB, globalPoint);
	revoluteJointDef.collideConnected = true;  //�ؽڵ����������Ƿ���໥��ײ
	revoluteJointDef.referenceAngle = 30.0f / 180 * M_PI;//���������ʱ����̫���
	revoluteJointDef.enableLimit = true;  //������û����������lowerAngle��upperAngle�����κ����á�
	revoluteJointDef.lowerAngle = 60.0f / 180 * M_PI; //��С�ĽǶȣ�bodyB�����������Ƕȣ��ٶ����ϼ�Ϊ0��
	revoluteJointDef.upperAngle = 135.0f / 180 * M_PI; //���ĽǶ�,bodyB�����������Ƕȣ��ٶ����ϼ�Ϊ0��
	///revoluteJointDef.referenceAngle = -90 / 180 * M_PI;
	b2RevoluteJoint* m_joint = (b2RevoluteJoint*)_L2World.world->CreateJoint(&revoluteJointDef);
	_currentRevoluteJoint = m_joint;
}

void Box2dTestSprite::_testQiaoQiaoBanRevoluteJoint()
{
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	b2Vec2 buttomCenter(globalCenterPoint.x, globalCenterPoint.y - 100.0f / PTM_RATIO);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = buttomCenter;

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;

	b2PolygonShape triangleShape;
	std::vector<b2Vec2> points;
	b2Vec2 left(-10.0 / PTM_RATIO, 0);
	b2Vec2 right(10.0 / PTM_RATIO, 0);
	b2Vec2 top(0, 20.0f / PTM_RATIO);
	points.emplace_back(left);
	points.emplace_back(right);
	points.emplace_back(top);
	triangleShape.Set(&points[0], points.size());
	fixtureDef.shape = &triangleShape;

	b2Body* m_triangleBody = _L2World.world->CreateBody(&bodyDef);
	m_triangleBody->CreateFixture(&fixtureDef);

	
	float halfBoxWidth = 5.0f;
	float halfBoxHeight = 0.05f;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(halfBoxWidth, halfBoxHeight);

	bodyDef.position.Set(buttomCenter.x, buttomCenter.y + top.y);
	fixtureDef.shape = &boxShape;
	bodyDef.type = b2_dynamicBody;
	b2Body* m_boxBody = _L2World.world->CreateBody(&bodyDef);
	m_boxBody->CreateFixture(&fixtureDef);


	b2Vec2 globalPoint = m_boxBody->GetWorldPoint(b2Vec2(0, 0));
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.Initialize(m_boxBody, m_triangleBody, globalPoint);
	
	revoluteJointDef.enableLimit = true;  //������û����������lowerAngle��upperAngle�����κ����á�
	revoluteJointDef.lowerAngle = -15.0f / 180 * M_PI; //��С�ĽǶȣ�bodyB�����������Ƕȣ��ٶ����ϼ�Ϊ0��
	revoluteJointDef.upperAngle = 15.0f / 180 * M_PI; //���ĽǶ�,bodyB�����������Ƕȣ��ٶ����ϼ�Ϊ0��
									   ///revoluteJointDef.referenceAngle = -90 / 180 * M_PI;
	b2RevoluteJoint* m_joint = (b2RevoluteJoint*)_L2World.world->CreateJoint(&revoluteJointDef);
	_currentRevoluteJoint = m_joint; 
}

void Box2dTestSprite::_testXiaoCheRevoluteJoint()
{
	testCase = new b2RevoluteJointTestCase(&this->_L2World);
	testCase->test();
}

void Box2dTestSprite::_testApplyFunction()
{
	testCase = new ApplyFunctionTestCase(&this->_L2World);
	testCase->test();
}

void Box2dTestSprite::_testMassData()
{
	testCase = new MassDataTestCase(&this->_L2World);
	testCase->test();
}

void Box2dTestSprite::_testContactTestCase1()
{
	testCase = new ContactTestCase1(&this->_L2World);
	testCase->test();
}

void Box2dTestSprite::initPhysics()
{
	_L2World.world->SetGravity(b2Vec2(0, -10.0f));
	cocos2d::Vec2 visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	b2Vec2 leftTop(visibleOrigin.x / PTM_RATIO, (visibleOrigin.y + visibleSize.height) / PTM_RATIO);
	b2Vec2 rightDown((visibleOrigin.x + visibleSize.width) / PTM_RATIO, visibleOrigin.y);
	Box2dHelper::createEdgeBody(_L2World.world, leftTop, rightDown);
	
	//b2Vec2 globalCenterPoint((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 2) / PTM_RATIO);
	//Box2dHelper::createStaticBoxBody(_L2World.world, globalCenterPoint, 5.0f, 0.5f);

	//b2Vec2 pos((visibleOrigin.x + visibleSize.width / 2) / PTM_RATIO, (visibleOrigin.y + visibleSize.height / 6) / PTM_RATIO);
	//Box2dHelper::createStaticBoxBody(_L2World.world, pos, 5.0f, 0.1f);
		
	//_testCircleShape();
	//_testPolygonShape();
	//_testEdgeShape();
	//_testChainShape();
	//_testCreateFixture();
	//_testRevoluteJoint();
	//_testRevoluteJoint2();
	//_testQiaoQiaoBanRevoluteJoint();
	//_testXiaoCheRevoluteJoint();
	//_testApplyFunction();
	//_testMassData();
	_testContactTestCase1();
}

bool Box2dTestSprite::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (testCase) {
		testCase->onTouchBegin(touch->getLocation());
	}
	return true;
}

void Box2dTestSprite::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	cocos2d::Vec2 pos = touch->getLocation();
	if (testCase) {
		testCase->onTouchEnd(touch->getLocation());
	}
	
	//Box2dHelper::createDefaultDynamicBoxBody(_L2World.world, b2Vec2(pos.x / PTM_RATIO, pos.y / PTM_RATIO), 0.5f, 0.5f);

	/*
	_currentRevoluteJoint->EnableMotor(true);
	_currentRevoluteJoint->SetMotorSpeed(M_PI / 10.0f * 30.0f);


	_currentBody->ApplyForce(b2Vec2(100.0f, 0.0f), _currentBody->GetWorldPoint(b2Vec2(-0.5f, 0.0f)), true);*/
	//cocos2d::log("current degree: %f", _currentRevoluteJoint->GetJointAngle() * 180 / M_PI);
	/***************b2CircleShape******************/
	//����Բ�ε�m_p
	//�����Ļ��Բ�λ������˶�,Բ�λ���
	//�������ԣ���������Ѿ��������ı�Բ�ε����ԣ�����ֱ����Ч������Ҫ����ResetMassData������������˵���г�ͻ��
	/*
	{
		b2CircleShape* shape = (b2CircleShape*)_staticCircleBody->GetFixtureList()->GetShape();
		if (shape)
		{
			shape->m_p.x = 0;
			shape->m_p.y -= 10.f / PTM_RATIO;
			shape->m_radius += 0.1f;
			//_staticCircleBody->ResetMassData(); //�����ÿ�����Ч
		}
	}
	*/

	/***************DestoryFixture******************/
	 
	//����DestoryFixture
	//����ɾ�������ÿ����״
	//ÿɾ��һ����״����ô������������Ķ���ı�
	/*
	{
		if (_currentBody)
		{
			b2Fixture* firstFixture = _currentBody->GetFixtureList();
			if (firstFixture)
			{
				_currentBody->DestroyFixture(firstFixture);
			}
			//�ݹ�ɾ�����е���״
			while (firstFixture)
			{
				_currentBody->DestroyFixture(firstFixture);
				firstFixture = _currentBody->GetFixtureList();
			}
		}
	}
	*/
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
	
	if (testCase) {
		testCase->step();
	}

	int velocityIterations = 8;
	int positionIterations = 1;

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	_L2World.world->Step(dt, velocityIterations, positionIterations);
	_L2World.world->ClearForces();
	
}
