#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "../Player/Player.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Farm);

private:
	// 初始化键盘监听器
	void initKeyboardListener();

	// 获取玩家的新位置，更新地图偏移量
	void updateMapPosition();
};

#endif