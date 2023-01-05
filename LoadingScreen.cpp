#include "LoadingScreen.h"
#include "HelloWorldScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* LoadingScreen::createScene()
{
    return LoadingScreen::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SplashScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadingScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //schedule GoToMenuScene function to run after a set period of time
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(LoadingScreen::GoToMenuScene), 3);

    auto backgroundSprite = Sprite::create("LoadingScreen.png");
    backgroundSprite->runAction(ScaleBy::create(0, 0.33));
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backgroundSprite);

    return true;
}

//define our GoToMenuScene
void LoadingScreen::GoToMenuScene(float dt) {
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

