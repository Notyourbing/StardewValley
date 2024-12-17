#ifndef __FARMMAP_H__
#define __FARMMAP_H__

#include "cocos2d.h"
#include "Crop.h"
#include "../Npc/Npc.h"
#include "TileNode.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"
#include "AnimalManager.h"
#include "../Tool/Kettle.h"
#include <string>
#include <memory>
#include <vector>

// 农场地图类
class FarmMap : public cocos2d::Node {
public:
	// 获取单例实例
	static FarmMap* getInstance();

	// 初始化地图
	bool init(const std::string& tmxFile);

	//随地图创建npc
	bool npcInit(const cocos2d::Vec2& position, Npc* npc);

	// 更新地图位置
	void moveMapByDirection(const cocos2d::Vec2& direction);

	// 获取地图大小
	cocos2d::Size getMapSize() const;

	// 碰撞检测：检查给定位置是否是障碍物
	bool isCollidable(const cocos2d::Vec2& position) const;

	// 用于鼠标左键与农场的交互逻辑
	void interactWithFarmMap();

	// 地图停止移动
	void stopMoving();

	// 瓦片地图对象
	cocos2d::TMXTiledMap* map;
	
	//获取当前位置地图的类
	TileNode* getTileNode(int x, int y);

	// 地图时间更新
	void farmMapTimeUpdate();
private:

	// 构造函数和析构函数私有化
	FarmMap();
	~FarmMap();

	// 禁用拷贝构造和赋值操作
	FarmMap(const FarmMap&) = delete;
	FarmMap& operator=(const FarmMap&) = delete;

	// 地图当前的偏移位置
	cocos2d::Vec2 currentPosition;

	// 地图的偏移速度
	cocos2d::Vec2 velocity;

	// 单例实例
	static FarmMap* instance;

	// 存储地图上每个节点的类
	TileNode* mapTileNode[FARMMAP_WIDTH][FARMMAP_HEIGHT];

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

	// 与石头块的交互
	void interactWithStone(std::string itemName, const int& x, const int& y);

	// 与草地的交互
	void interactWithGrass(std::string itemName, const int& x, const int& y);

	// 与水池的交互
	void interactWithWater(std::string itemName,const int& x, const int& y);

	// 与箱子的交互
	void interactWithMold(std::string itemName, const int& x, const int& y);
};

#endif