#include "Level1.h"
#include "Definitions.h"
#include "LoadingScreen.h"
#include "MyBodyParser.h"
#include "LevelsScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
bool pressed=false;
int NDirX = 0;
int NDirY = 0;
int Tentative;
cocos2d::EventKeyboard::KeyCode pressedKey;
Scene* Level1::createScene() {

    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = Level1::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->getPhysicsWorld()->setGravity(Vec2(0, -40));

    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Level1.cpp\n");

}
auto visibleSize = Director::getInstance()->getVisibleSize();
Vec2 origin = Director::getInstance()->getVisibleOrigin();

// on "init" you need to initialize your instance
Point start;
Point finish;
Point PosPlay;
Point PosPlayWin;
bool Level1::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /////
    ///
    ///
    
    auto label = Label::createWithTTF("Tentative :"+std::to_string(Tentative), "fonts/pico.ttf", 12);
    if (label == nullptr)
    {
        problemLoading("'fonts/pico.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Point(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    label->setTextColor(Color4B::ORANGE);

    
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point((visibleSize.width) / 2 + origin.x, (visibleSize.height / 2) + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    backgroundSprite = Sprite::create("background.png");

    WinPoint = Sprite::create("WinPoint.png");

   
    auto actionBACK = ScaleBy::create(0, 0.4);
    
    backgroundSprite->setPosition(Point(0, (visibleSize.height / 2)));
    
    WinPoint->setPosition(Point((3 * visibleSize.width), (visibleSize.height / 3) + origin.y));
    WinPoint->runAction(ScaleBy::create(0, 0.4));
    auto bodyWP=PhysicsBody::createCircle(WinPoint->getContentSize().width/2);
    bodyWP->setContactTestBitmask(true);
    bodyWP->setDynamic(false);
    WinPoint->setPhysicsBody(bodyWP);
    //---
    //ball
    ball = Sprite::create("ball.png");
    ball->setPosition(Point((0.5 * visibleSize.width), (visibleSize.height / 3) + origin.y));
    ball->runAction(ScaleBy::create(0, 0.7));
    ball->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Point(0, 40)), MoveBy::create(1, Point(0, -40)), NULL)));
    auto ball_body = PhysicsBody::createBox(ball->getContentSize() / 1, PhysicsMaterial(0, 0, 1));
    ball_body->setDynamic(false);
    ball_body->setCollisionBitmask(2);
    ball_body->setContactTestBitmask(true);
    ball->setPhysicsBody(ball_body);
    this->addChild(ball,3);


    ball2 = Sprite::create("ball.png");
    ball2->setPosition(Point((1.3 * visibleSize.width), (visibleSize.height / 3) + origin.y));
    ball2->runAction(ScaleBy::create(0, 0.7));
    ball2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Point(0, 60)), MoveBy::create(1, Point(0, -60)), NULL)));
    auto ball2_body = PhysicsBody::createBox(ball2->getContentSize() / 1, PhysicsMaterial(0, 0, 1));
    ball2_body->setDynamic(false);
    ball2_body->setCollisionBitmask(2);
    ball2_body->setContactTestBitmask(true);
    ball2->setPhysicsBody(ball2_body);
    this->addChild(ball2,6);

 
   

    //ball
   
    //spikes
    spike1 = Sprite::create("spike1.png");
    spike1->setPosition(Point((2.2 * visibleSize.width), (visibleSize.height / 3.45) + origin.y));
    spike1->runAction(ScaleBy::create(0, 0.35));
    auto spikeBody1 = PhysicsBody::createBox(spike1->getContentSize() / 1.25, PhysicsMaterial(0, 0, 1));
    spikeBody1->setDynamic(false);
    spikeBody1->setContactTestBitmask(true);

    spike1->setPhysicsBody(spikeBody1);
    spike1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Point(-80, 0)), MoveBy::create(1, Point(80, 0)), NULL)));


    this->addChild(spike1,5);


   spike2 = Sprite::create("spike2.png");
   spike2->setPosition(Point((2.25 * visibleSize.width), (visibleSize.height / 3.45) + origin.y));
   spike2->runAction(ScaleBy::create(0, 0.35));
    auto spikeBody2 = PhysicsBody::createBox(spike2->getContentSize()/1.25 , PhysicsMaterial(0, 0, 1));
    spikeBody2->setDynamic(false);
    spikeBody2->setContactTestBitmask(true);

   spike2->setPhysicsBody(spikeBody2);
   spike2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Point(60, 0)), MoveBy::create(1, Point(-60, 0)), NULL)));


    this->addChild(spike2,1);
     ////////////////////
    

    //wrecking ball

    

    WreckBall = Sprite::create("wreckingball.png");

    WreckBall->setPosition(Point((2.7 * visibleSize.width), (visibleSize.height / 2.21) + origin.y));
    auto WreckBallBody2 = PhysicsBody::createBox(WreckBall->getContentSize() / 1.23, PhysicsMaterial(0, 0, 1));
    WreckBallBody2->setDynamic(false);
    WreckBallBody2->setContactTestBitmask(true);

    WreckBall->setPhysicsBody(WreckBallBody2);

    this->addChild(WreckBall);

    auto actionWBall = RotateTo::create(1, 90);
    


    WreckBall->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.7,-90), RotateBy::create(0.7,90), NULL)));

    auto actionBACK2 = ScaleBy::create(0, 0.8);

   WreckBall->runAction(actionBACK2);

    // triangle a 2 :
    Triangle_2 = Sprite::create("triangleTrap.png");
    Triangle_2->setPosition(Point((0.9 * visibleSize.width), (visibleSize.height / 3.5) + origin.y));
    Triangle_2->runAction(ScaleBy::create(0, 0.15));
    auto Triangle3_Body = PhysicsBody::createBox(Triangle_2->getContentSize() / 1.25, PhysicsMaterial(0, 0, 1));
    Triangle3_Body->setDynamic(false);
    Triangle3_Body->setContactTestBitmask(true);
    Triangle_2->setPhysicsBody(Triangle3_Body);
    this->addChild(Triangle_2);


    Triangle2_2 = Sprite::create("triangleTRAP12.png");
    Triangle2_2->setPosition(Point((1.8 * visibleSize.width), (visibleSize.height / 3.55) + origin.y));
    Triangle2_2->runAction(ScaleBy::create(0, 0.35));
    auto Triangle2_Body = PhysicsBody::createBox(Triangle2_2->getContentSize() / 1.25, PhysicsMaterial(0, 0, 1));
    Triangle2_Body->setDynamic(false);
    Triangle2_Body->setContactTestBitmask(true);
    Triangle2_2->setPhysicsBody(Triangle2_Body);
    this->addChild(Triangle2_2,2);


    // - - - - - - - - -  -
    FloorSprite = Sprite::create
    ("flor2.png");
    FloorSprite->setPosition(Point((1.7 * visibleSize.width), (visibleSize.height / 8.3)));
    auto action1 = ScaleBy::create(0, 0.55);
    backgroundSprite->runAction(actionBACK);
    FloorSprite->runAction(action1);
    auto body1 = PhysicsBody::createBox(FloorSprite->getContentSize() / 1.1, PHYSICSBODY_MATERIAL_DEFAULT);
    body1->setContactTestBitmask(false);
    body1->setDynamic(false);
 
    FloorSprite->setPhysicsBody(body1);
    start = Point((1.7 * visibleSize.width), (visibleSize.height / 3) + origin.y);
    finish = Point((1.7 * visibleSize.width) - 900, (visibleSize.height / 3) + origin.y);
    PosPlay = Vec2(visibleSize.width / 4.5 + origin.x, visibleSize.height / 3.42 + origin.y);
    PosPlayWin = Vec2(visibleSize.width / 1.5 + origin.x, visibleSize.height / 3.42 + origin.y);

    myPlayer = Sprite::create("Player.png");
    myPlayer->setPosition(Vec2(visibleSize.width / 4.5 + origin.x, visibleSize.width / 5 + origin.y));
    auto body = PhysicsBody::createBox(myPlayer->getContentSize() / 1.3, PhysicsMaterial(0, 0, 0));
    body->setCollisionBitmask(2);
    body->setContactTestBitmask(true);
    body->setDynamic(true);
    myPlayer->setPhysicsBody(body);

    this->addChild(myPlayer,10);
    this->addChild(backgroundSprite, -10);
   
    this->addChild(FloorSprite);
    this->addChild(WinPoint, 10);



    auto action = ScaleBy::create(0, 0.15);
    myPlayer->runAction(action);
    




    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Level1::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


    
    
    
    isTouching = false;
    touchPosition = 0;
    // touch event
    EventListenerKeyboard* listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            NDirY += 4.0f;
            break;
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            NDirX -= 4.0f;
            break;
        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            NDirY -= 4.0f;
            break;
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            NDirX += 4.0f;
            break;
        }
    };

    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            NDirY = 0;
            break;
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:

            NDirX = 0;
            break;
        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            NDirY = 0;
            break;
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            NDirX = 0;
            pressed=true;
            break;
        }
    };



    this->scheduleUpdate();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    /*
    EventListenerKeyboard* onKeyBoardEvent = EventListenerKeyboard::create();
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(onKeyBoardEvent, myPlayer);
    */



   

    //fonction transition
    auto GoBack = MenuItemImage::create("Goback.png", "Goback.png", CC_CALLBACK_1(Level1::GoBackToLevelsScene, this));
    GoBack->setPosition(Point(visibleSize.width / 8, (visibleSize.height / 10) * 9));

    auto menu1 = Menu::create(GoBack, NULL);
     menu1->setPosition(Point::ZERO);
    this->addChild(menu1);
   
    return true;
}

