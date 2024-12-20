/****************************************************************
 * File Function: 瓦点类的实现，实现每个瓦点的具体功能
 * Author:        高鑫
 ****************************************************************/
#include "TileNode.h"
#include "../Crop/Crop.h"
#include "../Crop/DogbaneCrop.h"
#include "../Crop/CornCrop.h"
#include "../Crop/CarrotCrop.h"
#include "../Bag/Bag.h"
#include "../Food/DogbaneFood.h"
#include "../Food/CornFood.h"
#include "../Food/CarrotFood.h"
#include <algorithm>

// TileNode基类：构造函数
TileNode::TileNode(const cocos2d::Vec2& position, const TileType& tileType) :
	position(position), tileType(tileType){

}

// 初始化
bool TileNode::init() {
	return true;
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
cocos2d::Vec2 TileNode::getNodePosition() const {
	return position;
}

// TileNode基类：更新GID
void TileNode::updateGID() {
}

// Grass类：静态创建函数
Grass* Grass::create(const cocos2d::Vec2& position) {
	Grass* grass = new (std::nothrow) Grass(position);
	if (grass&&grass->init()) {
		return grass;
	}
	CC_SAFE_DELETE(grass);
	return nullptr;
}

// Grass类的初始化
bool Grass::init() {
	currentGID = GRASS_GID;
	return true;
}

// Grass类：构造函数
Grass::Grass(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Grass) {
}

// Soil类：静态构造函数
Soil* Soil::create(const cocos2d::Vec2& position) {
	Soil* soil = new (std::nothrow) Soil(position);
	if (soil&&soil->init()) {
		return soil;
	}
	CC_SAFE_DELETE(soil);
	return nullptr;
}

// Soil类初始化
bool Soil::init() {
	crop = nullptr;
	waterLevel = 0;
	fertilizeLevel = 0;
	isHoed = false;
	currentGID = SOIL_GID;
	return true;
}

// Soil类：构造函数
Soil::Soil(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Soil){
}

// Soil类：锄地
void Soil::soilHoe() {
	// 锄地或者锄去死亡作物
	if (crop == nullptr) {
		isHoed = true;
	}
	else {
		// 如果当前作物死亡
		if (crop->isDead()) {
			delete crop;
			crop = nullptr;
		}
	}
	updateGID();
}

// Soil类：浇水
void Soil::soilWater() {
	waterLevel = 10;
}

// Soil类：施肥
void Soil::soilFertilize() {
	fertilizeLevel = 10;
}

// Soil类：种植
void Soil::plantCrop(std::string seedName) {
	// 种植得先开垦
	if (isHoed&&crop==nullptr) {
		if (seedName == "dogbaneSeed") {				// 种植防风草
			crop = Dogbane::create();
		}
		else if (seedName == "cornSeed") {				// 种植玉米
			crop = Corn::create();
		}
		else {											// 种植胡萝卜
			crop = Carrot::create();
		}
		updateGID();
		crop->soilInfluence(waterLevel,fertilizeLevel);
	}
}

// Soil类：应用农药
void Soil::applyAgrochemical() {
	// 如果当前无作物，则直接返回
	if (crop == nullptr) {
		return;
	}

	// 应用农药
	crop->applyPesticide();
}

// Soil类：判断是否有作物
bool Soil::isPlanted() const {
	return crop != nullptr;
}

// Soil类：作物生长
void Soil::cropGrow() {
	// 获取作物种类
	CropType cropType = crop->getCropType();
	
	// 根据作物分类
	switch (cropType) {
	case CropType::Dogbane:
		dynamic_cast<Dogbane*>(crop)->grow();
		break;
	case CropType::Corn:
		dynamic_cast<Corn*>(crop)->grow();
		break;
	case CropType::Carrot:
		dynamic_cast<Carrot*>(crop)->grow();
		break;
	}

	// 更新土壤图块
	updateGID();
}

// Soil类：收获
void Soil::harvest() {
	// 判断作物是否成熟
	if (crop != nullptr && crop->isMature()) {
		Bag* bag = Bag::getInstance();
		CropType cropType = crop->getCropType();
		
		// 根据作物分类
		Food* harvestFood = nullptr;
		switch (cropType) {
		case CropType::Dogbane:
			harvestFood = DogbaneFood::create();
			break;
		case CropType::Corn:
			harvestFood = CornFood::create();
			break;
		case CropType::Carrot:
			harvestFood = CarrotFood::create();
			break;
		}

		// 添加作物物品
		bag->addItem(harvestFood);

		// 删除地图上的作物
		delete crop;
		crop = nullptr;

		// 更新图块
		updateGID();
	}
}

// Soil类：时间更新
void Soil::updateByTime() {
	// 含水量下降
	if (waterLevel) {
		waterLevel--;
	}

	// 含肥量下降
	if (fertilizeLevel){
		fertilizeLevel--;
	}

	// 作物更新
	if (crop) {
		cropGrow();
		crop->soilInfluence(waterLevel, fertilizeLevel);
	}

	// 更新图块
	updateGID();
}

// Soil类：更新GID
void Soil::updateGID() {
	// 根据是否有作物进行判断
	if (crop == nullptr) {
		// 判断是否耕种
		if (isHoed == false) {
			currentGID = SOIL_GID;
			return;
		}

		// 判断水	
		if(waterLevel>0){
			currentGID = WATER_SOIL_GID;
			return;
		}

		// 判断肥料
		if (fertilizeLevel > 0) {
			currentGID = FERTILIZED_SOIL_GID;
			return;
		}

		// 无水与肥料
		if (waterLevel == 0 && fertilizeLevel == 0) {
			currentGID = HOED_SOIL_GID;
		}
	}
	else {
		
		// 获得植物状态
		CropType cropType = crop->getCropType();
		int cropGrowthStage = crop->getGrowthStage();

		// 作物死亡
		if (cropGrowthStage == 0) {
			currentGID = DEAD_CROP;
			return;
		}

		// 植物种类分类
		switch (cropType) {
		case CropType::Dogbane:
			currentGID = judgeDogbaneGID(cropGrowthStage);
			break;
		case CropType::Corn:
			currentGID = judgeCornGID(cropGrowthStage);
			break;
		case CropType::Carrot:
			currentGID = judgeCarrotGID(cropGrowthStage);
			break;
		}
	}
}

// 防风草GID判断
int Soil::judgeDogbaneGID(int growStage) {
	// 不同生长阶段
	if (growStage == 1) {										// Dogbane生长阶段1
		// 判断水和肥料
		if (waterLevel && fertilizeLevel) {
			return DOGBANE_FIRST_FERTILIZE_WATER;
		}
		else if (waterLevel) {
			return DOGBANE_FIRST_WATER;
		}
		else if (fertilizeLevel) {
			return DOGBANE_FIRST_FERTILIZE;
		}
		else {
			return DOGBANE_FIRST;
		}
	}
	else if (growStage == 2) {								// Dogbane生长阶段2
		// 判断水和肥料
		if (waterLevel && fertilizeLevel) {
			return DOGBANE_SECOND_FERTILIZE_WATER;
		}
		else if (waterLevel) {
			return DOGBANE_SECOND_WATER;
		}
		else if (fertilizeLevel) {
			return DOGBANE_SECOND_FERTILIZE;
		}
		else {
			return DOGBANE_SECOND;
		}
	}
	else if (growStage == 3) {								// Dogbane生长阶段3
		// 判断虫害
		if (crop->judgeInfested()) {
			return DOGBANE_THIRD_ILL;
		}
		else {
			// 判断水和肥料
			if (waterLevel && fertilizeLevel) {
				return DOGBANE_THIRD_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return DOGBANE_THIRD_WATER;
			}
			else if (fertilizeLevel) {
				return DOGBANE_THIRD_FERTILIZE;
			}
			else {
				return DOGBANE_THIRD;
			}
		}
	}
	else {															// Dogbane生长阶段四
		// 判断虫害
		if (crop->judgeInfested()) {
			return DOGBANE_THIRD_ILL;
		}
		else {
			// 判断水和肥料
			if (waterLevel && fertilizeLevel) {
				return DOGBANE_FOURTH_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return DOGBANE_FOURTH_WATER;
			}
			else if (fertilizeLevel) {
				return DOGBANE_FOURTH_FERTILIZE;
			}
			else {
				return DOGBANE_FOURTH;
			}
		}
	}
}

// 玉米GID判断
int Soil::judgeCornGID(int growStage) {
	// 不同生长阶段
	if (growStage == 1) {									// Corn生长阶段1
		// 判断水和肥料
		if (waterLevel && fertilizeLevel) {
			return CORN_FIRST_FERTILIZE_WATER;
		}
		else if (waterLevel) {
			return CORN_FIRST_WATER;
		}
		else if (fertilizeLevel) {
			return CORN_FIRST_FERTILIZE;
		}
		else {
			return CORN_FIRST;
		}
	}
	else if (growStage == 2) {								// Corn生长阶段2
		// 判断是否有虫害
		if (crop->judgeInfested()) {
			return CORN_SECOND_ILL;
		}
		else{
			if (waterLevel && fertilizeLevel) {
				return CORN_SECOND_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return CORN_SECOND_WATER;
			}
			else if (fertilizeLevel) {
				return CORN_SECOND_FERTILIZE;
			}
			else {
				return CORN_SECOND;
			}
		}
	}
	else {													// Corn生长阶段3
		// 判断是否有虫害
		if (crop->judgeInfested()) {
			return CORN_THIRD_ILL;
		}
		else {
			if (waterLevel && fertilizeLevel) {
				return CORN_THIRD_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return CORN_THIRD_WATER;
			}
			else if (fertilizeLevel) {
				return CORN_THIRD_FERTILIZE;
			}
			else {
				return CORN_THIRD;
			}
		}
	}
}

// 胡萝卜GID判断
int Soil::judgeCarrotGID(int growStage) {
	// 不同生长阶段
	if (growStage == 1) {									// Carrot生长阶段1
		// 判断水和肥料
		if (waterLevel && fertilizeLevel) {
			return CARROT_FIRST_FERTILIZE_WATER;
		}
		else if (waterLevel) {
			return CARROT_FIRST_WATER;
		}
		else if (fertilizeLevel) {
			return CARROT_FIRST_FERTILIZE;
		}
		else {
			return CARROT_FIRST;
		}
	}
	else if (growStage == 2) {								// Carrot生长阶段2
		// 判断是否有虫害
		if (crop->judgeInfested()) {
			return CARROT_SECOND_ILL;
		}
		else {
			if (waterLevel && fertilizeLevel) {
				return CARROT_SECOND_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return CARROT_SECOND_WATER;
			}
			else if (fertilizeLevel) {
				return CARROT_SECOND_FERTILIZE;
			}
			else {
				return CARROT_SECOND;
			}
		}
	}
	else {													// Corn生长阶段3
		// 判断是否有虫害
		if (crop->judgeInfested()) {
			return CARROT_THIRD_ILL;
		}
		else {
			if (waterLevel && fertilizeLevel) {
				return CARROT_THIRD_FERTILIZE_WATER;
			}
			else if (waterLevel) {
				return CARROT_THIRD_WATER;
			}
			else if (fertilizeLevel) {
				return CARROT_THIRD_FERTILIZE;
			}
			else {
				return CARROT_THIRD;
			}
		}
	}
}

// Water类：静态创建函数
Water* Water::create(const cocos2d::Vec2& position) {
	Water* water = new (std::nothrow) Water(position);
	if (water&&water->init()) {
		return water;
	}
	CC_SAFE_DELETE(water);
	return nullptr;
}

// Water类：初始化
bool Water::init() {
	currentGID = WATER_GID;
	return true;
}

// Water类构造函数
Water::Water(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Water){
}

// Obstacle类：静态创建函数
Obstacle* Obstacle::create(const cocos2d::Vec2& position) {
	Obstacle* obstacle = new (std::nothrow) Obstacle(position);
	if (obstacle && obstacle->init()){
		return obstacle;
	}
	CC_SAFE_DELETE(obstacle);
	return nullptr;
}

// Obstacle类：初始化
bool Obstacle::init() {
	currentGID = OBSTACLES_GID;
	return true;
}

// Obstacle类：构造函数
Obstacle::Obstacle(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Obstacle){
}

// Stone类：静态创建函数
Stone* Stone::create(const cocos2d::Vec2& position) {
	Stone* stone = new (std::nothrow) Stone(position);
	if (stone && stone->init()) {
		return stone;
	}
	CC_SAFE_DELETE(stone);
	return nullptr;
}

// Obstacle类：初始化
bool Stone::init() {
	currentGID = STONE_GID;
	stoneSolidity = 3;
	return true;
}

// Stone类：构造函数
Stone::Stone(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Stone){
}

// Stone类：敲击石头
void Stone::knockRock() {
	stoneSolidity--;
}

// Stone类：判断是否击碎
bool Stone::isBroken() const{
	return stoneSolidity == 0;
}

// Mold类：静态创建函数
Mold* Mold::create(const cocos2d::Vec2& position) {
	Mold* mold = new (std::nothrow) Mold(position);
	if (mold && mold->init()) {
		return mold;
	}
	CC_SAFE_DELETE(mold);
	return nullptr;
}

// Obstacle类：初始化
bool Mold::init() {
	currentGID = MOLD_GID;
	return true;
}

// Mold类：构造函数
Mold::Mold(const cocos2d::Vec2& position) :
	TileNode(position, TileType::Mold){
}