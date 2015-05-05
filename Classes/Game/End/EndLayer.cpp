//
//  EndLayer.cpp
//  poputar
//
//  Created by allen on 15-4-12.
//
//

#include "EndLayer.h"


EndLayer* EndLayer::createEndLayer(){
    EndLayer *item = new EndLayer();
    if(item && item->initWithColor(Color4B(0, 0, 0, 120))){
        item->autorelease();
        item->setPosition(0,0);
        item->loadFrame();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}

void EndLayer::loadFrame(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto temp = Sprite::create("game/end/wujiaoxing.png");

    int xxCount = 3;
    float xxSide = temp->getContentSize().width;
    float xxSpace = 10;
    float startX = visibleSize.width/2-(xxCount/2) *(xxSide + xxSpace);

    for (int i=0; i<xxCount; i++) {
        auto spriteXX = ui::Scale9Sprite::create("game/end/wujiaoxing.png");
        spriteXX->setPreferredSize(Size(xxSide,xxSide));
        float x = startX+i*(xxSide+xxSpace);
        spriteXX->setPosition(Vec2(x,200));
        this->addChild(spriteXX);
    }
    
    std::string text ="弹的真棒";
    auto label = Label::createWithTTF(text, "fonts/yuanti.ttf", 30);
    label->setPosition(visibleSize.width/2,150);
    this->addChild(label);
    
    //重新开始
    ui::Button *restartBtn = ui::Button::create("game/end/restartBtnNormal.png","game/end/restartBtnSelect.png");
    restartBtn->setPosition(Vec2(visibleSize.width/2-restartBtn->getContentSize().width/2-20,50));
    restartBtn->addClickEventListener(CC_CALLBACK_1(EndLayer::restartController, this));
    this->addChild(restartBtn);
    
    //继续游戏
    ui::Button *goOnBtn = ui::Button::create("game/end/goonBtnNormal.png","game/end/goonBtnSelect.png");
    goOnBtn->setPosition(Vec2(visibleSize.width/2+restartBtn->getContentSize().width/2+20,50));
    goOnBtn->addClickEventListener(CC_CALLBACK_1(EndLayer::nextController, this));
    this->addChild(goOnBtn);
}

void EndLayer::restartController(cocos2d::Ref *ref){
    //重新闯关
    _delegate->endRestartCallback();
}

void EndLayer::nextController(cocos2d::Ref *ref){
    //继续下一关
    _delegate->endNextCallback();
}

void EndLayer::setDelegate(EndLayerDelegate *delegate){
    _delegate = delegate;
}