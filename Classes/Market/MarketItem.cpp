#include "MarketItem.h"
#include "../DateManage/DateManage.h"
#include <string>

// 静态创建函数
MarketItem* MarketItem::create(std::string name, int price) {
	MarketItem* marketItem = new (std::nothrow) MarketItem();
	if (marketItem && marketItem->init(name,price)) {
		return marketItem;
	}

	CC_SAFE_DELETE(marketItem);
	return nullptr;
}

// 初始化
bool MarketItem::init(std::string name, int price) {
	marketItemName = name;
	basePrice = price;
	currentPrice = price;
	return true;
}

// 动态调整价格
void MarketItem::adjustPrice() {

}