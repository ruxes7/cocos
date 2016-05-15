//
//  Menu.cpp
//  MyCocosApp
//
//  Created by 吉田光 on 2016/04/10日.
//
//

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SushiSprite.h"

class GameScene : public cocos2d::Layer
{
    
public:
    int score = 0, mistake = 0, sushicount = 0;
    //10 sushi list
    std::vector<std::string> strList =
    {
        "ANAGO", "EBI", "IKA", "INARI", "KAPPAMAKI",
        "MAGURO", "NATTOMAKI", "TAKO", "TAMAGO", "TEKKAMAKI"
    };
    cocos2d::Label* keyword;
    cocos2d::Label* text;
    cocos2d::Label* text2;
    //get a Maximum width and Height on Display
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    cocos2d::RepeatForever* repeatForever;
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    cocos2d::Size half;
    // スプライトを格納する配列
    cocos2d::Vector<SushiSprite*> sushis;
    
    // タッチ関係のイベント
    cocos2d::EventListenerTouchOneByOne* listener = cocos2d::EventListenerTouchOneByOne::create();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void GoToMainMenuScene(float dt);
    void makeHalfSizeOfSprite(void);
    void makeSushis(void);
    void setKeyword(void);
    void update(float delta);
    int getrandomNum(void);
    void setStatus(void);
    void updateStatus(void);
    void addsushi(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
