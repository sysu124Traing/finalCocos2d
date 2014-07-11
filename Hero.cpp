#include "Hero.h"
#include "StageScene.h"
#include "Bullet.h"
#include "Resource.h"

USING_NS_CC;

Hero::Hero()
{
	hp = 100;
	status = HERO_STATUS_NOMAL;
	buff = HERO_BUFF_NORMAL;

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	myHero = Sprite::create("DQIV.png",Rect(0,144,36,48));
	myHero->setScale(2);
	auto body = PhysicsBody::createCircle(myHero->getContentSize().width);
	body->getShape(0)->setFriction(0);
	body->setContactTestBitmask(0xFFFFFFFF);
	myHero->setPhysicsBody(body);
	//myHero->setPosition(Point(0,500));
	//body->applyForce(Vec2(0,body->getMass()*200));

	auto animation = Animation::create();
	auto frame1 = SpriteFrame::create("DQIV.png",Rect(36,144,36,48));
	auto frame2 = SpriteFrame::create("DQIV.png",Rect(72,144,36,48));
	auto frame3 = SpriteFrame::create("DQIV.png",Rect(108,144,36,48));
	animation->addSpriteFrame(frame1);
	animation->addSpriteFrame(frame2);
	animation->addSpriteFrame(frame3);
	animation->setDelayPerUnit(0.6f/3.0f);
	animation->setLoops(-1);
	auto anime = Animate::create(animation);
	myHero->runAction(anime);
}

bool Hero::injured(int damage)
{
	hp -= damage;
	HpBar* bar = (HpBar*)this->getParent()->getParent()->getParent()->getChildByTag(234)->getChildByTag(123);
	bar->changeHp(-damage);
	if(hp <= 0)
	{
		//TODO
		return false;
	}
	else
	{
		myHero->runAction(Blink::create(1,5));
		return true;
	}
}

void Hero::jump()
{
	if(status == HERO_STATUS_NOMAL)
	{
		float Force = this->myHero->getPhysicsBody()->getMass()*250;
		this->myHero->getPhysicsBody()->applyImpulse(Vec2(0,Force));
		status = HERO_STATUS_JUMP;
	}
}

void Hero::roll()
{
}

void Hero::attack()
{
	//获取层
	StageScene* layer = (StageScene*)this->getParent();
	//调用Bullet类的Launch方法，并addchild到层中
	layer->addChild(layer->getBulletClass()->Launch(this->myHero),1,TAG_BULLET);
}