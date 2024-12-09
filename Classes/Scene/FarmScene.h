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

	//该地图上所有npc，静态成员变量
	static std::vector<Npc*> npcs;

	// 析构函数，负责管理静态成员变量的内存
	~Farm();

private:
	void closeButtonClicked(Ref* pSender);
	
	// 保存玩家数据
	void savePlayer();
};

#endif