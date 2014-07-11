#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0,-98));
	auto layer = HelloWorld::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create("DQIV.png",Rect(0, 144, 36, 48 ));
	sprite->setPosition( Point(visibleSize.width/4,visibleSize.height/2) );
	sprite->setTag(TAG_HERO);
	auto body = PhysicsBody::createBox( sprite->getContentSize() );
	body->setVelocity(Vec2(400,0));
	body->getShape(0)->setFriction( 0 );
	body->applyForce(Vec2(0, 98* body->getMass()));
	sprite->setPhysicsBody( body );
	layer->addChild(sprite);

	scene->runAction(Follow::create(sprite));
    
	return scene;

}
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

	ob=  Obstacle::create(this);
	mym = MyMap::create(this);
	this->scheduleUpdate();
	return true;
}
void HelloWorld::update(float time){
	ob->Manager(this->getChildByTag(TAG_HERO)->getPositionX(),this->getChildByTag(TAG_HERO)->getPositionY());
	mym->mapReload(this->getChildByTag(TAG_HERO)->getPositionX());
}




void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
