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