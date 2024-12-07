#ifndef __KETTLE_H__
#define __KETTLE_H__

#include "Tool.h"
#include "../Constant/Constant.h"

// 水壶类
class Kettle : public Tool {
private:

	// 水壶的含水量
	int waterLevel;

public:
	// 静态创建方法
	static Kettle* create();

	// 水壶的构造函数
	Kettle();

	// 初始化水壶
	bool init();

	// 使用工具
	void useTool() override;

	// 获得当前水壶水量
	int getCurrentWaterLevel() const;

	// 水壶补水
	void refillWateringCan(int water);
};

#endif