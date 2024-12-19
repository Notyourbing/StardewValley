#ifndef __MARKET_ITEM_H__
#define __MARKET_ITEM_H__

#include "cocos2d.h"
#include <string>

/*
 * Class Name:     MarketItem
 * Class Function: 市场单品类
 */
class MarketItem {
public:
	std::string marketItemName;				// 商品名称
	int basePrice;							// 基础价格
	int currentPrice;						// 现在的价格
	int supply;								// 背包中该商品的数量

	// 静态创建函数
	static MarketItem* create(std::string name);

	// 初始化
	bool init();

	// 调整价格
	void adjustPrice();
};

#endif // !__MARKET_ITEM_H__
