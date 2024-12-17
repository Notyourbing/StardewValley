#pragma once
#include "cocos2d.h"

class SkillTreeUI : public cocos2d::Layer {
public:
    // 获取单例实例
    static SkillTreeUI* getInstance();

    // 初始化
    virtual bool init();

    // 是否打开
    static bool isOpen;

    // 打开UI界面
    void openSkillUI();

private:
    // 静态实例
    static SkillTreeUI* instance;

    // 框中具体实现
    void setupUI();

    // 析构函数，instance不会是野指针
    ~SkillTreeUI();

    // 关闭按钮的回调函数
    void closeCallback(cocos2d::EventListenerMouse* listener);
};
