#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Player/Player.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"
#include "../DateManage/DateManage.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	bool init();

	CREATE_FUNC(Farm);

	//该地图上所有npc
	std::vector<Npc*> npcs;

	// 显示初始对话框
	void showInitialDialogue(Npc* npc);

	// 显示对话选项
	void showDialogueOptions(Npc* npc, Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel, cocos2d::EventListenerMouse* lastListener);

	// 根据选择的选项更新对话内容
	 void updateDialogueAfterOptionSelected(Npc* npc, std::vector<ui::Button*> optionButtons, int optionIndex, Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel) ;

	// 关闭对话框和所有对话文字
	void closeDialogue(Sprite* dialogueBackground, Label* label, Sprite* npcTalkImage, Label* nameLabel, cocos2d::EventListenerMouse* lastListener);
	
	void createFestivals();

	void checkFestivalEvent();

	bool isDialogueVisible;

	void updateDate();

private:
	// 用于显示日期的标签
	cocos2d::Label* dateLabel; 

	// 记录当前按下的键
	std::set<cocos2d::EventKeyboard::KeyCode> keysPressed;

	std::vector<ui::Button*> optionButtons;  // 存储对话选项按钮

	// 初始化键盘监听器
	void initKeyboardListener();

	// 根据按下的键来更新玩家和地图移动的方向
	void updateMovement();

	// 初始化鼠标监听器
	void initMouseListener();
};

#endif