/****************************************************************
 * File Function: 胡萝卜食物类，用于描述胡萝卜物品在背包中的状态
 * Author:        高鑫
 ****************************************************************/
#ifndef __CARROTFOOD_H__
#define __CARROTFOOD_H__

#include "cocos2d.h"
#include "Food.h"

// 胡萝卜食物类
class CarrotFood : public Food {
public:
	// 静态创建方法
	static CarrotFood* create();

	// 初始化胡萝卜食物
	bool init() override;
};
#endif 