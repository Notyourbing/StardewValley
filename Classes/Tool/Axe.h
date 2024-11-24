#ifndef __AXE_H__
#define __AXE_H__

#include "Tool.h"

// 斧头类
class Axe : public Tool {
public:
	// 静态创建方法
	static Axe* create();

	// 初始化斧头
	bool init();

	// 使用工具
	void useTool(const cocos2d::Vec2& targetPosition) override;
};

#endif
