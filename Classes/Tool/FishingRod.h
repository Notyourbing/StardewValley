/****************************************************************
 * File Function: 渔具类，继承Tool类，用于实现玩家钓鱼操作
 * Author:        韦瑾钰
 ****************************************************************/
#ifndef __FISHINGROD_H__
#define __FISHINGROD_H__

#include "Tool.h"

class FishingRod : public Tool {
public:
	// 静态创建方法
	static FishingRod* create();

	// 初始化
	bool init();

    // 重载使用工具的函数，执行钓鱼的操作
    void useItem() override;

	// 收回鱼竿的动画
	void reelInRod();

	// 是否正在使用工具
	static bool isUsed;
};
#endif