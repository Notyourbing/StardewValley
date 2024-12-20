/****************************************************************
 * File Function: 肥料类，用于初始化物品中的肥料
 * Author:        高鑫
 ****************************************************************/
#ifndef __FERTILIZER_H_
#define __FERTILIZER_H_

#include "Tool.h"

// Fertilizer类
class Fertilizer : public Tool {
public:
	static Fertilizer* create();

	// 初始化肥料
	bool init() override;

	// 使用工具
	void useItem() override;
};
#endif