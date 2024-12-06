#ifndef __DIALOGUE_BOX_H__
#define __DIALOGUE_BOX_H__

#include "cocos2d.h"
#include "../Npc/Npc.h"
#include "ui/CocosGUI.h"
#include "../Player/Player.h"
#include "../Map/FarmMap.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"

class DialogueBox : public cocos2d::Node {
public:
    // 静态创建函数
    static DialogueBox* create(Npc* npc);

    // 初始化函数
    bool init(Npc* npc);

    // 显示对话框的初始内容
    void showInitialDialogue();

    // 显示对话选项
    void showDialogueOptions(EventListenerMouse* lastListener);

    // 更新对话框内容
    void updateDialogueAfterOptionSelected(int optionIndex);

    // 关闭对话框
    void closeDialogue(EventListenerMouse* lastListener);

    // 用于鼠标事件监听
    void initMouseListener();

    // 获取下个节日
    std::string getNextFestival();

    static bool isDialogueVisible;  // 对话框是否显示

private:
    Npc* npc;                                           // 当前与之对话的 NPC
    cocos2d::Label* dialogueLabel;                      //对话内容
    cocos2d::Label* nameLabel;                          //npc名字
    cocos2d::Sprite* dialogueBackground;                //对话背景
    cocos2d::Sprite* npcTalkImage;                      //npc立绘
    std::vector<cocos2d::ui::Button*> optionButtons;    // 存储对话选项按钮
    cocos2d::EventListenerMouse* mouseListener;         // 用于处理点击事件
};

#endif // __DIALOGUE_BOX_H__
