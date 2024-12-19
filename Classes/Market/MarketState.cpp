#include "MarketState.h"
#include "../Constant/Constant.h"
#include <string>

// 静态创建函数
MarketState* MarketState::create() {
	MarketState* marketState = new (std::nothrow) MarketState();
	if (marketState && marketState->init()) {
		return marketState;
	}

	CC_SAFE_DELETE(marketState);
	return nullptr;
}

// 初始化
bool MarketState::init() {
	// 向市场中加入商品
	for (auto good : INIT_GOODS) {
		MarketGood* marketGood = MarketGood::create(&good);
		marketGoods.push_back(marketGood);
	}
	return true;
}

// 出售物品
int MarketState::sellingGoods(const std::string& goodName) {
	// 先调整市场中的商品价格
	adjustGoodPrice();

	// 遍历市场找到价格
	for (auto good : marketGoods) {
		if (good->getGoodName() == goodName) {
			return good->getGoodPrice();
		}
	}

	// 没找到该商品
	return 0;
}

// 调整市场中每个物品的价格
void MarketState::adjustGoodPrice() {
	// 遍历市场，对每个商品进行价格调整
	for (auto good : marketGoods) {
		good->adjustPrice();
	}
}