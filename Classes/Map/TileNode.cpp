#include "TileNode.h"
#include <algorithm>

// TileNode基类：构造函数
TileNode::TileNode(const cocos2d::Vec2& position, const TileType& tileType, const int& currentGID) :
	position(position), tileType(tileType), currentGID(currentGID) {
}

// 获取该节点的类型
TileType TileNode::getTileType() const {
	return tileType;
}

// 返回给土壤块的GID
int TileNode::getCurrentGID() const {
	return currentGID;
}

// TileNode基类：获取位置
cocos2d::Vec2 TileNode::getPosition() const {
	return position;
}

// Grass类：构造函数
Grass::Grass(const cocos2d::Vec2& position,const int& GID) :
	TileNode(position, TileType::Grass, GID) {
}

// Soil类：构造函数
Soil::Soil(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Soil, SOIL_GID), crop(nullptr),
	isWatered(false), isFertilized(false), isHoed(false),
	waterLevel(0), fertilizeLevel(0)
{}

// Soil类：锄地
void Soil::hoe() {
	isHoed = true;
}

// Soil类：浇水
void Soil::water() {
	if (isHoed ) {
		waterLevel = 10;
		isWatered = true;
	}
}

// Soil类：施肥
void Soil::fertilize() {

	// 当已经种植作物时才能施肥
	if (crop) {
		fertilizeLevel = 10;
		isFertilized = true;

	}
}

// Soil类：种植
void Soil::plantCrop(const std::string& seedName) {
	// 未开垦和已经种植的话返回
	if (isHoed == false || crop != nullptr) {
		return;
	}

	// 根据种子的类别种不同的作物
	if (seedName == "appleSeed") {
		crop = new Apple(getPosition());
	}
	else if (seedName == "cornSeed") {
		crop = new Corn(getPosition());
	}
	else if (seedName == "carrotSeed") {
		crop = new Carrot(getPosition());
	}
}

// Soil类：收获
void Soil::harvest() {
	// 有待完善 需要增加
}

// 土壤类随时间变化的更新函数
void Soil::gidUpdateByTime() {
	if (crop == nullptr) {
		return;
	}
	else {
		crop->grow();
		currentGID = crop->getCurrentGID();
	}
}

// Soil类：随事件变化的更新函数
void Soil::gidUpdateByEvent() {
	if (isHoed == false) {
		currentGID = SOIL_GID;
	}
	else {
		if (isWatered) {
			if (crop == nullptr) {
				currentGID = WATER_SOIL_GID;
			}
			else {
				currentGID = crop->getCurrentGID();
			}
		}
		else {
			if (crop == nullptr) {
				currentGID = HOED_SOIL_GID;
			}
			else {
				currentGID = crop->getCurrentGID();
			}
		}
	}
}

int Water::waterResource = MAX_WATER_RESOURCE;

// Water类：构造函数
Water::Water(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Water, WATER_GID){}

// Water类：判断水资源
bool Water::isWaterDepleted() const {
	return waterResource == 0;
}

// Water类：抽水
void Water::pumpWater(int water) {
	waterResource -= water;
}

// Water类：下雨补充水资源
void Water::rechargeWaterResource() {
	waterResource = (waterResource+RANIY_REPLENISH)<MAX_WATER_RESOURCE ? waterResource+RANIY_REPLENISH:MAX_WATER_RESOURCE;
}

// Water类：获得当前水资源
int Water::getCurrentWaterResource() const {
	return waterResource;
}

// Water类：随时间变化
void Water::gidUpdateByTime() {
	// 判断当前水资源是否枯竭
	if (waterResource) {
		currentGID = WATER_GID;
	}
}

// Water类：随时间变化
void Water::gidUpdateByEvent() {
	// 判断当前水资源是否枯竭
	if (waterResource == 0) {
		currentGID = SOIL_GID;
	}
}

// Obstacle类：构造函数
Obstacle::Obstacle(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Obstacle, 100)
{}

// Stone类：构造函数
Stone::Stone(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Stone, STONE_GID),stoneSolidity(3)
{}

// Stone类：敲击石头
void Stone::knockRock() {
	stoneSolidity--;
}

// Stone类：判断是否击碎
bool Stone::isBroken() const{
	return stoneSolidity == 0;
}

// Mold类：构造函数
Mold::Mold(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Mold, 200)
{}