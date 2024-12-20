/****************************************************************
 * File Function: 实现开始场景类，继承自Scene，是游戏的第一个场景
 * Author:        赵卓冰
 ****************************************************************/
#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

class Welcome : public cocos2d::Scene {
public:
    // 静态创建场景方法
    static cocos2d::Scene* createScene();

private:
    // 初始化场景
    bool init();

    // 新游戏项的回调函数
    void menuNewGameCallback(cocos2d::Ref* pSender);

    // 加载游戏项的回调函数
    void menuLoadGameCallback(cocos2d::Ref* pSender);

    // 合作项的回调函数
    void menuCooperationCallback(cocos2d::Ref* pSender);

    // 退出项的回调函数
    void menuExitCallback(cocos2d::Ref* pSender);

    // 静态创建场景方法
    CREATE_FUNC(Welcome);
};
#endif
