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

// 农场场景类
class Farm : public cocos2d::Scene {
public:
	// 创建场景，静态函数
	static cocos2d::Scene* createScene();

	// 创建场景，静态函数 create()
	CREATE_FUNC(Farm);

	//该地图上所有npc，静态成员变量
	static std::vector<Npc*> npcs;

	// 根据人物的位置自动从农场场景切换到其他四个场景
	void changeSceneAuto();

	// 析构函数，负责npcs的内存管理
	~Farm();
private:
	// 农场场景的初始化函数
	bool init();

	// 关闭按钮的回调函数
	void closeButtonClicked(Ref* pSender);
};

#endif