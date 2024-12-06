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
#include "../Map/Animal.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	bool init();

	CREATE_FUNC(Farm);

	//该地图上所有npc
	std::vector<Npc*> npcs;

private:

	void closeButtonClicked(Ref* pSender);

	// 初始化鼠标监听器(使用工具和打开对话框)
	void initMouseListener();

	// 存储农场中的动物
	std::vector<Animal*> animals;


};

#endif