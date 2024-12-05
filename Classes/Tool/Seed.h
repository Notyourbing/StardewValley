#ifndef __SEED_H__
#define __SEED_H__

#include "Tool.h"
#include "cocos2d.h"

// Seed类：继承自工具类，表示物品中的种子
class Seed : public Tool {
private:
public:
	// 静态创建方法
	static Seed* create();

	// 初始化种子
	bool init();

	// 使用工具
	void useTool() override;
};

#endif
