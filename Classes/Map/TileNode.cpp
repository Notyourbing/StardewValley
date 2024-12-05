#include "TileNode.h"


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

// TileNode基类：更新图块的GID
// 思路根据状态去更新
void TileNode::updateGID() {
	return;
}

// Grass类：构造函数
Grass::Grass(const cocos2d::Vec2& position,const int& GID) :
	TileNode(position, TileType::GRASS, GID) {

}

// Grass类的交互函数
void Grass::interact(const std::string& toolName) {
	
}

// Soil类：构造函数
Soil::Soil(const cocos2d::Vec2& position) :
	TileNode(position, TileType::SOIL, HOED_SOIL_GID), crop(nullptr),
	isWatered(false), isFertilized(false), isHoed(false),
	waterLevel(0), fertilizeLevel(0)
{}

// Soil类：根据当前的状态更新GID
void Soil::updateGID() {

	// 根据土壤的条件更新GID
	if (isHoed == false) {
		currentGID = SOIL_GID;
		return;
	}

	// 判断是否有作物
	if (crop == nullptr) {
		if (isWatered == true) {
			currentGID = HOED_SOIL_GID;
		}
		else {
			currentGID = WATER_SOIL_GID;
		}
	}
	else {
		currentGID=crop->getCurrentGID();
		CCLOG("%d",currentGID);
	}
}

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
void Soil::plantCrop(std::string seedName) {
	
	// 判断土地是否种植
	if (isHoed == false) {
		return;
	}

	// 当土壤上没有作物的时候
	if (crop == nullptr) {
		if (seedName == "apple") {		// 种植苹果

		}
		else if(seedName=="corn"){		// 种植玉米

		}
		else if(seedName=="carrot"){	// 种植胡萝卜
			crop = new Carrot(this->getPosition());
		}
	}
}

// Soil类：
void Soil::interact(const std::string& toolName) {
	
	// 土壤与工具的交互
	if (toolName=="hoe") {						// 如果是锄头，那么进行锄地
		hoe();
	}
	else if (toolName == "wateringCan") {		// 如果是水壶，那么进行浇水
		water();
	}
	else if (toolName == "fertilizer") {		// 如果是肥料，那么进行施肥
		fertilize();
	}
	else if (toolName == "seed") {				// 如果是种子，那么进行种植
		plantCrop("carrot");
	}
	this->updateGID();
}

// Water类：构造函数
Water::Water(const cocos2d::Vec2& position) :
	TileNode(position, TileType::WATER, WATER_GID){}

// Water类：交互函数
void Water::interact(const std::string& toolName) {

}

// Stone类：构造函数
Stone::Stone(const cocos2d::Vec2& position) :
	TileNode(position, TileType::STONE, STONE_GID) {}