/****************************************************************
 * File Function: 物品类，抽象基类，用于放入背包中
 * Author:        赵卓冰 韦瑾钰
 ****************************************************************/
#ifndef __Item_H__
#define __Item_H__

#include "cocos2d.h"
#include "../Constant/Constant.h"
#include <string>

// 物品类，是一个抽象类
class Item : public cocos2d::Sprite {
public:
	// 初始化（纯虚函数，子类必须实现）
	virtual bool init(const ItemInfo& item_info) = 0;

	// 使用物品（纯虚函数，子类必须实现）
	virtual void useItem() = 0;

	// 获取工具名称，内联函数，直接实现
	std::string getItemName() const {
		return itemName;
	}

	//获取图片位置
	std::string getItemImage() const {
		return itemImage;
	}

	// 虚析构函数
	virtual ~Item() {}
protected:
	// 名称
	std::string itemName;
	// 图片位置
	std::string itemImage;
};

#endif
