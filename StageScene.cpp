#include "StageScene.h"
#include "Resource.h"

Scene* StageScene::createScene()
{
	srand(unsigned(time(0)));

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bigScene = Scene::create();

	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0,-200.0f));

    auto layer = StageScene::create();
	auto informationLayer = Layer::create();
	layer->setPhyWorld(scene->getPhysicsWorld());

	HpBar* hpBar = new HpBar(100);
	informationLayer->addChild(hpBar,0,123);

	auto content = "stage demo";
	auto label = Label::create(content, "Arial", 24);  
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
							origin.y + visibleSize.height - label->getContentSize().height));
	informationLayer->addChild(label);

	/*auto body = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);*/

	layer->camera = new ActionCamera();
	layer->camera->startWithTarget(scene);

    scene->addChild(layer);
	bigScene->addChild(scene,0);
	bigScene->addChild(informationLayer,1,234);
	
	//scene->addChild(edgeNode);

    return bigScene;
}

bool StageScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	b = new Bullet();
	this->addChild(b);

	c = new Coin();
	this->addChild(c);

	o = Obstacle::create(this);
	m = MyMap::create(this);

	//加载手势识别模板
	g_r = new GeometricRecognizer;
	g_r->loadTemplates();

	//初始化Hero对象
	hero = new Hero();
	hero->myHero->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	hero->myHero->getPhysicsBody()->setVelocity(Vec2(100,0));
	this->addChild(hero);
	this->addChild(hero->myHero,1,TAG_HERO);

	auto ob = new Hero();
	ob->myHero->setPosition(Vec2(visibleSize.width/2 + origin.x + 1000, visibleSize.height/2 + origin.y));
	this->addChild(ob);
	this->addChild(ob->myHero,1,TAG_ENEMY);

	//初始化地面
	/*auto groundBody = PhysicsBody::createEdgeSegment(Vec2(0,30),Vec2(INT16_MAX,30),PHYSICSBODY_MATERIAL_DEFAULT,3);
	groundBody->setContactTestBitmask(0xFFFFFFFF);
	groundBody->setDynamic(false);
	auto ground = Node::create();
	ground->setPosition(Point(0,10));
	ground->setPhysicsBody(groundBody);
	this->addChild(ground,1,TAG_GROUND);*/

	//触摸事件监听
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(StageScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(StageScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(StageScene::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [=](const PhysicsContact& contact)
	{
		auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
		if(spriteA == NULL || spriteB == NULL)
			return false;

		//主角与地面碰撞，将主角状态从JUMP恢复为NOMAL
		if((spriteA->getTag() == TAG_HERO && spriteB->getTag() == TAG_GROUND) || (spriteB->getTag() == TAG_HERO && spriteA->getTag() == TAG_GROUND))
		{
			auto body = hero->myHero->getPhysicsBody();
			body->setVelocity(Vec2(body->getVelocity().x,0));
			hero->status = HERO_STATUS_NOMAL;
		}

		//子弹与其他物体碰撞，消除子弹
		else if(spriteA->getTag() == TAG_BULLET || spriteB->getTag() == TAG_BULLET)
		{
			if(spriteA->getTag() == TAG_BULLET)
				b->removeOneBullet(spriteA);
			else
				b->removeOneBullet(spriteB);
			hero->injured(10);
		}
		
		return true;
	};
	dispatcher->addEventListenerWithFixedPriority(contactListener,10);
    
	scheduleUpdate();

    return true;
}

void StageScene::update(float time){
	//设置相机跟随主角移动
	auto LastEyeX = hero->myHero->getPositionX() - hero->myHero->getContentSize().width;
	auto EyeZ = camera->getEye().z;
	camera->setEye(LastEyeX,0,EyeZ);
	camera->setCenter(Vec3(LastEyeX ,0,0));
	//保持主角的前进速度
	hero->myHero->getPhysicsBody()->setVelocity(Vec2(400,hero->myHero->getPhysicsBody()->getVelocity().y));
	//清除所有飞出屏幕范围外的子弹
	b->removeUselessBullets();
	c->removeUselessCoins();

	if(CCRANDOM_0_1() > 0.99)
	{
		auto newCoin = c->placeCoin();
		if(newCoin != NULL)
			this->addChild(newCoin,1,TAG_COIN);
	}
	o->Manager(hero->myHero->getPositionX(),hero->myHero->getPositionY());
	m->mapReload(hero->myHero->getPositionX());
}

bool StageScene::onTouchBegan(Touch *touch, Event* event)
{
	//hero->jump();
	return true;
}

void StageScene::onTouchMoved(Touch *touch, Event* event)
{
	Point location = touch->getLocationInView();

	Point2D temp;
	temp.x = location.x;
	temp.y = location.y;

	p2d.push_back(temp);
}

void StageScene::onTouchEnded(Touch *touch, Event* event)
{
	//单击屏幕——攻击
	if(p2d.size() < 1)
		hero->attack();
		//return;
	//向上划——跳
	else
	{
		RecognitionResult r = g_r->recognize(p2d);
		if(r.name == "Up")
			hero->jump();
		p2d.clear();
	}
}

Bullet* StageScene::getBulletClass(){
	return b;
}