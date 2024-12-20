/****************************************************************
 * File Function: 实现斧头类，继承自Tool，用来砍树
 * Author:        赵卓冰
 ****************************************************************/
#ifndef __AXE_H__
#define __AXE_H__

#include "Tool.h"

// 斧头类
class Axe : public Tool {
public:
	// 静态创建方法
	static Axe* create();

	// 初始化斧头
	bool init() override;

	// 使用工具
	void useItem() override;
};
#endif
