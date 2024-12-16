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

	virtual ~Tool() {}
};

#endif
