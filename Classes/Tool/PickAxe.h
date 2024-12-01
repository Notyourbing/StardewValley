#ifndef __PICKAXE_H__
#define __PICKAXE_H__

#include "Tool.h"

// 十字镐类
class Pickaxe : public Tool {
public:
	// 静态创建方法
	static Pickaxe* create();

	// 初始化斧头
	bool init();

	// 使用工具
	void useTool() override;
};

#endif
