//
//  Menu.cpp
//  MyCocosApp
//
//  Created by 吉田光 on 2016/04/10日.
//
//

#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

class SplashScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);

    void GoToMainMenuScene(float dt);
};

#endif // __SPLASH_SCENE_H__
