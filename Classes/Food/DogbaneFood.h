/****************************************************************
 * File Function: 防风草物品类，用于描述防风草在背包中的状态
 * Author:        高鑫
 ****************************************************************/
#ifndef __DOGBANEFOOD_H__
#define __DOGBANEFOOD_H__

#include "cocos2d.h"
#include "Food.h"

// 防风草物品类
class DogbaneFood : public Food {
public:
	// 静态创建方法
	static DogbaneFood* create();

	// 初始化防风草食物
	bool init() override;

};
#endif // !__DOGBANEFOOD_H__
