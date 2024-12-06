#ifndef __BAG_H__
#define __BAG_H__
#include "cocos2d.h"
#include "../Tool/Tool.h"
#include "../Item/Item.h"

class Bag : public cocos2d::Node {
public:
	// 单例模式获取背包实例
	static Bag* getInstance();

	// 初始化背包
	bool init();

	// 添加工具到背包
	bool addTool(Tool* tool);

	// 移除工具
	void removeTool(const int index);

	// 获取某个工具
	Tool* getTool(const int index) const;

	// 设置选中的工具
	void selectTool(const int index);

	// 获取当前选中的工具
	Tool* getSelectedTool() const;

	// 显示背包
	void updateDisplay();

	// 当前所拥有的工具
	std::vector<Tool*> tools;

	//向背包中加入物品
	bool addItem(Item* item);

	// 获取背包中的物品
	const std::vector<Item*>& getItems() const;

private:
	// 单例实例
	static Bag* instance;

	std::vector<Item*> items;        // 背包中的物品

	// 私有构造函数，防止多次实例化，确保唯一性
	Bag();
	~Bag();

	// 禁止拷贝和赋值
	Bag(const Bag&) = delete;
	Bag& operator=(const Bag&) = delete;

	// 当前选中的工具索引
	int selectedIndex;

	// 用于显示背包的矩形框和工具
	cocos2d::Sprite* bagBackground;			 // 背景框
	std::vector<cocos2d::Sprite*> toolIcons; // 工具图标

	static const int capacity = 9;			// 背包放工具的容量
	static const int allCapacity = 9;		// 背包总容量
	static const int iconSize = 54;			// 每个图标的宽度/高度
	static const int spacing = 10;			// 图标间距
};
#endif __BAG_H__