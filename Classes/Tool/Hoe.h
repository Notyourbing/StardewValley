/****************************************************************
 * File Function: 实现锄头类，继承自Tool，用来锄地
 * Author:        赵卓冰
 ****************************************************************/
#ifndef __HOE_H__
#define __HOE_H__

#include "Tool.h"

// 锄头类
class Hoe : public Tool {
public:
	// 静态初始化方法
	static Hoe* create();

	// 初始化斧头
	bool init() override;

	// 使用工具
	void useItem() override;
};
#endif
