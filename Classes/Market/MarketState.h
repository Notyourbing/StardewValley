#ifndef __MARKETSTATE_H__
#define __MARKETSTATE_H__

#include "cocos2d.h"
#include "MarketGood.h"
#include "../Date/DateManage.h"
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
	std::vector<MarketGood*> marketGoods;

	// 出售物品
	int sellingGoods(const std::string& goodName);
private:
	// 调整市场中每个物品的价格
	void adjustGoodPrice();
};

#endif // !__MARKETSTATE_H__
