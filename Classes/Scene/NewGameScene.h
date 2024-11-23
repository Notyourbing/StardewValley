#ifndef __NEW_GAME_SCENE_H__
#define __NEW_GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class NewGame : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// 实现静态create()函数
	CREATE_FUNC(NewGame);

private:
	// 保存用户输入的文本
	cocos2d::ui::TextField* nameInput;

	// 按钮回调函数
	void onOKButtonClicked(cocos2d::Ref* pSender);

	// 返回项的回调函数
	void backCallBack(cocos2d::Ref* pSender);
};

#endif