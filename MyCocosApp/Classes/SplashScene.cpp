//
//  Menu.cpp
//  MyCocosApp
//
//  Created by 吉田光 on 2016/04/10日.
//
//

#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;


Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //get a Maximum width and Height of Display
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //set a BackGroundCorlor
    auto bg = LayerColor::create(Color4B::WHITE);
    this->addChild(bg);
    
    //set a Splash Screen Image
    auto backgroundSprite = Sprite::create("JinjaGames.png");
    backgroundSprite->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(backgroundSprite);
    
    //Go to MainMenu at 2 seconds
    this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);
    
    return true;
}

void SplashScene::GoToMainMenuScene(float dt)
{
    auto scene = MainMenuScene::createScene();
    //0.5秒かけてホワイトアウトしてSplashSceneを破棄してMainMenuSceneに遷移する
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}