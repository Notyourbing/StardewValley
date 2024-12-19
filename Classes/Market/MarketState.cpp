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
	return true;
}

// 出售物品
void MarketState::sellingItems() {

}

// 调整市场中每个物品的价格
void MarketState::adjustItemPrice() {

}