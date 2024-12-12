#pragma once
#include "cocos2d.h"

class SkillTreeUI : public cocos2d::Layer {
public:

    static SkillTreeUI* getInstance();

    // 初始化
    virtual bool init();
    // 是否打开
    static bool isOpen;

    void openSkill();

private:
    static SkillTreeUI* instance; // 静态实例
    // 框中具体实现
    void setupUI();

    ~SkillTreeUI();

    // 关闭
    void closeCallback(cocos2d::EventListenerMouse* listener);
};
