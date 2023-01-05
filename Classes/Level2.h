#ifndef _LEVEL_2__H_
#define _LEVEL_2__H_

#include "cocos2d.h"


class Level2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback


    // implement the "static create()" method manually
    CREATE_FUNC(Level2);
    // declaration d'un sprit
    cocos2d::Sprite* FloorSprite;
    cocos2d::Sprite* backgroundSprite;
    cocos2d::Sprite* myPlayer;
    cocos2d::Sprite* myPlayer2;
    cocos2d::Sprite* Mob;
    cocos2d::Sprite* fire;
    cocos2d::Sprite* WinPoint;
    cocos2d::Sprite* Bob;
    cocos2d::Sprite* Bob2;
    cocos2d::Sprite* Hamer;
    cocos2d::Sprite* Triagle_3;
    cocos2d::Sprite* Hamer2;
    cocos2d::Sprite* TR;
    

    void update(float dt);
    bool isTouching;
    float touchPosition;
    cocos2d::EventKeyboard::KeyCode KeyClick;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
    void setPhysicsWorld(cocos2d::PhysicsWorld* world) {
        mWorld = world;
        mWorld->setGravity(cocos2d::Vect(0, 0));
    }
    bool onContactBegin(cocos2d::PhysicsContact& contact);
private:
    cocos2d::PhysicsWorld* mWorld;
    void GoBackToLevelsScene(cocos2d::Ref* pSender);

};

#endif // _LEVEL_2__H_
