/****************************************************************
 * File Function: 玉米作物类的实现，实现玉米作物在不同条件下的生长
 * Author:        高鑫
 ****************************************************************/
#include "CornCrop.h"
#include "../Date/DateManage.h"
#include "../Constant/Constant.h"

// 静态创建函数
Corn* Corn::create() {
	Corn* corn = new (std::nothrow) Corn();
	if (corn && corn->init()) {
		return corn;
	}
	CC_SAFE_DELETE(corn);
	return nullptr;
}

// 初始化
bool Corn::init() {
	// 初始化不同季节的生长阶段天数
	seasonalGrowthStageDay["Spring"].push_back(CORN_SPRING_STAGE_FIRST);
	seasonalGrowthStageDay["Spring"].push_back(CORN_SPRING_STAGE_SECOND);
	seasonalGrowthStageDay["Summer"].push_back(CORN_SUMMER_STAGE_FIRST);
	seasonalGrowthStageDay["Summer"].push_back(CORN_SUMMER_STAGE_SECOND);
	seasonalGrowthStageDay["Fall"].push_back(CORN_AUTUMN_STAGE_FIRST);
	seasonalGrowthStageDay["Fall"].push_back(CORN_AUTUMN_STAGE_SECOND);
	seasonalGrowthStageDay["Winter"].push_back(CORN_WINTER_STAGE_FIRST);
	seasonalGrowthStageDay["Winter"].push_back(CORN_WINTER_STAGE_SECOND);
	return true;
}

// 构造函数
Corn::Corn() :
	Crop(CropType::Corn) {
}

// 作物生长
void Corn::grow() {
	// 判断是否干旱以及虫害
	if (isDrought == false && isInfested == false) {
		if (isFertilized) {
			growedDay += 2;
		}
		else {
			growedDay++;
		}
	}
	
	// 干旱天数增加
	if (isDrought) {
		droughtDay++;
	}

	// 病害天数增加
	if (isInfested) {
		infestedDay++;
	}

	// 判断干旱或者虫害天数是否超过正常天数
	if (droughtDay > WATER_SCARCITY_DAY || infestedDay > INFESTED_DAY) {
		growthStage = 0;				// 作物死亡
		return;
	}

	// 随机生成病害
	if (isInfested == false) {
		generatePest();
	}

	// 更新作物生长阶段
	updateGrowthStage();
}

// 随机生成病害
void Corn::generatePest() {
	// 获得当前季节与天气
	DateManage* dateManage = DateManage::getInstance();
	std::string season = dateManage->getCurrentSeason();
	Weather weather = dateManage->getCurrentWeather();

	// 前两个生长阶段不会产生病害
	if (growthStage == 0 || growthStage == 1 || growthStage == 2) {
		return;
	}

	// 基础虫害概率
	int basePestProbability = 0;

	// 根据季节获得基础虫害概率
	if (season == "Spring") {
		basePestProbability = CORN_SPRING_PEST_PROBABILITY;
	}
	else if (season == "Summer") {
		basePestProbability = CORN_SUMMER_PEST_PROBABILITY;
	}
	else if (season == "Fall") {
		basePestProbability = CORN_AUTUMN_PEST_PROBABILITY;
	}
	else {
		basePestProbability = CORN_WINTER_PEST_PROBABILITY;
	}

	// 根据天气增加虫害概率
	switch (weather) {
	case Weather::Sunny:
		basePestProbability -= 5;
		break;
	case Weather::LightRain:
		basePestProbability += 5;
		break;
	case Weather::HeavyRain:
		basePestProbability += 10;
		break;
	}

	// 随机生成病害
	isInfested = (std::rand() % 100) < basePestProbability;
}