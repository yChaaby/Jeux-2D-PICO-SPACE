#include "Level2.h"
#include "LoadingScreen.h"
#include "MyBodyParser.h"
#include "LevelsScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
bool pressed2;
int nX = 0;
int nY = 0;
int Tentative2;
Point PosPlay21;
cocos2d::EventKeyboard::KeyCode pressed2Key2;
Scene* Level2::createScene() {

    auto scene = Scene::createWithPhysics();
    // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = Level2::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->getPhysicsWorld()->setGravity(Vec2(0, -40));

    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Level2.cpp\n");

}
auto visibleSize2 = Director::getInstance()->getVisibleSize();
Vec2 origin2 = Director::getInstance()->getVisibleOrigin();

// on "init" you need to initialize your instance
Point start2;
Point finish2;
Point PosPlay2;
bool Level2::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    this->scheduleUpdate();
    nX=0;
    nY=0;
    auto visibleSize2 = Director::getInstance()->getVisibleSize();
    Vec2 origin2 = Director::getInstance()->getVisibleOrigin();
    /////
    ///
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize2, PHYSICSBODY_MATERIAL_DEFAULT);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point((visibleSize2.width) / 2 + origin2.x, (visibleSize2.height / 2) + origin2.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    auto label = Label::createWithTTF("Tentative :"+std::to_string(Tentative2), "fonts/pico.ttf", 12);
    if (label == nullptr)
    {
        problemLoading("'fonts/pico.ttf'");
    }
    else
    {
       
        label->setPosition(Point(origin2.x + visibleSize2.width/2,
                                origin2.y + visibleSize2.height - label->getContentSize().height));

        this->addChild(label, 1);
    }

    ////
    backgroundSprite = Sprite::create("Backgroud2.jpg");
    Mob = Sprite::create("trapTYPE1.png");
    WinPoint = Sprite::create("WinPoint.png");

    auto actionTRAP = RotateBy::create(0.1, 50);

    Mob->runAction(RepeatForever::create(actionTRAP));

    Mob->setPosition(Point((1.3 * visibleSize2.width), (visibleSize2.height / 3) + origin2.y));
    auto actionBACK = ScaleBy::create(0, 0.35);
    auto actionBACK1 = ScaleBy::create(0, 0.3);
    backgroundSprite->setPosition(Point(0, (visibleSize2.height / 2)));
    // mob setup physique :
    auto Mob_Body = PhysicsBody::createCircle(Mob->getContentSize().width / 2);
    Mob_Body->setCollisionBitmask(1);
    Mob_Body->setContactTestBitmask(true);
    Mob_Body->setDynamic(true);
    Mob->setPhysicsBody(Mob_Body);
    WinPoint->setPosition(Point((3 * visibleSize2.width), (visibleSize2.height / 3) + origin2.y));
    WinPoint->runAction(ScaleBy::create(0, 0.4));
    auto bodyWP=PhysicsBody::createCircle(WinPoint->getContentSize().width/2);
    bodyWP->setContactTestBitmask(true);
    bodyWP->setDynamic(false);
    WinPoint->setPhysicsBody(bodyWP);
    //---
    Hamer = Sprite::create("Hamer.png");
    Hamer->setPosition(Point((0.97 * visibleSize2.width), (visibleSize2.height / 2.62) + origin2.y));
    Hamer->runAction(ScaleBy::create(0, 0.4));
    Hamer->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Point(0, 80)), MoveBy::create(1, Point(0, -80)), NULL)));
    auto Hamer_body = PhysicsBody::createBox(Hamer->getContentSize() / 1, PhysicsMaterial(0, 0, 1));
    Hamer_body->setDynamic(false);
    Hamer_body->setCollisionBitmask(2);
    Hamer_body->setContactTestBitmask(true);
    Hamer->setPhysicsBody(Hamer_body);
    this->addChild(Hamer);

    Hamer2 = Sprite::create("Hamer.png");
    Hamer2->setPosition(Point((1.65 * visibleSize2.width), (visibleSize2.height / 1.9) + origin2.y));
    Hamer2->runAction(ScaleBy::create(0, 0.4));
    Hamer2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.8, Point(0, 80)), MoveBy::create(1, Point(0, -80)), NULL)));
    auto Hamer_body2 = PhysicsBody::createBox(Hamer2->getContentSize() / 1, PhysicsMaterial(0, 0, 1));
    Hamer_body2->setDynamic(false);
    Hamer_body2->setCollisionBitmask(2);
    Hamer_body2->setContactTestBitmask(true);
    Hamer2->setPhysicsBody(Hamer_body2);
    
   

    //Hamer
    Bob = Sprite::create("eye.png");
    Bob->setPosition(Point((0.64 * visibleSize2.width), (visibleSize2.height / 3.5) + origin2.y));
    Bob->runAction(ScaleBy::create(0, 0.65));
    auto Bobody = PhysicsBody::createBox(Bob->getContentSize() / 1.25, PhysicsMaterial(0, 0, 1));
    Bobody->setDynamic(false);
    Bobody->setContactTestBitmask(true);

    Bob->setPhysicsBody(Bobody);
    Bob->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Point(45, 0)), MoveBy::create(1, Point(-45, 0)), NULL)));


    this->addChild(Bob);


    Bob2 = Sprite::create("eye.png");
    Bob2->setPosition(Point((2.8 * visibleSize2.width), (visibleSize2.height / 3.5) + origin2.y));
    Bob2->runAction(ScaleBy::create(0, 0.65));
    auto Bobody2 = PhysicsBody::createBox(Bob2->getContentSize() / 1.25, PhysicsMaterial(0, 0, 1));
    Bobody2->setDynamic(false);
    Bobody2->setContactTestBitmask(true);

    Bob2->setPhysicsBody(Bobody2);
    Bob2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Point(-60, 0)), MoveBy::create(1, Point(60, 0)), NULL)));


    this->addChild(Bob2);
    
    // trigle a 3 :
    Triagle_3 = Sprite::create("Triagle3.png");
    Triagle_3->setPosition(Point((1.65 * visibleSize2.width), (visibleSize2.height / 3.5) + origin2.y));
    Triagle_3->runAction(ScaleBy::create(0, 0.35));
    auto Triangle3_Body = PhysicsBody::createBox(Triagle_3->getContentSize() / 1.25, PhysicsMaterial(0, 0, 1));
    Triangle3_Body->setDynamic(false);
    Triangle3_Body->setContactTestBitmask(true);
    Triagle_3->setPhysicsBody(Triangle3_Body);
    this->addChild(Triagle_3);

    fire = Sprite::create("fiya.png");
    fire->setPosition(Point((2.4 * visibleSize2.width), (visibleSize2.height / 3.7) + origin2.y));
    fire->runAction(ScaleBy::create(0, 0.35));
    
    fire->setOpacity(0);
    auto fadeOut = FadeOut::create(3);
    auto fadeIn = FadeIn::create(3);
    auto actionFire1= Sequence::create(fadeOut,fadeIn,NULL);
    fire->runAction(RepeatForever::create(actionFire1));
    auto fire_Body = PhysicsBody::createBox(fire->getContentSize() / 1.25, PhysicsMaterial(0, 0, 1));
    fire_Body->setDynamic(false);
    fire_Body->setContactTestBitmask(true);
    fire->setPhysicsBody(fire_Body);
    this->addChild(fire);
    // - - - - - - - - -  -
    FloorSprite = Sprite::create
    ("flor3.png");
    FloorSprite->setPosition(Point((1.7 * visibleSize2.width), (visibleSize2.height / 8.3)));
    auto action1 = ScaleBy::create(0, 0.55);
    backgroundSprite->runAction(actionBACK);
    FloorSprite->runAction(action1);
    auto body1 = PhysicsBody::createBox(FloorSprite->getContentSize() / 1.1, PHYSICSBODY_MATERIAL_DEFAULT);
    body1->setContactTestBitmask(false);
    body1->setDynamic(false);
    
    FloorSprite->setPhysicsBody(body1);
    start2 = Point((1.7 * visibleSize2.width), (visibleSize2.height / 3) + origin2.y);
    finish2 = Point((1.7 * visibleSize2.width) - 900, (visibleSize2.height / 3) + origin2.y);
    PosPlay2 = Vec2(visibleSize2.width / 4.5 + origin2.x, visibleSize2.height / 3.42 + origin2.y);
    PosPlay21=Point(visibleSize2.width*0.65 + origin2.x, visibleSize2.height/3.42 + origin2.y);

    myPlayer = Sprite::create("Player.png");
    myPlayer->setPosition(Vec2(visibleSize2.width / 4.5 + origin2.x, visibleSize2.width / 5 + origin2.y));
    auto body = PhysicsBody::createBox(myPlayer->getContentSize() / 1.3, PhysicsMaterial(0, 0, 0));
    body->setCollisionBitmask(2);
    body->setContactTestBitmask(true);
    body->setDynamic(true);
    myPlayer->setPhysicsBody(body);

    this->addChild(myPlayer);
    this->addChild(backgroundSprite, -10);
    this->addChild(Mob, 10);
    this->addChild(FloorSprite, -1);
    this->addChild(WinPoint, 10);



    auto action = ScaleBy::create(0, 0.15);
    myPlayer->runAction(action);
    Mob->runAction(actionBACK1);




    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Level2::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


   
    // touch event
    EventListenerKeyboard* listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            nY += 4.0f;
            break;
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            nX -= 4.0f;
            break;
        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            nY -= 4.0f;
            break;
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

            nX += 4.0f;
            break;
        }
    };

    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        
        printf("%d",nX);
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            nY =0;
            break;
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:

            nX =0;
            break;
        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            nY =0;
            break;
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

            nX =0;
            break;
        }
    };



    this->scheduleUpdate();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    

    auto GoBack = MenuItemImage::create("Goback.png", "Goback.png", CC_CALLBACK_1(Level2::GoBackToLevelsScene, this));
    GoBack->setPosition(Point(visibleSize2.width / 8, (visibleSize2.height / 10) * 9));

    auto menu1 = Menu::create(GoBack, NULL);


    menu1->setPosition(Point::ZERO);
    this->addChild(menu1);

   
    return true;
}


