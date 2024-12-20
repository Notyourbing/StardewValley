/****************************************************************
 * File Function: 实现工具类，是抽象类，继承自Item
 * Author:        赵卓冰
 ****************************************************************/
#include "Tool.h"
#include "../Map/FarmMap.h"

USING_NS_CC;

// 根据工具名称初始化
bool Tool::init(const ItemInfo& item_info) {
	itemName = (std::string)item_info.name;
	itemImage = (std::string)item_info.image;
	return Sprite::initWithFile(item_info.image);
}