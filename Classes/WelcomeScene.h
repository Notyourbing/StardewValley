#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

class Welcome : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // 新游戏项的回调函数
    void menuNewGameCallback(cocos2d::Ref* pSender);

    // 加载游戏项的回调函数
    void menuLoadGameCallback(cocos2d::Ref* pSender);

    // 合作项的回调函数
    void menuCooperationCallback(cocos2d::Ref* pSender);

    // 退出项的回调函数
    void menuExitCallback(cocos2d::Ref* pSender);



    // implement the "static create()" method manually
    // CREATE_FUNC(Welcome);
    static Welcome* create();

};

#endif // __WELCOME_SCENE_H__
