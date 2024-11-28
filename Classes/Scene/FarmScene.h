#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Player/Player.h"
#include "../Map/FarmMap.h"
#include "../Npc/Npc.h"
#include "../Map/TileMap.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// <<<<<<< HEAD
	// =======
	//该地图上所有npc
	std::vector<Npc*> npcs;

	void showDialogue(Npc* npc);  // 用来显示对话框的方法

	bool isCollidingWithTile(const Vec2& position) const;

	// 初始化地图图层
	void initLayers();

	// 初始化瓦片节点
	void initTileNodes();

	// 创建瓦片节点
	std::shared_ptr<TileNode> createTileNode(const std::string& layerName, const cocos2d::Vec2& position);

	// >>>>>>> 75f5d433ca3bd3759a894911816bae485e86db27
	CREATE_FUNC(Farm);

	bool isDialogueVisible = false;

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