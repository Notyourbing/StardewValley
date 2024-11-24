#ifndef __FARMMAP_H__
#define __FARMMAP_H__

#include "cocos2d.h"
#include "../Npc/Npc.h"
#include <string>
class FarmMap : public cocos2d::Node {
public:
	// 获取单例实例
	static FarmMap* getInstance();

	// 初始化地图
	bool init(const std::string& tmxFile);

	//随地图创建npc
	bool npcInit(const Vec2& position, Npc* npc);

	// 更新地图位置
	void moveMapByDirection(const cocos2d::Vec2 &direction);
	
	// 获取地图大小
	cocos2d::Size getMapSize() const;

private:
	// 构造函数和析构函数私有化
	FarmMap();
	~FarmMap();

	// 禁用拷贝构造和赋值操作
	FarmMap(const FarmMap&) = delete;
	FarmMap& operator=(const FarmMap&) = delete;

	// 瓦片地图对象
	cocos2d::TMXTiledMap* map = nullptr;

	// 地图当前的偏移位置
	cocos2d::Vec2 currentPosition; 

	// 地图的偏移速度
	cocos2d::Vec2 velocity;

	// 单例实例
	static FarmMap* instance;
};


#endif
