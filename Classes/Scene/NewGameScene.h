/****************************************************************
 * File Function: 实现新开始游戏场景类，继承自Scene，从开始场景会切换
 *				  本场景，玩家输入自己的游戏id
 * Author:        赵卓冰
 ****************************************************************/
#ifndef __NEW_GAME_SCENE_H__
#define __NEW_GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class NewGame : public cocos2d::Scene {
public:
	// 静态创建场景函数
	static cocos2d::Scene* createScene();

private:
	// 保存用户输入的文本
	cocos2d::ui::TextField* nameInput;

	// 按钮回调函数
	void onOKButtonClicked(cocos2d::Ref* pSender);

	// 返回项的回调函数
	void backCallBack(cocos2d::Ref* pSender);

	// 初始化
	bool init();

	// 实现静态create()函数
	CREATE_FUNC(NewGame);
};

#endif