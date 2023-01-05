#ifndef __LEVEL1_SCENE_H__
#define __LEVEL1_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class Level3 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
   

    // implement the "static create()" method manually
    CREATE_FUNC(Level3);
    // declaration d'un sprit
    cocos2d::Sprite *FloorSprite;
    cocos2d::Sprite *backgroundSprite;
    cocos2d::Sprite *myPlayer;
    cocos2d::Sprite *myPlayer2;
    cocos2d::Sprite *Mob;
    cocos2d::Sprite *WinPoint;
    cocos2d::Sprite *Bob;
    cocos2d::Sprite *Hamer;
    cocos2d::Sprite *Triagle_3;
    cocos2d::Sprite *Triagle_32;
    cocos2d::Sprite *Hamer1;
    cocos2d::Sprite *TR;

    
    void update(float dt);
    bool isTouching;
    float touchPosition;
    cocos2d::EventKeyboard::KeyCode KeyClick;
 
    void setPhysicsWorld(cocos2d::PhysicsWorld* world){
        mWorld = world;
        mWorld->setGravity(cocos2d::Vect(0, 0));
        }
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void GoBackToLevelsScene(cocos2d::Ref* pSender);

private:
    cocos2d::PhysicsWorld* mWorld;
    
};

#endif // __LEVEL1_SCENE_H__

