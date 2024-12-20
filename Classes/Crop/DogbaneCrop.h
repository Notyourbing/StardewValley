/****************************************************************
 * File Function: 防风草作物类，继承自Crop抽象基类，实现防风草的生长逻辑
 * Author:        高鑫
 ****************************************************************/
#ifndef __DOGBANE_CROP_H__
#define __DOGBANE_CROP_H__

#include "cocos2d.h"
#include "Crop.h"

// 防风草作物类
class Dogbane : public Crop {
public:
	// 静态创建函数
	static Dogbane* create();

	// 初始化
	bool init() override;

	// 构造函数
	Dogbane();

	// 生长函数
	void grow() override;

	// 产生病害
	void generatePest() override;
};

#endif 