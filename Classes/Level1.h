#ifndef _LEVEL_1__H_
#define _LEVEL_1__H_

#include "cocos2d.h"


class Level1 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback


    // implement the "static create()" method manually
    CREATE_FUNC(Level1);
    // declaration d'un sprit
    cocos2d::Sprite* FloorSprite;
    cocos2d::Sprite* backgroundSprite;
    cocos2d::Sprite* myPlayer;
    cocos2d::Sprite* myPlayer2;
    cocos2d::Sprite* WreckBall;
    cocos2d::Sprite* wreckballhold;
    cocos2d::Sprite* WinPoint;   
    cocos2d::Sprite* spike1;
    cocos2d::Sprite* spike2;
    cocos2d::Sprite* ball;
    cocos2d::Sprite* ball2;
    cocos2d::Sprite* Triangle_2;
    cocos2d::Sprite* Triangle2_2;
   
   
    

    void update(float dt);
    bool isTouching;
    float touchPosition;
    cocos2d::EventKeyboard::KeyCode KeyClick;

   
    void setPhysicsWorld(cocos2d::PhysicsWorld* world) {
        mWorld = world;
        mWorld->setGravity(cocos2d::Vect(0, 0));
    }
    bool onContactBegin(cocos2d::PhysicsContact& contact);
private:
    cocos2d::PhysicsWorld* mWorld;
   
    /*void GoBackToLevelsScene(cocos2d::Ref* pSender);*/
     void GoBackToLevelsScene(cocos2d::Ref* pSender);

};

#endif // _LEVEL_1__H_
