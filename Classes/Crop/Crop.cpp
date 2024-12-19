#include "Crop.h"
#include "../Date/DateManage.h"
#include "../Constant/Constant.h"

// Crop基类：构造函数
Crop::Crop(const CropType& cropType) :
	cropType(cropType), growthStage(1),
	isInfested(false), isDrought(false), isFertilized(false),
	infestedDay(0), droughtDay(0),growedDay(0) {
}

// 土壤对作物的影响
void Crop::soilInfluence(int waterLevel,int fertilizeLevel) {
	// 土壤含水
	if (waterLevel) {
		isDrought = false;
		droughtDay = 0;
	}
	else {
		isDrought = true;
	}

	// 土壤含肥
	if (fertilizeLevel) {
		isFertilized = true;
	}
	else {
		isFertilized = false;
	}
}

// 初始化
bool Crop::init() {
	return true;
}

// 判断死亡
bool Crop::isDead() {
	return growthStage == 0;
}

// 判断作物成熟
bool Crop::isMature() {
	switch (cropType){
	case CropType::Dogbane:
		return growthStage == DOGBANE_MAX_GROWTH_STAGE;
		break;
	case CropType::Corn:
		return growthStage == CORN_MAX_GROWTH_STAGE;
		break;
	case CropType::Carrot:
		return growthStage == CARROT_MAX_GROWTH_STAGE;
		break;
	}
}

// 使用农药
void Crop::applyPesticide() {
	isInfested = false;
	infestedDay = 0;
}

// 更新生长阶段
void Crop::updateGrowthStage() {
	// 获得季节
	DateManage* dateManage = DateManage::getInstance();
	std::string currentSeason = dateManage->getCurrentSeason();

	if (isDead()) {
		return;
	}

	// 初始生长阶段为1
	growthStage = 1;

	// 判断生长阶段
	int totalDays = 0;
	for (int index = 0; index < static_cast<int>(seasonalGrowthStageDay[currentSeason].size()); index++) {
		totalDays += seasonalGrowthStageDay[currentSeason][index];
		if (totalDays > growedDay) {
			break;
		}
		growthStage ++;
	}
	CCLOG("%d",growthStage);
	dateManage = nullptr;
}

// 获取生长阶段
int Crop::getGrowthStage() const {
	return growthStage;
}

// 判断作物虫害
bool Crop::judgeInfested() const {
	return isInfested == true;
}

// 获得当前作物类型
CropType Crop::getCropType() const {
	return cropType;
}
