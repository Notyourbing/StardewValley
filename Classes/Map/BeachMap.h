#ifndef __BEACHMAP_H__
#define __BEACHMAP_H__

#include "cocos2d.h"
#include "TileNode.h"
#include "../Festival/Festival.h"
#include "../Constant/Constant.h"
#include "../Bag/Bag.h"


// 海滩地图
class BeachMap : public cocos2d::Node {
public:
	// 获取单例实例
	static BeachMap* getInstance();

	// 初始化地图
	bool init(const std::string& tmxFile);

	// 更新地图位置
	void moveMapByDirection(const cocos2d::Vec2& direction);

	// 获取地图大小
	const cocos2d::Size& getMapSize() const;

	// 碰撞检测：检查给定位置是否是障碍物
	bool isCollidable(const cocos2d::Vec2& position) const;

	// 用于鼠标左键与海滩的交互逻辑
	void interactWithBeachMap();

	// 地图停止移动
	void stopMoving();

	// 获取地图的瓦片地图对象
	cocos2d::TMXTiledMap* getTiledMap();

	//获取当前位置地图的类
	TileNode* getTileNode(const int x, const int y) const;

	// 地图随着时间的更新
	void beachMapUpdateByTime();

private:
	// 构造函数和析构函数私有化
	BeachMap();
	~BeachMap();

	// 禁用拷贝构造和赋值操作
	BeachMap(const BeachMap&) = delete;
	BeachMap& operator=(const BeachMap&) = delete;

	// 地图的偏移速度
	cocos2d::Vec2 velocity;

	// 单例实例
	static BeachMap* instance;

	// 瓦片地图对象
	cocos2d::TMXTiledMap* tiledMap;

	// 存储地图上每个节点的类
	TileNode* mapTileNode[BEACHMAP_WIDTH][BEACHMAP_HEIGHT];

	// 用来存储TMX地图的各个层
	cocos2d::TMXLayer* backgroundLayer;
	cocos2d::TMXLayer* waterLayer;
};
#endif
