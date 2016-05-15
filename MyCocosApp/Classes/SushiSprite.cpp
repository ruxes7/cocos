//
//  SushiSprite.cpp
//  MyCocosApp
//
//  Created by 吉田光 on 2016/04/09土.
//
//

#include "SushiSprite.h"

using namespace cocos2d;

SushiSprite::SushiSprite()
{
}

/**
 *  スプライトの範囲を取得
 *
 *  @return Rect
 */


Rect SushiSprite::getRect()
{
    // スプライトの座標（画像の真ん中の座標のこと）
    Vec2 point = this->getPosition();
    
    // スプライトの幅と高さ
    int w = this->getContentSize().width + 5;
    int h = this->getContentSize().height + 5;
    
    // スプライトの範囲を返す
    return Rect(point.x-(w/2), point.y-(h/2), w, h);
}

/**
 *  引数の座標がスプライトの範囲内かどうかを返す（タッチ時の座標情報を渡す）
 *
 *  @param point 座標ポイント
 *
 *  @return ture or false
 */
bool SushiSprite::isTouchPoint(Vec2 point)
{
    return this->getRect().containsPoint(point);
}
