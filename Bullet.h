#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

USING_NS_CC;

class Bullet : public cocos2d::Node
{
public:
	Bullet();
	Sprite* Launch(Sprite* from, int direction = 1);	//1为向右，-1为向左
	void Hit(Sprite* target);	
	void removeUselessBullets();
	void removeOneBullet(Sprite* bullet);

private:
	Vector<Sprite*>* bulletsVector;
};
#endif