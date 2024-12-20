/****************************************************************
 * File Function: MilkingPail类的具体实现
 * Author:        高鑫
 ****************************************************************/
#include "MilkingPail.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// MilkPail类：静态创建函数
MilkPail* MilkPail::create() {
	MilkPail* milkPail = new (std::nothrow) MilkPail();
	if (milkPail && milkPail->init()) {
		milkPail->autorelease();
		return milkPail;
	}
	CC_SAFE_DELETE(milkPail);
	return nullptr;
}

// MilkPail类：初始化挤奶桶
bool MilkPail::init() {
	// 调用基类的初始化方法
	return Tool::init({ "milkPail", MILKPAIL });
}

// MilkPail类：使用工具
void MilkPail::useItem() {

}