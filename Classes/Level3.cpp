#include "Level3.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "MyBodyParser.h"
#include "LevelsScene.h"
#include "Definitions.h"

USING_NS_CC;
bool pressed3;
int DirX = 0 ;
int DirY = 0 ;
int Tentative3;

cocos2d::EventKeyboard::KeyCode pressed3Key;
Scene* Level3::createScene(){
    
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = Level3::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->getPhysicsWorld()->setGravity(Vec2(0,-40));
    
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Level3.cpp\n");

}
auto visibleSize33 = Director::getInstance()->getVisibleSize();
Vec2 origin3 = Director::getInstance()->getVisibleOrigin();

// on "init" you need to initialize your instance
Point start3;
Point finish3;
Point PosPlay3;
Point PosPlay31;
bool Level3::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    
    this->scheduleUpdate();
    
    auto visibleSize3 = Director::getInstance()->getVisibleSize();
    Vec2 origin3 = Director::getInstance()->getVisibleOrigin();
    /////
    ///
    auto label = Label::createWithTTF("Tentative :"+std::to_string(Tentative3), "fonts/pico.ttf", 12);
    if (label == nullptr)
    {
        problemLoading("'fonts/pico.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Point(origin3.x + visibleSize3.width/2,
                                 origin3.y + visibleSize3.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    ///
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize3,PHYSICSBODY_MATERIAL_DEFAULT);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point((visibleSize3.width)/2 + origin3.x, (visibleSize3.height / 2 ) +origin3.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    auto GoBack = MenuItemImage::create("Goback.png", "Goback.png", CC_CALLBACK_1(Level3::GoBackToLevelsScene, this));
    GoBack->setPosition(Point(visibleSize3.width / 8, (visibleSize3.height / 10) * 9));

    auto menu1 = Menu::create(GoBack, NULL);


    menu1->setPosition(Point::ZERO);
    this->addChild(menu1);
    ////
    backgroundSprite=Sprite::create("Backgroud1.jpg");
    Mob = Sprite::create("trapTYPE1.png");
    WinPoint = Sprite::create("WinPoint.png");
    
    auto actionTRAP=RotateBy::create(0.1, 50);
    
    Mob->runAction(RepeatForever::create(actionTRAP));
    
    Mob->setPosition(Point((1.3*visibleSize3.width), (visibleSize3.height / 3 ) +origin3.y));
    auto actionBACK= ScaleBy::create(0,0.35);
    auto actionBACK1= ScaleBy::create(0, 0.3);
    backgroundSprite->setPosition(Point(0,(visibleSize3.height / 2 )));
    // mob setup physique :
    auto Mob_Body = PhysicsBody::createCircle(Mob->getContentSize().width/2);
    Mob_Body->setContactTestBitmask(true);
    Mob_Body->setDynamic(true);
    Mob->setPhysicsBody(Mob_Body);
    // winpoint:
    WinPoint->setPosition(Point((3.05*visibleSize3.width), (visibleSize3.height / 3 ) +origin3.y));
    WinPoint->runAction(ScaleBy::create(0,0.4));
    auto bodyWP=PhysicsBody::createCircle(WinPoint->getContentSize().width/2);
    bodyWP->setContactTestBitmask(true);
    bodyWP->setDynamic(false);
    WinPoint->setPhysicsBody(bodyWP);
    // </winpont>
    //---
    Hamer = Sprite::create("Hamer.png");
    Hamer->setPosition(Point((2*visibleSize3.width), (visibleSize3.height / 2.62 ) +origin3.y));
    Hamer->runAction(ScaleBy::create(0,0.4));
    Hamer->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1,Point(0,100)),MoveBy::create(1,Point(0,-100)),NULL)));
    auto Hamer_body =PhysicsBody::createBox(Hamer->getContentSize()/1 , PhysicsMaterial(0,0,1));
    Hamer_body->setDynamic(false);
    Hamer_body->setContactTestBitmask(true);
    Hamer->setPhysicsBody(Hamer_body);
    this->addChild(Hamer);
    //-- hamer 1
    Hamer1 = Sprite::create("Hamer.png");
    Hamer1->setPosition(Point((2.18*visibleSize3.width), (visibleSize3.height / 2.62 ) +origin3.y));
    Hamer1->runAction(ScaleBy::create(0,0.4));
    Hamer1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.3,Point(0,80)),MoveBy::create(0.45,Point(0,-80)),NULL)));
    auto Hamer1_body =PhysicsBody::createBox(Hamer1->getContentSize()/1 , PhysicsMaterial(0,0,1));
    Hamer1_body->setDynamic(false);
    Hamer1_body->setContactTestBitmask(true);
    Hamer1->setPhysicsBody(Hamer1_body);
    this->addChild(Hamer1);
    //</Hamer>
    Bob = Sprite::create("MOB.png");
    Bob->setPosition(Point((0.64*visibleSize3.width), (visibleSize3.height / 3.5 ) +origin3.y));
    Bob->runAction(ScaleBy::create(0,0.65));
    auto Bobody =PhysicsBody::createBox(Bob->getContentSize()/1.25 , PhysicsMaterial(0,0,1));
    Bobody->setDynamic(false);
    Bobody->setContactTestBitmask(true);
    
    Bob->setPhysicsBody(Bobody);
    Bob->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1,Point(55,0)),MoveBy::create(1,Point(-55,0)),NULL)));
    
    
    this->addChild(Bob);
    
    // trigle a 3 :
    Triagle_3 = Sprite::create("Triagle3.png");
    Triagle_3->setPosition(Point((1.65*visibleSize3.width), (visibleSize3.height / 3.5 ) +origin3.y));
    Triagle_3->runAction(ScaleBy::create(0,0.35));
    auto Triangle3_Body =PhysicsBody::createBox(Triagle_3->getContentSize()/1.25 , PhysicsMaterial(0,0,1));
    Triangle3_Body->setDynamic(false);
    Triangle3_Body->setContactTestBitmask(true);
    Triagle_3->setPhysicsBody(Triangle3_Body);
    this->addChild(Triagle_3);
    // - - - - - - - - -  -
    FloorSprite = Sprite::create
    ("flor1.png");
    FloorSprite->setPosition(Point((1.7*visibleSize3.width) ,  (visibleSize3.height / 8.3 ) ));
    auto action1= ScaleBy::create(0, 0.55);
    backgroundSprite->runAction(actionBACK);
    FloorSprite->runAction(action1);
    auto body1 = PhysicsBody::createBox(FloorSprite->getContentSize()/1.1 , PHYSICSBODY_MATERIAL_DEFAULT);
    body1->setContactTestBitmask(false);
    body1->setDynamic(false);
    
    Triagle_32 = Sprite::create("Triagle3.png");
    Triagle_32->setPosition(Point((2.7*visibleSize3.width),  (visibleSize3.height / 3.5 ) +origin3.y) );
    Triagle_32->runAction(ScaleBy::create(0,0.35));
    auto Triangle32_Body =PhysicsBody::createBox(Triagle_3->getContentSize()/1.25 , PhysicsMaterial(0,0,1));
    Triangle32_Body->setDynamic(false);
    Triangle32_Body->setContactTestBitmask(true);
    Triagle_32->setPhysicsBody(Triangle32_Body);
    this->addChild(Triagle_32);

    FloorSprite->setPhysicsBody(body1);
    start3=Point((1.7*visibleSize3.width) ,  (visibleSize3.height / 3 ) +origin3.y);
    finish3=Point((1.7*visibleSize3.width) - 900 ,  (visibleSize3.height / 3 ) +origin3.y);
    PosPlay3=Vec2(visibleSize3.width/4.5 + origin3.x, visibleSize3.height/3.42 + origin3.y);
    PosPlay31=Vec2(visibleSize3.width/1.3 + origin3.x, visibleSize3.height/3.42 + origin3.y);
    
    myPlayer = Sprite::create("Player.png");
    myPlayer->setPosition(Point(visibleSize3.width/4.5 + origin3.x, visibleSize3.width/5 + origin3.y));
    auto body = PhysicsBody::createBox(myPlayer->getContentSize()/1.3 ,PhysicsMaterial(1000,0,0));
    body->setContactTestBitmask(true);
    body->setDynamic(true);
    myPlayer->setPhysicsBody(body);
    
    this->addChild(myPlayer);
    this->addChild(backgroundSprite,-10);
    this->addChild(Mob,10);
    this->addChild(FloorSprite, -1);
    this->addChild(WinPoint,10);
    
    
     
    auto action= ScaleBy::create(0, 0.15);
    myPlayer->runAction(action);
    Mob->runAction(actionBACK1);
    
    
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin =CC_CALLBACK_1(Level3::onContactBegin, this);
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
            DirY += 4.0f;
            break;
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            DirX -= 4.0f;
            break;
        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            DirY -= 4.0f;
            break;
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
           
            DirX += 4.0f;
            break;
        }
    };

    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            DirY =0;
            break;
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            
            DirX =0;
            break;
        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            DirY =0;
            break;
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            
            DirX =0;
            break;
        }
    };

    

    this->scheduleUpdate();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
   
    return true;
}


