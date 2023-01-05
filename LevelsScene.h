#ifndef __LEVELS_SCENE_H__
#define __LEVELS_SCENE_H__

#include "cocos2d.h"

class LevelsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();



    // implement the "static create()" method manually
    CREATE_FUNC(LevelsScene);
private:
    void GoToLevel1Scene(cocos2d::Ref* sender);
    void GoToLevel2Scene(cocos2d::Ref* sender);
    void GoToLevel3Scene(cocos2d::Ref* sender);
};

#endif // __LEVELS_SCENE_H__
