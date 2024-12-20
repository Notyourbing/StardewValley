/****************************************************************
 * File Function: 瓦点类，为瓦点地图上不同的图块赋予不同的属性
 * Author:        高鑫
 ****************************************************************/
#ifndef __TILE_NODE_H__
#define __TILE_NODE_H__

#include "cocos2d.h"
#include "../Crop/Crop.h"
#include "../Constant/Constant.h"
#include "string"

// 瓦点类型
enum class TileType {
	Grass,
	Soil,
	Obstacle,
	Mold,
	Water,
	Stone,
};

// 瓦点抽象基类
class TileNode {
private:
	// 瓦点位置
	cocos2d::Vec2 position;

	// 瓦点类型
	TileType tileType;
	
protected:
	// 瓦点的GID
	int currentGID;

public:
	// 构造函数
	TileNode(const cocos2d::Vec2& position, const TileType& tileType);

	// 初始化
	virtual bool init();

	// 返回瓦点的类型
	TileType getTileType() const;

	// 返回瓦点GID
	int getCurrentGID() const;

	// 返回瓦点位置
	cocos2d::Vec2 getNodePosition() const;

	// 更新瓦点GID
	virtual void updateGID();
};

// 瓦店草类，地图上的草
class Grass : public TileNode {
public:
	// 静态创建函数
	static Grass* create(const cocos2d::Vec2& position);

	// 构造函数
	Grass::Grass(const cocos2d::Vec2& position);

	// 初始化
	bool init() override;
};

// 瓦点土壤类，地图上的土壤
class Soil : public TileNode {
private:
	// 作物
	Crop* crop;

	// 是否被锄地
	bool isHoed;

	// 含水量
	int waterLevel;

	// 含肥量
	int fertilizeLevel;

	// 防风草GID判断
	int judgeDogbaneGID(int growStage);

	// 玉米GID判断
	int judgeCornGID(int growStage);

	// 胡萝卜GID判断
	int judgeCarrotGID(int growStage);

public:
	// 静态创建函数
	static Soil* create(const cocos2d::Vec2& position);

	// 构造函数
	Soil(const cocos2d::Vec2& position);

	// 初始化
	bool init() override;

	// 锄地
	void soilHoe();

	// 浇水
	void soilWater();

	// 施肥
	void soilFertilize();

	// 种植作物
	void plantCrop(std::string seedName);

	// 判断是否有作物
	bool isPlanted() const;

	// 作物生长
	void cropGrow();

	// 应用农药
	void applyAgrochemical();

	// 收获作物
	void harvest();

	// 随时间变化
	void updateByTime();

	// 更新图块
	void updateGID() override;
};

// 瓦点水类，地图上的水
class Water : public TileNode {
public:
	// 静态创建函数
	static Water* create(const cocos2d::Vec2& position);

	// 初始化
	bool init() override;

	// 构造函数
	Water(const cocos2d::Vec2& position);
};

// 瓦点障碍类，地图上的障碍
class Obstacle : public TileNode {
public:
	// 静态创建函数
	static Obstacle* create(const cocos2d::Vec2& position);

	// 初始化
	bool init() override;

	// 构造函数
	Obstacle(const cocos2d::Vec2& position);
};

// 瓦点石头类，地图上的石头
class Stone : public TileNode {
private:
	// 坚固程度
	int stoneSolidity;		
public:
	// 静态创建函数
	static Stone* create(const cocos2d::Vec2& position);

	// 初始化
	bool init() override;

	// 构造函数
	Stone(const cocos2d::Vec2& position);

	// 敲击石头
	void knockRock();

	// 是否被击碎
	bool isBroken() const;
};

// 瓦点箱子类，地图上的箱子
class Mold : public TileNode {
public:
	// 静态创建函数
	static Mold* create(const cocos2d::Vec2& position);

	// 初始化
	bool init() override;

	Mold(const cocos2d::Vec2& position);
};

#endif