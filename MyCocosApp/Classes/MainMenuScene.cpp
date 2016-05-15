//
//  Menu.cpp
//  MyCocosApp
//
//  Created by 吉田光 on 2016/04/10日.
//
//

#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool MainMenuScene::init()
{
    if( !Layer::init() ){
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //set a backgroundcolor
    auto Gbg = LayerGradient::create(Color4B::GREEN, Color4B::BLACK);
    this->addChild(Gbg, 0);
    
    //set a game title
    auto Title = Label::createWithTTF("Sushi Train", "fonts/Marker Felt.ttf", 24);
    Title->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - Title->getContentSize().height - 20) );
    this->addChild(Title, 2);

    //set a Logo "Jinja Games"
    auto JinjaGames = Sprite::create("JinjaGames.png");
    JinjaGames->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + JinjaGames->getContentSize().height/2 ) );
    this->addChild(JinjaGames, 2);
    
    auto underbg = LayerColor::create(Color4B::WHITE, origin.x + visibleSize.width,
                                  origin.y + JinjaGames->getContentSize().height);
    this->addChild(underbg, 1);

    // set a startButton
    auto startButton = MenuItemImage::create(
                                             "Sushis/MAGURO.png",  // 通常状態の画像
                                             "Sushis/8.png",  // 押下状態の画像
                                             CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    startButton->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    auto start = Menu::create(startButton, NULL);
    start->setPosition(Vec2::ZERO);
    this->addChild(start, 1);
    
    //set a closeButton
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
    closeItem->setContentSize( Size(closeItem->getContentSize().width * 1.5f, closeItem->getContentSize().height * 1.5f) );
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    // create menu, it's an autorelease object
    auto close = Menu::create(closeItem, NULL);
    close->setPosition(Vec2::ZERO);
    this->addChild(close, 2);
    
    return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref *pSender)
{
    auto scene = GameScene::createScene();

    // 0.5秒かけてホワイトアウトしてゲームに移動する
    TransitionFade* fade = TransitionFade::create(0.5f, scene, Color3B::WHITE);
    
    //MainMenuSceneを破棄してGameSceneに遷移する
    Director::getInstance()->replaceScene(fade);
}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}