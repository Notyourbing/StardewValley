/****************************************************************
 * File Function: 实现十字镐类，继承自Tool,十字镐可以挖矿和石头
 * Author:        韦瑾钰 赵卓冰
 ****************************************************************/
#ifndef __PICKAXE_H__
#define __PICKAXE_H__

#include "Tool.h"

// 十字镐类
class Pickaxe : public Tool {
public:
	// 静态创建方法
	static Pickaxe* create();

	// 初始化十字镐
	bool init();

	// 使用工具
	void useItem() override;
};
#endif