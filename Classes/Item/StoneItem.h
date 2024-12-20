/****************************************************************
 * File Function: 石头类，继承Item类，被稿子挖下的石头以Item子类的方式存储于背包中
 * Author:        韦瑾钰
 ****************************************************************/
#ifndef __STONEITEM_H__
#define __STONEITEM_H__

#include "Item.h"
#include "cocos2d.h"

class StoneItem : public Item {
public:
	// 静态创建函数
	static StoneItem* create(const ItemInfo& item_info) {
		StoneItem* stoneItem = new (std::nothrow) StoneItem();

		// 使用 item_info 初始化状态
		if (stoneItem && stoneItem->init(item_info)) {
			stoneItem->autorelease();
			return stoneItem;
		}
		else {
			CC_SAFE_DELETE(stoneItem);
			return nullptr;
		}
	}
	// 初始化）
	bool init(const ItemInfo& item_info) override {
		itemName = item_info.name;
		itemImage = item_info.image;
		return Sprite::initWithFile(item_info.image);
	}

	// 重写使用工具
	void useItem() override {};
};

#endif 
