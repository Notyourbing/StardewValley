/****************************************************************
 * File Function: 农药类的具体实现
 * Author:        高鑫
 ****************************************************************/
#include "Agrochemical.h"
#include "../Constant/Constant.h"

USING_NS_CC;

Agrochemical* Agrochemical::create() {
	Agrochemical* agrochemical = new (std::nothrow) Agrochemical();
	if (agrochemical && agrochemical->init()) {
		agrochemical->autorelease();
		return agrochemical;
	}
	CC_SAFE_DELETE(agrochemical);
	return nullptr;
}

bool Agrochemical::init() {
	// 调用基类的初始化方法
	return Tool::init({ "agrochemical", AGROCHEMICAL });
}

// 使用农药
void Agrochemical::useItem() {

}