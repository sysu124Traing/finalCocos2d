#include "HpBar.h"

USING_NS_CC;

HpBar::HpBar(int max)
{
	maxHp = max;
	currentHp = max;

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*background = Sprite::create("background.jpg");
	background->setPositionY(origin.y + visibleSize.height - background->getContentSize().height);
	this->addChild(background);*/

	hp = Sprite::create("hp.jpg");

	progressTimer = ProgressTimer::create(hp);
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer->setMidpoint(Vec2(0,1));
	progressTimer->setBarChangeRate(Vec2(1,0));
	progressTimer->setPercentage(100);
	this->addChild(progressTimer);
	progressTimer->setPosition(progressTimer->getPositionX() + progressTimer->getContentSize().width*2.5,origin.y + visibleSize.height - progressTimer->getContentSize().height);
	progressTimer->setScaleY(2);
	progressTimer->setScaleX(5);

	progressTimer->retain();
}

void HpBar::changeHp(int change)
{
	currentHp += change;
	if(currentHp < 0)
		currentHp = 0;
	else if(currentHp > maxHp)
		currentHp = maxHp;
	auto progress = ProgressFromTo::create(0.5,progressTimer->getPercentage(),currentHp/maxHp*100);
	progressTimer->runAction(progress);
}