int para;
void Level1::update(float dt) {

    if(myPlayer->getPositionX()>PosPlay.x && NDirX < 0){
        myPlayer->setPositionX(myPlayer->getPosition().x + NDirX );
    }
    else if(NDirX>0 && finish.x <= FloorSprite->getPosition().x || NDirX<0 && start.x >= FloorSprite->getPosition().x) {
        FloorSprite->setPositionX(FloorSprite->getPositionX() - NDirX);
        WinPoint->setPositionX(WinPoint->getPositionX() - NDirX);
        spike1->setPositionX(spike1->getPositionX() - NDirX);
        spike2->setPositionX(spike2->getPositionX() - NDirX);
        ball->setPositionX(ball->getPositionX() - NDirX);
        ball2->setPositionX(ball2->getPositionX() - NDirX);
        WreckBall->setPositionX(WreckBall->getPositionX() - NDirX);
        Triangle_2->setPositionX(Triangle_2->getPositionX() - NDirX);
        Triangle2_2->setPositionX(Triangle2_2->getPositionX() - NDirX);
       

    }else if(finish.x >= FloorSprite->getPosition().x){
        myPlayer->setPositionX(myPlayer->getPosition().x + NDirX );
    }
    
    if (NDirY > 0 && myPlayer->getPositionY() < PosPlay.y) {
        myPlayer->runAction(JumpTo::create(0.5, Point(myPlayer->getPositionX(), myPlayer->getPositionY()), 30, 1));
        CocosDenshion::SimpleAudioEngine::getInstance()->
        playEffect("Jump.mp3");
    }

}

bool Level1::onContactBegin(PhysicsContact& contact)
{
    NDirX=0;
    NDirY=0;

    if (myPlayer->getPositionX()>PosPlayWin.x ) {
        
        CocosDenshion::SimpleAudioEngine::getInstance()->
        playEffect("WIN.mp3");
        Tentative=0;
        auto scene = LevelsScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }else if(pressed){
        pressed=false;
        Tentative++;
        auto scene = Level1::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    

    return true;
}
//void Level1::GoBackToLevelsScene(cocos2d::Ref* sender) {
//
//    NDirector::getInstance()->popScene();
//}

//fonction transition
void Level1::GoBackToLevelsScene(cocos2d::Ref* sender) {
    auto scene = LevelsScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
