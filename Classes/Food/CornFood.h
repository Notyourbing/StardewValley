/****************************************************************
 * File Function: 玉米食物类，用于描述玉米物品在背包中的状态
 * Author:        高鑫
 ****************************************************************/
#ifndef __CORNFOOD_H__
#define __CORNFOOD_H__

#include "cocos2d.h"
#include "Food.h"

// 玉米食物类
class CornFood : public Food {
public:
	// 静态创建方法
	static CornFood* create();

	// 初始化玉米食物
	bool init() override;
};
#endif