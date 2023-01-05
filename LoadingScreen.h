
#ifndef __LOADING_SCREEN_H__
#define __LOADING_SCREEN__

#include "cocos2d.h"

class LoadingScreen : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();



    // implement the "static create()" method manually
    CREATE_FUNC(LoadingScreen);
private:
    void GoToMenuScene(float dt); //doubt time

};

#endif // __LOADING_SCREEN_H__

