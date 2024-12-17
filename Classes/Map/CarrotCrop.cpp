#include "CarrotCrop.h"
#include "../DateManage/DateManage.h"
#include "../Constant/Constant.h"

Carrot* Carrot::create() {
	Carrot* carrot = new (std::nothrow) Carrot();
	if (carrot && carrot->init()) {
		return carrot;
	}
	CC_SAFE_DELETE(carrot);
	return nullptr;
}

bool Carrot::init() {
	// 初始化不同季节的生长阶段天数
	seasonalGrowthStageDay["Spring"].push_back(CARROT_SPRING_STAGE_FIRST);
	seasonalGrowthStageDay["Spring"].push_back(CARROT_SPRING_STAGE_SECOND);
	seasonalGrowthStageDay["Summer"].push_back(CARROT_SUMMER_STAGE_FIRST);
	seasonalGrowthStageDay["Summer"].push_back(CARROT_SUMMER_STAGE_SECOND);
	seasonalGrowthStageDay["Fall"].push_back(CARROT_AUTUMN_STAGE_FIRST);
	seasonalGrowthStageDay["Fall"].push_back(CARROT_AUTUMN_STAGE_SECOND);
	seasonalGrowthStageDay["Winter"].push_back(CARROT_WINTER_STAGE_FIRST);
	seasonalGrowthStageDay["Winter"].push_back(CARROT_WINTER_STAGE_SECOND);
	return true;
}


// 构造函数
Carrot::Carrot() :
	Crop(CropType::Carrot) {
}

// 生长函数
void Carrot::grow() {
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

	// 更新当前生长阶段
	updateGrowthStage();
}

// 随机生成病害
void Carrot::generatePest() {
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
		basePestProbability = CARROT_SPRING_PEST_PROBABILITY;
	}
	else if (season == "Summer") {
		basePestProbability = CARROT_SUMMER_PEST_PROBABILITY;
	}
	else if (season == "Fall") {
		basePestProbability = CARROT_AUTUMN_PEST_PROBABILITY;
	}
	else {
		basePestProbability = CARROT_WINTER_PEST_PROBABILITY;
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