void Level2::update(float dt) {
    if(myPlayer->getPositionX()>PosPlay2.x && nX < 0){
        myPlayer->setPositionX(myPlayer->getPosition().x + nX );
    }
    else if(nX>0 && finish2.x <= FloorSprite->getPosition().x || nX<0 && start2.x >= FloorSprite->getPosition().x){
        FloorSprite->setPositionX(FloorSprite->getPositionX() - nX);
        Mob->setPositionX(Mob->getPositionX() - nX);
        WinPoint->setPositionX(WinPoint->getPositionX() - nX);
        Bob->setPositionX(Bob->getPositionX() - nX);
        Bob2->setPositionX(Bob2->getPositionX() - nX);
        Hamer->setPositionX(Hamer->getPositionX() - nX);
        //Hamer2->setPositionX(Hamer2->getPositionX() - nX);
        fire->setPositionX(fire->getPositionX() - nX);
        Triagle_3->setPositionX(Triagle_3->getPositionX() - nX);
       
        //TR->setPositionX(TR->getPositionX() - nX);


    }else if(finish2.x >= FloorSprite->getPosition().x){
        myPlayer->setPositionX(myPlayer->getPosition().x + nX );
    }
    if (nY >0 and myPlayer->getPositionY()<PosPlay2.y) {
        myPlayer->runAction(JumpTo::create(0.5, Point(myPlayer->getPositionX(), myPlayer->getPositionY()), 30, 1));
        CocosDenshion::SimpleAudioEngine::getInstance()->
        playEffect("Jump.mp3");
    }

}

bool Level2::onContactBegin(PhysicsContact& contact)
{

    nX=0;
    nY=0;
    if (myPlayer->getPositionX()>PosPlay21.x ) {
        
        CocosDenshion::SimpleAudioEngine::getInstance()->
        playEffect("WIN.mp3");
        Tentative2=0;
        auto scene = LevelsScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

    }else{
        Tentative2++;
        auto scene = Level2::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

        
    
    }
    return true;
}
void Level2::GoBackToLevelsScene(cocos2d::Ref* sender) {
    nX=0;
    nY=0;
    Tentative2=0;
    auto scene = LevelsScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}
