#ifndef __MARKETSTATE_H__
#define __MARKETSTATE_H__

#include "cocos2d.h"
#include "MarketItem.h"
#include "../DateManage/DateManage.h"
#include <vector>

/*
 * Class Name:     MarketState
 * Class Function: 市场交易类
 */
class MarketState {
public:
	// 静态创建函数
	static MarketState* create();

	// 市场的初始化
	bool init();

	// 用来存储市场上售卖的物品
	std::vector<MarketItem> marketItems;

	// 出售物品
	void sellingItems();
private:
	// 调整市场中每个物品的价格
	void adjustItemPrice();
};

#endif // !__MARKETSTATE_H__
