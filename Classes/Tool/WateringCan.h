#ifndef __KETTLE_H__
#define __KETTLE_H__

#include "Tool.h"

// 水壶类
class Kettle : public Tool {
public:
	// 静态创建方法
	static Kettle* create();

	// 初始化水壶
	bool init();

	// 使用工具
	void useTool() override;
};

#endif