#ifndef __MILKINGPAIL_H__
#define __MILKINGPAIL_H__

#include "cocos2d.h"
#include "Tool.h"

// MilkPail类：挤奶桶
class MilkPail : public Tool {
public:
	// 静态创建方法
	static MilkPail* create();

	// 初始化挤奶桶
	bool init() override;

	// 使用工具
	void useItem() override;
};
#endif