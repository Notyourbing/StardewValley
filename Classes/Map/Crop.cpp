#include "Crop.h"

// Crop基类：构造函数
Crop::Crop(const CropType& cropType,  const int& cropGID, cocos2d::Vec2 position) :
	cropType(cropType), growthStage(0),
	isInfested(false), isDrought(false), isFertilized(false),
	cropGID(cropGID), position(position), infestedDay(0), 
	droughtDay(0),growedDay(0) {
	switch (cropType) {
	case CropType::Apple:						// 苹果在不同季节的生长天数
		seasonGrowDay[Season::Spring] = 4;
		seasonGrowDay[Season::Summer] = 3;
		seasonGrowDay[Season::Autumn] = 6;
		seasonGrowDay[Season::Winter] = 7;
		break;
	case CropType::Corn:						// 玉米在不同季节的生长天数
		seasonGrowDay[Season::Spring] = 5;
		seasonGrowDay[Season::Summer] = 4;
		seasonGrowDay[Season::Autumn] = 7;
		seasonGrowDay[Season::Winter] = 8;
		break;
	case CropType::Carrot:						// 胡萝卜在不同季节的生长天数
		seasonGrowDay[Season::Spring] = 6;
		seasonGrowDay[Season::Summer] = 5;
		seasonGrowDay[Season::Autumn] = 8;
		seasonGrowDay[Season::Winter] = 9;
		break;
	}
}

// Crop基类：浇水
void Crop::irrigate() {

	isDrought = false;
	droughtDay = 0;
}

// Crop基类：施肥
void Crop::fertilize() {
	isFertilized = true;
}

// Crop基类：使用农药
void Crop::applyPesticide() {
	isInfested = false;
	infestedDay = 0;
}

// Crop基类：获得当前图块的GID
int Crop::getCurrentGID() {
	return cropGID;
}

// Crop基类：获得当前季节生长天数
int Crop::getCurrentSeasonGrowDay(Season season) {
	switch (season) {
	case Season::Spring:
		return seasonGrowDay[Season::Spring];
		break;
	case Season::Summer:
		return seasonGrowDay[Season::Summer];
		break;
	case Season::Autumn:
		return seasonGrowDay[Season::Autumn];
		break;
	case Season::Winter:
		return seasonGrowDay[Season::Winter];
		break;
	}
}

// Apple子类：构造函数
Apple::Apple(const cocos2d::Vec2& posiiton) :
	Crop(CropType::Apple, SEED_GID, position) {
}

// Apple子类：更新函数重写
void Apple::updateGID() {
	switch (growthStage) {
	case 1:

		break;
	case 2:
		break;
	case 3:
		break;
	}
}

// Apple子类：grow函数的重写
void Apple::grow() {
	// 待完善
	growedDay++;
	DateManage* dateManage = DateManage::getInstance();
	Season currentSeason;
	if (dateManage->getCurrentSeason() == "Spring") {
		currentSeason = Season::Spring;
	}
	else if (dateManage->getCurrentSeason() == "Summer") {
		currentSeason = Season::Summer;
	}
	else if (dateManage->getCurrentSeason() == "Autumn") {
		currentSeason = Season::Autumn;
	}
	else {
		currentSeason = Season::Winter;
	}
	growedDay++;
	if (growedDay >= getCurrentSeasonGrowDay(currentSeason)) {
		cropGID = APPLE_GID;
	}
}

// Corn子类：构造函数
Corn::Corn(const cocos2d::Vec2& posiiton) :
	Crop(CropType::Corn, SEED_GID, position) {
}

// Corn子类：grow函数的重写
void Corn::grow() {
	// 待完善
	growedDay++;
	DateManage* dateManage = DateManage::getInstance();
	Season currentSeason;
	if (dateManage->getCurrentSeason() == "Spring") {
		currentSeason = Season::Spring;
	}
	else if (dateManage->getCurrentSeason() == "Summer") {
		currentSeason = Season::Summer;
	}
	else if (dateManage->getCurrentSeason() == "Autumn") {
		currentSeason = Season::Autumn;
	}
	else {
		currentSeason = Season::Winter;
	}
	growedDay++;
	if (growedDay >= getCurrentSeasonGrowDay(currentSeason)) {
		cropGID = CORN_GID;
	}
}

// Carrot子类：构造函数
Carrot::Carrot(const cocos2d::Vec2& posiiton) :
	Crop(CropType::Carrot,SEED_GID, position) {
}

// Carrot子类：生长函数
void Carrot::grow() {
	// 待完善
	growedDay++;
	DateManage* dateManage = DateManage::getInstance();
	Season currentSeason;
	if (dateManage->getCurrentSeason() == "Spring") {
		currentSeason = Season::Spring;
	}
	else if (dateManage->getCurrentSeason() == "Summer") {
		currentSeason = Season::Summer;
	}
	else if (dateManage->getCurrentSeason() == "Autumn") {
		currentSeason = Season::Autumn;
	}
	else {
		currentSeason = Season::Winter;
	}
	growedDay++;
	if (growedDay >= getCurrentSeasonGrowDay(currentSeason)) {
		cropGID = CARROT_GID;
	}
}
