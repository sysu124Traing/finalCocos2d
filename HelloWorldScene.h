#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Obstacle.h"
#include "refe.h"
#include "MyMap.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
    PhysicsWorld* m_world;
public:
	Obstacle* ob;
	void setPhyWorld(PhysicsWorld* world){m_world = world;}
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    void menuCloseCallback(cocos2d::Ref* pSender);
	void update(float time);
	MyMap* mym;
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
