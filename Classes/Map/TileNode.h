#ifndef __TILE_NODE_H__
#define __TIEL_NODE_H__

#include "cocos2d.h"
#include "Crop.h"
#include "string"

// 有哪几种瓦片地图的节点
enum class TileType {
	GRASS,
	SOIL,
	OBSTACLE,
	MOLD,
	WATER,
	STONE,
};

// 瓦片地图节点基类
class TileNode {
private:
	// 存储基类的位置
	cocos2d::Vec2 position;

	// 存储该节点的类型
	TileType tileType;

	// 当前这个瓦点的GID
	int currentGID;

protected:
	// 更新当前节点的GID
	void updateGID(int newGID) {
		currentGID = newGID;
	}

public:
	// 瓦片地图节点基类的构造函数
	TileNode(const cocos2d::Vec2& position, const TileType& tileType,const int& currentGID) :
		position(position), tileType(tileType),currentGID(currentGID)
	{} // ?? 注意括号的格式保持和其他文件统一，这里不应该另起一行。另外这里是.h文件，对于非静态成员变量和函数只应该有声明不应该有定义

	// 获取该节点的类型
	TileType getTileType() const{
		return tileType;
	}

	// 返回给土壤块的GID
	int getCurrentGID() const {
		return currentGID;
	}

	// TileNode节点与左键的交互
	virtual void interact(std::string toolName) {};
};

// Grass类表示草，从TileNode类继承而来
class Grass : public TileNode {
public:
	Grass(const cocos2d::Vec2& position):
		TileNode(position,TileType::GRASS,1)
	{}

	// 草地的养殖交互函数的实现
	virtual void interact(std::string toolName);
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
public:
	// 土壤类的构造函数
	Soil(const cocos2d::Vec2& position) :
		TileNode(position, TileType::SOIL,3), crop(nullptr),
		isWatered(false), isFertilized(false), isHoed(false),
		waterLevel(0),fertilizeLevel(0)
	{}

	// 土壤的锄地
	void hoe();

	// 土壤的浇水
	void water();

	// 土壤的施肥
	void fertilize();

	// ?? 这个也写虚函数是因为Soil还有派生类吗？
	void interact(std::string toolName) override;
};

// Water类表示水，从TileNode类继承而来
class Water : public TileNode {
public:
	Water(const cocos2d::Vec2& position) :
		TileNode(position, TileType::WATER,17)
	{}
};

// Obstacle类表示障碍，从TileNode类继承而来
class Obstacle : public TileNode {
public:
	Obstacle(const cocos2d::Vec2& position) :
		TileNode(position,TileType::OBSTACLE,100)
	{}
};

// MOLD类表示箱子，从TileNode类继承而来
class Mold : public TileNode {
public:
	Mold(const cocos2d::Vec2& position) :
		TileNode(position, TileType::MOLD,200)
	{}
};

// STONE类表示障碍，从TileNode类继承而来
class Stone : public TileNode {
public:
	Stone(const cocos2d::Vec2& position) :
		TileNode(position, TileType::STONE,22)
	{}
};

#endif