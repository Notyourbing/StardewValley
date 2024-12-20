/****************************************************************
 * File Function: 实现农场场景类，继承自Scene，是游戏的主要场景
 *				  农场中有npc，玩家可以耕种，养殖，钓鱼，砍树，交易等。
 * Author:        赵卓冰
 ****************************************************************/
#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Player/Player.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"
#include "../Date/DateManage.h"

// 农场场景类
class Farm : public cocos2d::Scene {
public:
	// 创建场景，静态函数
	static cocos2d::Scene* createScene();

	// 获取地图上所有的npc
	static std::vector<Npc*> getNpcs();

	// 根据人物的位置自动从农场场景切换到其他四个场景
	void changeSceneAuto();

	// 析构函数，负责npcs的内存管理
	~Farm();

	//该地图上所有npc, 静态成员变量
	static std::vector<Npc*> npcs;
private:


	// 农场场景的初始化函数
	bool init();

	// 关闭按钮的回调函数
	void closeButtonClicked(Ref* pSender);

	// 创建场景，静态函数 create()
	CREATE_FUNC(Farm);
};

#endif