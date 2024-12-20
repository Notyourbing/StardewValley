/****************************************************************
 * File Function: 技能树在场景中展示类，用于实现技能树的显示与更新
 * Author:        韦瑾钰
 ****************************************************************/
#ifndef __SKILLTREEUI_H__
#define __SKILLTREEUI_H__

#include "cocos2d.h"

class SkillTreeUI : public cocos2d::Layer {
public:
    // 获取单例实例
    static SkillTreeUI* getInstance();

    // 初始化
    virtual bool init();

    // 打开UI界面
    void openSkillUI();

    // 是否打开
    static bool getOpenStatus() { return isOpen; }

    // open状态设置
    static void setOpenStatus(bool status) { isOpen = status; }

    //更新显示状态
    void updateUI();

private:
    // 静态实例
    static SkillTreeUI* instance;

    // 框中具体实现
    void setupUI();

    // 析构函数，instance不会是野指针
    ~SkillTreeUI();

    // 关闭按钮的回调函数
    void closeCallback(cocos2d::EventListenerMouse* listener);

    // 是否打开
    static bool isOpen;
};
#endif __SKILLTREEUI_H__