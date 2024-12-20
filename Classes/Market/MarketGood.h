/****************************************************************
 * File Function: 市场单品类，用于初始化市场中的商品，并实现价格动态变化
 * Author:        高鑫
 ****************************************************************/
#ifndef __MARKET_ITEM_H__
#define __MARKET_ITEM_H__

#include "cocos2d.h"
#include "../Constant/Constant.h"
#include <string>

// 市场单品类
class MarketGood {
public:
	// 静态创建函数
	static MarketGood* create(MarketGoodLabel* good);

	// 初始化
	bool init(std::string name, int price);

	// 调整价格
	void adjustPrice();

	// 获取商品名称
	std::string getGoodName() const;

	// 获取商品价格
	int getGoodPrice() const;
private:
	std::string marketGoodName;				// 商品名称
	int basePrice;							// 基础价格
	int currentPrice;						// 现在的价格
};

#endif // !__MARKET_ITEM_H__
