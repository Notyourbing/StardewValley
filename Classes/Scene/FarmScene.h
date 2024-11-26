#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "../Player/Player.h"
#include "./Map/TileMap.h"

class Farm : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Farm);

private:
	// 记录当前按下的键
	std::set<cocos2d::EventKeyboard::KeyCode> keysPressed;

	bool isCollidingWithTile(const Vec2& position) const;

	// 初始化地图图层
	void initLayers();

	// 初始化瓦片节点
	void initTileNodes();

	// 创建瓦片节点
	std::shared_ptr<TileNode> createTileNode(const std::string& layerName, const cocos2d::Vec2& position);


	// 初始化键盘监听器
	void initKeyboardListener();

	// 根据按下的键来更新玩家和地图移动的方向
	void updateMovement();

<<<<<<< HEAD
	Vec2 worldToTileCoord(const Vec2& worldPosition) const;

	// 地图对象
	cocos2d::TMXTiledMap* tmxMap;
	// 背景层
	cocos2d::TMXLayer* backgroundLayer;
	// 碰撞层
	cocos2d::TMXLayer* collisionLayer=nullptr;
	// 交互层
	cocos2d::TMXLayer* interactiveLayer;
	// 瓦片节点集合
	std::vector<std::shared_ptr<TileNode>> tileNodes;
	// 定义 houses 成员变量
	std::vector<House*> houses; 
=======
	// 初始化鼠标监听器
	void initMouseListener();
>>>>>>> origin/master
};

#endif