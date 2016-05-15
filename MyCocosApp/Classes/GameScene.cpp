//
//  Menu.cpp
//  MyCocosApp
//
//  Created by 吉田光 on 2016/04/10日.
//
//

#include "GameScene.h"
#include "MainMenuScene.h"
#include "SushiSprite.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //music
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("PLAY.mp3");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("PLAY.mp3", true);

    
    //for set a half size of sushi image.
    makeHalfSizeOfSprite();
    
    //add background color with gradient
    auto Gbg = LayerGradient::create(Color4B::ORANGE, Color4B::BLACK);
    this->addChild(Gbg);
    
    //Touch setting
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    auto dip = Director::getInstance()->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, this);
    listener->setEnabled(true);
    
    //copyright
    auto label2 = Label::createWithTTF("@Jinja Games", "fonts/Marker Felt.ttf", 6);
    label2->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + label2->getContentSize().height/2));
    this->addChild(label2, 1);
    
    //Score and Miss counter on HUD
    setStatus();
    
    //make 10 sushis
    makeSushis();
    
    //init keyword
    setKeyword();
    
    //change keyword at 5 second intervel
    this->schedule(schedule_selector(GameScene::update), 5.0f);
    
    //add sushi on table at 0.9f second interval
    this->schedule(schedule_selector(GameScene::addsushi), 0.9f);
    
    return true;
}

void GameScene::GoToMainMenuScene(float dt)
{
    
    Scene *scene = MainMenuScene::createScene();
    // 0.5秒かけてホワイトアウトしてタイトルに移動する
    TransitionFade* fade = TransitionFade::create(0.5f, scene, Color3B::WHITE);
    
    //GameSceneを破棄してMainMenuSceneに遷移する
    Director::getInstance()->replaceScene(fade);
    
    //stop play music
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();

}

void GameScene::makeHalfSizeOfSprite(void)
{
    auto sushi0 = Sprite::create("Sushis/1.png");
    half = sushi0->getContentSize();
    half.width /= 4;
    half.height /= 4;
}

void GameScene::makeSushis()
{
    for (int i=0 ; i<10 ; i++) {
        SushiSprite* sushi = new SushiSprite();
        sushi->initWithFile("Sushis/" + strList[i] + ".png");
        sushi->autorelease();
        sushi->setContentSize(Size(half.width, half.height));
        sushi->setPosition(Vec2(origin.x + visibleSize.width - half.width, origin.y + visibleSize.height - half.height));
        sushi->setScale(0.25f);
        sushi->setTag(i);
        sushis.insert(i, sushi);
    }
}

void GameScene::setKeyword(void)
{
    keyword = Label::createWithSystemFont(strList[getrandomNum()], "fonts/Marker Felt.ttf", 18);
    keyword->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - keyword->getContentSize().height));
    this->addChild(keyword, 1);

}


void GameScene::update(float delta)
{
    //定期的に呼び出す
    keyword->setString(strList[getrandomNum()]);
}

int GameScene::getrandomNum(void)
{
     return arc4random()%10;
}

void GameScene::setStatus(void)
{
    text = Label::createWithSystemFont("Score: " + StringUtils::toString(score), "fonts/Marker Felt.ttf", 12);
    text->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height/2));
    this->addChild(text);
    
    text2 = Label::createWithSystemFont("Miss : " + StringUtils::toString(mistake), "fonts/Marker Felt.ttf", 12);
    text2->setPosition(Vec2(origin.x + visibleSize.width/2,
                           origin.y + visibleSize.height/2 - 20));
    this->addChild(text2);
}

void GameScene::updateStatus(void)
{
    text->setString("Score: " + StringUtils::toString(score));
    text2->setString("Miss: " + StringUtils::toString(mistake));
}

void GameScene::addsushi(float delta)
{
    auto moveTo2 = MoveTo::create(3.0f, Vec2(origin.x + visibleSize.width - half.width, origin.y + half.height));
    auto moveTo3 = MoveTo::create(1.5f, Vec2(origin.x + 6, origin.y + half.height));
    auto moveTo4 = MoveTo::create(3.0f, Vec2(origin.x + 6, origin.y + visibleSize.height - half.height - 50));
    auto moveTo5 = MoveTo::create(1.5f, Vec2(origin.x + visibleSize.width - half.width, origin.y + visibleSize.height - half.height - 50));
    auto sequence = Sequence::create(moveTo2, moveTo3, moveTo4, moveTo5, nullptr);
    repeatForever = RepeatForever::create(sequence);
    
    if(sushicount == 10) return;
    this->addChild(sushis.at(sushicount));
    sushis.at(sushicount)->runAction(repeatForever);
    
    sushicount++;
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    //タッチが始まった時の処理
    for(int i=0 ; i<10 ; i++) {
        //when touch point contains sushi
        if(sushis.at(i)->isTouchPoint(touch->getLocation() ) ){
            //Hiting
            if( keyword->getString() == strList[ sushis.at(i)->getTag() ] ) {
                score++;
                updateStatus();
                keyword->setString(strList[getrandomNum()]);
                break;
            }
            //Coming off
            else {
                mistake++;
                updateStatus();
                break;
            }
        }
    }
    
    //player not be able to touch, when player win or lost.
    //and go to MainMenu

    //Game Clear
    if(score == 10) {
        listener->setEnabled(false);
        
        auto label2 = Label::createWithTTF("KUDOS !!", "fonts/Marker Felt.ttf", 20);
        label2->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + 60));
        this->addChild(label2, 1);
        
        this->scheduleOnce(schedule_selector(GameScene::GoToMainMenuScene), 5);

    }
    
    //Game Over
    if(mistake == 3) {
        listener->setEnabled(false);
        
        auto label3 = Label::createWithTTF("GAME OVER ...", "fonts/Marker Felt.ttf", 20);
        label3->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + 60));
        this->addChild(label3, 1);
        
        this->scheduleOnce(schedule_selector(GameScene::GoToMainMenuScene), 5);

    }
    return true;
}