#include "LevelsScene.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"

USING_NS_CC;

Scene* LevelsScene::createScene()
{
    return LevelsScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LevelsScene::init()
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


    auto LevelItem = MenuItemImage::create("Level1pre.png", "Level1.png", CC_CALLBACK_1(LevelsScene::GoToLevel1Scene, this));
    LevelItem->setPosition(Point((visibleSize.width / 4)+LevelItem->getContentSize().width/2, visibleSize.height / 2));
    
    auto Level2Item = MenuItemImage::create("Level2pre.png", "Level2.png", CC_CALLBACK_1(LevelsScene::GoToLevel2Scene, this));
    Level2Item->setPosition(Point((visibleSize.width / 2)+Level2Item->getContentSize().width/2, visibleSize.height / 2));


    auto Level3Item = MenuItemImage::create("Level3pre.png", "Level3.png", CC_CALLBACK_1(LevelsScene::GoToLevel3Scene, this));
    Level3Item->setPosition(Point((visibleSize.width / 4)*3+Level3Item->getContentSize().width/2, visibleSize.height / 2));

    auto menu1 = Menu::create(Level3Item, Level2Item, LevelItem, NULL);


    menu1->setPosition(Point::ZERO);
    this->addChild(menu1);



    return true;
}

void LevelsScene::GoToLevel1Scene(cocos2d::Ref* sender) {
    auto scene = Level1::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->    playEffect("Click.mp3");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}

void LevelsScene::GoToLevel2Scene(cocos2d::Ref* sender) {
    auto scene = Level2::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Click.mp3");

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void LevelsScene::GoToLevel3Scene(cocos2d::Ref* sender) {
    auto scene = Level3::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->
    playEffect("Click.mp3");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


