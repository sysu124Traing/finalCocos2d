#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class Hero : public cocos2d::Node
{
public:
	Hero();
	bool injured(int damage);
	
	void roll();
	void jump();
	void attack();

	int hp;
	int status;
	int buff;

	Sprite* myHero;
};
#endif