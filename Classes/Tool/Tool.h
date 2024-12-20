/****************************************************************
 * File Function: 实现工具类，是抽象类，继承自Item
 * Author:        赵卓冰
 ****************************************************************/

#ifndef __TOOL_H__
#define __TOOL_H__
#include "../Item/Item.h"
#include "cocos2d.h"
#include <string>

// 工具类
class Tool : public Item {
public:
	// 初始化
	virtual bool init(const ItemInfo& item_info) override;

	// 虚析构函数，保证子类析构函数被正确调用
	virtual ~Tool() {}
};
#endif
