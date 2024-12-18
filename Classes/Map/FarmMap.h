#ifndef __FARMMAP_H__
#define __FARMMAP_H__
#include "cocos2d.h"
#include "Crop.h"
#include "TileNode.h"
#include "AnimalManager.h"
#include "SceneMap.h"
#include "../Npc/Npc.h"
#include "../Bag/Bag.h"
#include "../Tool/Kettle.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"
#include <string>
#include <memory>
#include <vector>

// 农场地图类
class FarmMap : public SceneMap {
public:
	// 获取单例实例
	static FarmMap* getInstance();

	// 初始化地图
	bool init(const std::string& tmxFile) override;

	//随地图创建npc
	bool npcInit(const cocos2d::Vec2& position, Npc* npc);

	// 更新地图位置
	void moveMapByDirection(const cocos2d::Vec2& direction);

	// 碰撞检测：检查给定位置是否是障碍物
	bool isCollidable(const cocos2d::Vec2& position) const;

	// 用于鼠标左键与农场的交互逻辑
	void interactWithMap() override;

	// 地图时间更新
	void mapUpdateByTime();
private:
	// 构造函数和析构函数私有化
	FarmMap();
	~FarmMap();

	// 禁用拷贝构造和赋值操作
	FarmMap(const FarmMap&) = delete;
	FarmMap& operator=(const FarmMap&) = delete;

	// 单例实例
	static FarmMap* instance;

	// 用来存储TMX地图的各个层
	cocos2d::TMXLayer* grassLayer;
	cocos2d::TMXLayer* soilLayer;
	cocos2d::TMXLayer* obstacleLayer;
	cocos2d::TMXLayer* moldLayer;
	cocos2d::TMXLayer* waterLayer;
	cocos2d::TMXLayer* stoneLayer;

	// 动物对象
	AnimalManager* animalManager;

	// 与土壤块的交互
	void interactWithSoil(std::string itemName, const int& x, const int& y);
};
#endif