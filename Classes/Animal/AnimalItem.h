/****************************************************************
 * File Function: 动物物品类，牛、鸡、羊、猪的背包物品
 * Author:        高鑫
 ****************************************************************/
#ifndef __AnimalItem_H__
#define __AnimalItem_H__

#include "cocos2d.h"
#include "../Item/Item.h"

// AnimalItem类：表示背包中的动物
class AnimalItem : public Item {
public:
	// 初始化
	virtual bool init(const ItemInfo& item_info) override;

	// 使用工具
	// virtual void useItem() override;

	virtual ~AnimalItem() {}
};

// CowItem类
class CowItem : public AnimalItem {
public:
	// 静态创建方法
	static CowItem* create();

	// 初始化奶牛物品
	bool init();

	// 使用工具
	void useItem() override;
};

// SheepItem类
class SheepItem : public AnimalItem {
public:
	// 静态创建方法
	static SheepItem* create();

	// 初始化羊物品
	bool init();

	// 使用工具
	void useItem() override;
};

// ChickenItem类
class ChickenItem : public AnimalItem {
public:
	// 静态创建方法
	static ChickenItem* create();

	// 初始化鸡物品
	bool init();

	// 使用工具
	void useItem() override;
};

// PigItem类
class PigItem : public AnimalItem {
public:
	// 静态创建方法
	static PigItem* create();

	// 初始化猪物品
	bool init();

	// 使用工具
	void useItem() override;
};
#endif