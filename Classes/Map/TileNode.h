#ifndef __TILE_NODE_H__
#define __TILE_NODE_H__

#include "cocos2d.h"
#include "Crop.h"
#include "../Constant/Constant.h"
#include "string"

/*
 * Class Name:     TileType
 * Class Function: 瓦点类型
 */
enum class TileType {
	Grass,
	Soil,
	Obstacle,
	Mold,
	Water,
	Stone,
};

/*
 * Class Name:     TileNode
 * Class Function: 瓦点基类
 */
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

/*
 * Class Name:	   Grass
 * Class Function: 地图中的草
 */
class Grass : public TileNode {
public:
	// 静态创建函数
	static Grass* create(const cocos2d::Vec2& position);

	// 构造函数
	Grass::Grass(const cocos2d::Vec2& position);

	// 初始化
	bool init() override;
};

/*
 * Class Name:	   Soil
 * Class Function: 地图中的土壤
 */
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


class Water : public TileNode {
public:
	// 静态创建函数
	static Water* create(const cocos2d::Vec2& position);

	// 初始化
	bool init() override;

	// 构造函数
	Water(const cocos2d::Vec2& position);
};

class Obstacle : public TileNode {
public:
	// 静态创建函数
	static Obstacle* create(const cocos2d::Vec2& position);

	// 初始化
	bool init() override;

	// 构造函数
	Obstacle(const cocos2d::Vec2& position);
};

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


class Mold : public TileNode {
public:
	// 静态创建函数
	static Mold* create(const cocos2d::Vec2& position);

	// 初始化
	bool init() override;

	Mold(const cocos2d::Vec2& position);
};

#endif