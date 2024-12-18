#ifndef __BAG_H__
#define __BAG_H__
#include "cocos2d.h"
#include "../Tool/Tool.h"
#include "../Food/Food.h"

class Bag : public cocos2d::Node {
public:
	// 单例模式获取背包实例
	static Bag* getInstance();

	// 初始化背包
	bool init();

	// 添加物品到背包
	bool addItem(Item* item);
		
	// 移除物品
	void removeItem(const int index);

	// 获取某个物品
	Item* getItem(const int index) const;

	// 设置选中的物品
	void setSelectedItem(const int index);

	// 获取当前选中的物品
	Item* getSelectedItem() const;

	// 显示背包
	void updateDisplay();
	
	// 获取背包大小，也就是不同物品的个数
	int getSize();

	// 获取背包中物品的索引
	int getItemIndex(const std::string& itemName);

	// 获取当前选中物品的索引
	int getSelectedIndex() {
		return selectedIndex;
	}

	// 重写基类成员函数getContentSize()
	const cocos2d::Size& getContentSize() const override;

	// 清空背包
	void clearBag();

	//设置物品到指定索引
	void setItem(const int index, Item* item, const int quantity);

	// 获取总容量
	int getTotalCapacity() const;

	// 获取所有物品的向量
	const std::vector<Item*>& getItems() const;

	// 获取所有物品的数量
	const std::vector<int>& getQuantities() const;

	// 查看背包中是否有目标物品
	bool checkItemIn(const std::string& targetName);
private:
	// 单例实例
	static Bag* instance;

	// 私有构造函数，防止多次实例化，确保唯一性
	Bag();
	~Bag();

	// 禁止拷贝和赋值
	Bag(const Bag&) = delete;
	Bag& operator=(const Bag&) = delete;

	// 当前选中的物品索引
	int selectedIndex;

	// 背景框
	cocos2d::Sprite* bagBackground;

	// 当前所拥有的物品
	std::vector<Item*> items;

	// 物品数量标签
	std::vector<cocos2d::Label*> itemLabels;

	// 每个物品的数量
	std::vector<int> quantities;

	// 静态常量
	static const int capacity = 9;			 // 背包放物品的一行容量
	static const int row = 2;				 // 2行
	static const int iconSize = 54;			 // 每个图标的宽度/高度
	static const int spacing = 10;			 // 图标间距
};
#endif __BAG_H__