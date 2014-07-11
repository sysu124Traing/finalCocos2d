#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet()
{
	bulletsVector = new Vector<Sprite*>;
}

Sprite* Bullet::Launch(Sprite* from, int direction)
{
	auto bullet = Sprite::create("CloseNormal.png");
	bullet->setPosition(from->getPositionX() + 1.2*direction*from->getContentSize().width, from->getPositionY());
	bullet->setScale(0.5);
	//bullet->runAction(MoveBy::create(1,Vec2(2000,0)));
	auto body = PhysicsBody::createCircle(bullet->getContentSize().width /4);
	body->getShape(0)->setFriction(0);
	body->setContactTestBitmask(0xFFFFFFFF);
	body->setVelocity(Vec2(1000*direction,0));
	bullet->setPhysicsBody(body);

	bulletsVector->pushBack(bullet);

	return bullet;
}

void Bullet::removeOneBullet(Sprite* bullet)
{
	auto layer = this->getParent();
	layer->removeChild(bullet,false);
	bulletsVector->eraseObject(bullet);
}

void Bullet::removeUselessBullets()
{
	auto layer = this->getParent();
	for(Vector<Sprite*>::iterator i = bulletsVector->begin(); i != bulletsVector->end(); i++)
	{
		auto worldSpace = this->convertToWorldSpace(i[0]->getPosition());

		if(worldSpace.x > Director::getInstance()->getWinSize().width)
		{
			layer->removeChild(i[0],false);
			i = bulletsVector->erase(i);
		}
		if(i == bulletsVector->end())
			break;
	}
}

void Bullet::Hit(Sprite* target)
{
	//TODO
}