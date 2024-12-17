#ifndef __CORNCROP_H__
#define __CORNCROP_H__

#include "cocos2d.h"
#include "Crop.h"

/*
 * Class Name:     Corn
 * Class Function: 玉米作物类
 */
class Corn : public Crop {
public:
	// 静态创建函数
	static Corn* create();

	// 初始化
	bool init() override;

	// 构造函数
	Corn();

	// 玉米的生长函数
	void grow() override;

	// 随机产生病害
	void generatePest() override;
};

#endif // 
