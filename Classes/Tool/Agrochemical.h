#ifndef __AGROCHEMICAL_H__
#define __AGROCHEMICAL_H__

#include "cocos2d.h"
#include "Tool.h"

class Agrochemical : public Tool {
public:
	// 静态创建方法
	static Agrochemical* create();

	// 初始化农药
	bool init() override;

	// 使用工具
	void useItem() override;
};

#endif
