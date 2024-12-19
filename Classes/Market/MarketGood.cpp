#include "MarketGood.h"
#include "../DateManage/DateManage.h"
#include <string>

// 静态创建函数
MarketGood* MarketGood::create(MarketGoodLabel* good) {
	MarketGood* marketGood = new (std::nothrow) MarketGood();
	if (marketGood && marketGood->init(good->name,good->basePrice)) {
		return marketGood;
	}

	CC_SAFE_DELETE(marketGood);
	return nullptr;
}

// 初始化
bool MarketGood::init(std::string name, int price) {
	// 初始化商品
	marketGoodName = name;
	basePrice = price;
	currentPrice = price;
	return true;
}

// 动态调整价格
void MarketGood::adjustPrice() {
	// 石头的价格固定不变
	if (getGoodName() == "stoneItem") {
		return;
	}
	// 获取当前季节与天气
	DateManage* dateManage = DateManage::getInstance();
	std::string season = dateManage->getCurrentSeason();
	Weather weather = dateManage->getCurrentWeather();

	// 季节的影响
	if (season == "Spring") {
		currentPrice = basePrice;
	}
	else if (season == "Summer") {
		currentPrice = basePrice / 2;
	}
	else if (season == "Fall") {
		currentPrice = basePrice * 3 / 2;
	}
	else {
		currentPrice = basePrice * 2;
	}

	switch(weather){
	case Weather::Sunny:
		currentPrice += SUNNY_MONEY_INFLUENCE;
		break;
	case Weather::LightRain:
		currentPrice += LIGHTRAIN_MONEY_INFLUENCE;
		break;
	case Weather::HeavyRain:
		currentPrice += HEAVYRAIN_MONEY_INFLUENCE;
		break;
	case Weather::Snowy:
		currentPrice += SNOWY_MONEY_INFLUENCE;
		break;
	}
}

// 获取商品名称
std::string MarketGood::getGoodName() const {
	return marketGoodName;
}

// 获取商品价格
int MarketGood::getGoodPrice() const {
	return currentPrice;
}