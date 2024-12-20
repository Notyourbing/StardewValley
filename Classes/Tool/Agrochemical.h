/****************************************************************
 * File Function: 农药类，继承自Tool类
 * Author:        高鑫
 ****************************************************************/
#ifndef __AGROCHEMICAL_H__
#define __AGROCHEMICAL_H__

#include "cocos2d.h"
#include "Tool.h"

// 农药类
class Agrochemical : public Tool {
public:
	// 静态创建方法
	static Agrochemical* create();

	// 初始化农药
	bool init() override;

	// 使用工具
	void useItem() override;
};

#endif // !__AGROCHEMICAL_H__
