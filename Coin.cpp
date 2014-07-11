#include "Coin.h"

USING_NS_CC;

Coin::Coin()
{
	coinsVector = new Vector<Sprite*>;
}

void Coin::removeOneCoin(Sprite* coin)
{
	auto layer = this->getParent();
	layer->removeChild(coin,false);
	coinsVector->eraseObject(coin);
}

void Coin::removeUselessCoins()
{
	auto layer = this->getParent();
	for(Vector<Sprite*>::iterator i = coinsVector->begin(); i != coinsVector->end(); i++)
	{
		auto worldSpace = this->convertToWorldSpace(i[0]->getPosition());

		if(worldSpace.x < 0)
		{
			layer->removeChild(i[0],false);
			i = coinsVector->erase(i);
		}
		if(i == coinsVector->end())
			break;
	}
}

Sprite* Coin::placeCoin()
{
	if(coinsVector->size() <= 4)
	{
		auto layer = this->getParent();
		auto newCoin = Sprite::create("CloseSelected.png");

		float y = CCRANDOM_0_1()*(250-80) + 80;
		Vec2 temp = Vec2(Director::getInstance()->getWinSize().width, y);
		Vec2 pos = this->convertToNodeSpace(temp);
		newCoin->setPosition(pos);
		coinsVector->pushBack(newCoin);

		return newCoin;
	}
	return NULL;
}