void Level3::update(float dt){
    if(myPlayer->getPositionX()>PosPlay3.x && DirX < 0){
        myPlayer->setPositionX(myPlayer->getPosition().x + DirX );
    }
    else if(DirX>0 && finish3.x <= FloorSprite->getPosition().x || DirX<0 && start3.x >= FloorSprite->getPosition().x){
    FloorSprite->setPositionX(FloorSprite->getPositionX() - DirX);
    Mob->setPositionX(Mob->getPositionX() - DirX);
    WinPoint->setPositionX(WinPoint->getPositionX() - DirX);
    Bob->setPositionX(Bob->getPositionX() - DirX);
    Hamer->setPositionX(Hamer->getPositionX() - DirX);
    Triagle_3->setPositionX(Triagle_3->getPositionX() - DirX);
    Triagle_32->setPositionX(Triagle_32->getPositionX() - DirX);
    Hamer1->setPositionX(Hamer1->getPositionX() - DirX);


        
    }else if(finish3.x >= FloorSprite->getPosition().x){
        myPlayer->setPositionX(myPlayer->getPosition().x + DirX );
    }
    if (DirY >0 and myPlayer->getPositionY()<PosPlay3.y) {
        CocosDenshion::SimpleAudioEngine::getInstance()->
        playEffect("Jump.mp3");
        myPlayer->runAction(JumpTo::create(0.5, Point(myPlayer->getPositionX(), myPlayer->getPositionY()), 30, 1));
    }
    
}
// le contact
bool Level3::onContactBegin(PhysicsContact& contact)
{
    DirX=0;
    DirY=0;
    
    if (myPlayer->getPositionX()>PosPlay31.x ) {
        CocosDenshion::SimpleAudioEngine::getInstance()->
        playEffect("WIN.mp3");
        Tentative3=0;
        auto scene = HelloWorld::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

    }else{
        
        Tentative3++;
        auto scene = Level3::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
    
    
return true;
}

void Level3::GoBackToLevelsScene(cocos2d::Ref* sender) {
    DirX=0;
    DirY=0;
    Tentative3=0;
    auto scene = LevelsScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
