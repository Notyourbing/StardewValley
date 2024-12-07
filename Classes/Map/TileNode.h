#ifndef __TILE_NODE_H__
#define __TIEL_NODE_H__

#include "cocos2d.h"
#include "Crop.h"
#include "../Constant/Constant.h"
#include "string"

// 有哪几种瓦片地图的节点
enum class TileType {
	Grass,
	Soil,
	Obstacle,
	Mold,
	Water,
	Stone,
};

// 瓦片地图节点基类
class TileNode {
private:
	// 存储基类的位置
	cocos2d::Vec2 position;

	// 存储该节点的类型
	TileType tileType;

	// 更新当前节点的GID
	virtual void updateGID();

protected:

	// 当前这个瓦点的GID
	int currentGID;

public:
	// 瓦片地图节点基类的构造函数
	TileNode(const cocos2d::Vec2& position, const TileType& tileType, const int& currentGID);

	// 获取该节点的类型
	TileType getTileType() const;

	// 返回给土壤块的GID
	int getCurrentGID() const;

	// 获取该TileNode节点的位置
	cocos2d::Vec2 getPosition() const;

	// TileNode节点与左键的交互
	virtual void interact(const std::string& toolName) {};

	// 土壤的更新函数
	virtual void updateByTime() {};
};

/* Grass类表示草，从TileNode类继承而来
** 用来在草地上养殖动物
*/
class Grass : public TileNode {
public:

	// Grass类的构造函数
	Grass::Grass(const cocos2d::Vec2& position,const int& GID);

	// 草地的养殖交互函数的实现
	void interact(const std::string& toolName) override;
};

// Soil类表示土壤，从TileNode类继承而来
class Soil : public TileNode {
private:
	// 表示土壤中的作物
	Crop* crop;

	// 是否被锄地
	bool isHoed;

	// 是否已经浇水
	bool isWatered;

	// 是否已经施肥
	bool isFertilized;

	// 土壤的含水量
	int waterLevel;

	// 土壤的含肥量
	int fertilizeLevel;

	// 土壤的锄地
	void hoe();

	// 土壤的浇水
	void water();

	// 土壤的施肥
	void fertilize();

	// 土壤的种植
	void plantCrop(std::string seedName);

	// updateGID的重写
	void updateGID() override;
public:
	// 土壤类的构造函数
	Soil(const cocos2d::Vec2& position);

	//	土壤的交互函数
	void interact(const std::string& toolName) override;

	// 土壤的更新函数
	void updateByTime() override;

	// 土壤状态对作物的影响
	void influenceCropStatus();
};

// Water类表示水，从TileNode类继承而来
class Water : public TileNode {
private:
	static int waterResource;				// 表示当前水库中的水资源,所有的水资源都共用一个waterResource
public:

	// Water类表示水
	Water(const cocos2d::Vec2& position);

	// 判断水资源是否枯竭
	bool isWaterDepleted() const;

	// Water类的交互函数
	void interact(const std::string& toolName) override;

	// 取水
	void pumpWater(int water);

	// 下雨补充水资源
	void rechargeWaterResource();

	// 获得当前水资源
	int getCurrentWaterResource() const;
};

// Obstacle类：障碍
class Obstacle : public TileNode {
public:
	// 构造函数
	Obstacle(const cocos2d::Vec2& position);
};

// STONE类表示障碍，从TileNode类继承而来
class Stone : public TileNode {
private:
	int stoneSolidity;		// 石头的坚固程度
public:
	// 构造函数
	Stone(const cocos2d::Vec2& position);

	// 敲击石头
	void knockRock();

	// 是否被击碎
	bool isBroken() const;
};

/* Mold类用于开启商店
*/
class Mold : public TileNode {
public:
	Mold(const cocos2d::Vec2& position);
};

#endif