#ifndef __HPBAR_H__
#define __HPBAR_H__

#include "cocos2d.h"

USING_NS_CC;

class HpBar : public Node
{
public:
	HpBar(int max);
	void changeHp(int change);

private:
	float maxHp;
	float currentHp;
	Sprite* background;
	Sprite* hp;
	ProgressTimer* progressTimer;
};

#endif