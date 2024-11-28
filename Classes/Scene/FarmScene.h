#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "../Player/Player.h"
#include "../Map/TileMap.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Farm);

private:
	// 记录当前按下的键
	std::set<cocos2d::EventKeyboard::KeyCode> keysPressed;

	// 初始化键盘监听器
	void initKeyboardListener();

	// 根据按下的键来更新玩家和地图移动的方向
	void updateMovement();

	// 初始化鼠标监听器
	void initMouseListener();
};

#endif