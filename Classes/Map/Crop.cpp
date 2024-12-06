#include "Crop.h"

// Crop基类：构造函数
Crop::Crop(const CropType& cropType, const int& maxGrowthDay, const int& cropGID, cocos2d::Vec2 position) :
	cropType(cropType), maxGrowthDay(maxGrowthDay), growthStage(0),
	isInfested(false), isDrought(false), isFertilized(false),
	cropGID(cropGID), position(position), infestedDay(0), 
	droughtDay(0) {}

// Crop基类：浇水
void Crop::irrigate() {

	isDrought = false;
	droughtDay = 0;
}

// Crop基类：施肥
void Crop::fertilize() {
	isFertilized = true;
}

// Crop基类：获取成长所需要的天数
int Crop::getMaturedDay() const {
	return maxGrowthDay;
}

// Crop基类：判断是否成熟
bool Crop::isMature() const{

	// 已经超过作物成熟所需要的天数以及及时处理
	if (growedDay >= getMaturedDay() && growedDay <= maxAliveDay) {
		return true;
	}
	return false;
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

// Apple子类：构造函数
Apple::Apple(const cocos2d::Vec2& posiiton) :
	Crop(CropType::APPLE, 28, 34, position) {
	season.push_back(Season::SPRING);
	season.push_back(Season::SUMMER);
	season.push_back(Season::AUTUMN);
}

// Apple子类：生长函数
void Apple::grow() {

	// 判断是否缺水或者遭受虫害
	if (isDrought || isInfested) {
		return;
	}
	
	// 判断是否是施肥
	if (isFertilized) {
		growedDay += 2;
	}
	else {
		growedDay += 1;
	}

	if (growedDay >= 0 && growedDay <= getMaturedDay() / 3) {
		growthStage = 1;
		this->updateGID();
	}
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

// Corn子类：构造函数
Corn::Corn(const cocos2d::Vec2& posiiton) :
	Crop(CropType::APPLE, 36, 34, position) {
	season.push_back(Season::SPRING);
	season.push_back(Season::SUMMER);
}

// Carrot子类：构造函数
Carrot::Carrot(const cocos2d::Vec2& posiiton) :
	Crop(CropType::APPLE, 40, 34, position) {
	season.push_back(Season::SPRING);
}

