#include "GameMenu.h"
#include "StageSelectScene.h"

USING_NS_CC;

Scene* GameMenu::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameMenu::create();

    scene->addChild(layer);

    return scene;
}

bool GameMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto gameStart = MenuItemImage::create(
                                           "newgameA.png",
                                           "newgameB.png",
										   CC_CALLBACK_1(GameMenu::gameStartCallBack,this));
	gameStart->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	auto menu = Menu::create(gameStart, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
	auto content = "menu";
	auto label = LabelTTF::create(content, "Arial", 24);  
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    auto backGround = Sprite::create("HelloWorld.png");
    backGround->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backGround, 0);

    return true;
}

void GameMenu::gameStartCallBack(Ref* pSender)
{
	Director::getInstance()->replaceScene(StageSelectScene::createScene());
}