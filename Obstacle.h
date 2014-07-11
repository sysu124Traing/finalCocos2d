#ifndef _OBSTACLE_
#define _OBSTACLE_

#include "cocos2d.h"
#include "resource.h"
USING_NS_CC;

class Obstacle :public cocos2d::Node{
public:
	float herox,heroy;
	Size s;
	Layer* layer;
	Obstacle();
	int timeController;
	int groundPos;
	Array* currentOblist;
	int startPos; //��ʼλ��

	static Obstacle* create(Layer* layer);
	int obType();
	int miType();

	void addHoleob(float pos);
	void Manager(float pos,float y);
	void addWallob(float pos);
	void addMissile(float pos);
	void addBandingob(float pos,float distance);
	
	Vector<Sprite*> groundlist;
	float curGround;
	float curLength;
	float nextGround;
	float nextLength;
	float setLength();//���õذ峤��
	float setInterval();//���õذ���
	void addGroundob();
	bool isGroundob(float pos);
	
	bool isWallob();
	bool isMissileob();
	bool isBandingob();
	float setMissilePos();
};
#endif