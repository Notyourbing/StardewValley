#include "TileNode.h"
#include<iostream>




// TileNode基类：构造函数
TileNode::TileNode(const cocos2d::Vec2& position, const TileType& tileType, const int& currentGID) :
	position(position), tileType(tileType), currentGID(currentGID) {

}

// Grass类：构造函数
Grass::Grass(const cocos2d::Vec2& position) :
	TileNode(position, TileType::GRASS, 5) {

}

// Grass类的交互函数
void Grass::interact(std::string toolName) {
	// 判断动物
	if (toolName == "crow") {				// 牛

	}
	else if (toolName == "chicken") {		// 鸡

	}
	else if (toolName == "sheep") {			// 羊

	}
	else if (toolName == "pig") {			// 猪

	}
}

// Soil类：构造函数
Soil::Soil(const cocos2d::Vec2& position) :
	TileNode(position, TileType::SOIL, 36), crop(nullptr),
	isWatered(false), isFertilized(false), isHoed(false),
	waterLevel(0), fertilizeLevel(0)
{}


// Soil类：锄地
void Soil::hoe() {
	isHoed = true;
	this->updateGID(64);
}

// Soil类：浇水
void Soil::water() {
	if (isHoed ) {
		// 判断这个土壤位置是否有作物
		if (crop == nullptr) {
			this->updateGID(96);
		}
		// 更新土壤的状态
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
	// 当土壤上没有作物的时候
	if (crop == nullptr) {
		if (seedName == "apple") {		// 种植苹果

		}
		else if(seedName=="corn"){		// 种植玉米

		}
		else if(seedName=="carrot"){	// 种植胡萝卜
			
		}
	}
}

// Soil类：
void Soil::interact(std::string toolName) {
	
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

	}
}