//
//  Menu.hpp
//  MyCocosApp
//
//  Created by 吉田光 on 2016/04/10日.
//
//

#ifndef __MAIN_MENU_SCENE__
#define __MAIN_MENU_SCENE__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(MainMenuScene);
    
    void GoToGameScene(cocos2d::Ref* pSender);
};
#endif /* MainMenuScene_h */
