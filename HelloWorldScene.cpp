#include "HelloWorldScene.h"
#include "LevelsScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorld.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("MENU.png");
    backgroundSprite->runAction(ScaleBy::create(0, 0.33));
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    
    auto playItem = MenuItemImage::create("Playpre.png", "Play.png", CC_CALLBACK_1(HelloWorld::GoToLevelsScene, this));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));


    auto menu = Menu::create(playItem, NULL);


    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    return true;
}

void HelloWorld::GoToLevelsScene(cocos2d::Ref* sender) {
    auto scene = LevelsScene::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->
    playEffect("Click.mp3");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
