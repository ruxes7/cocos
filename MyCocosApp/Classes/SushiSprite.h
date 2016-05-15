//
//  SushiSprite.hpp
//  MyCocosApp
//
//  Created by 吉田光 on 2016/04/09土.
//
//

#ifndef __SUSHI_SPRITE__
#define __SUSHI_SPRITE__

#include "cocos2d.h"

class SushiSprite : public cocos2d::Sprite
{
public:
    
    SushiSprite();
    
    cocos2d::Rect getRect();
    bool isTouchPoint(cocos2d::Point);
};
#endif /* SushiSprite_hpp */