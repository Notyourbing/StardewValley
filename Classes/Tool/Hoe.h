#ifndef __HOE_H__
#define __HOE_H__

#include "Tool.h"

// 锄头类
class Hoe : public Tool {
public:
	static Hoe* create();

	// 初始化斧头
	bool init();

	// 使用工具
	void useTool() override;
};

#endif
