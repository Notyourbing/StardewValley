#include "Bag.h"
#include "../Tool/Axe.h"
#include "../Tool/PickAxe.h"
#include "../Tool/Hoe.h"
#include "../Tool/Scythe.h"
#include "../Tool/FishingRod.h"
#include "../Tool/WateringCan.h"
#include "../Player/Player.h"
#include "../Tool/Seed.h"

USING_NS_CC;

// 初始化静态成员变量
Bag* Bag::instance = nullptr;

Bag* Bag::getInstance() {
	if (instance == nullptr) {
		instance = new (std::nothrow) Bag();
		if (instance && instance->init()) {
			instance->autorelease();
		}
		else {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

Bag::Bag(): selectedIndex(0) {}

Bag::~Bag() {
	if (instance != nullptr) {
		instance = nullptr;
	}
}

bool Bag::init() {
	if (!Node::init()) {
		return false;
	}

	// 初始化工具
	tools.resize(capacity, nullptr);
	selectedIndex = 0;

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const float startX = visibleSize.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 50.0f; // 背包显示在屏幕底部，距底部 50 像素


	bagBackground = Sprite::create("icon/bagBackground.png");
	if (bagBackground) {
		bagBackground->setPosition(Vec2(startX + (capacity * (iconSize + spacing)) / 2, startY + iconSize / 2));
		this->addChild(bagBackground, 0);
	}


	// 初始化工具图标
	for (int i = 0; i < capacity; ++i) {
		auto icon = Sprite::create(); // 空白图标
		icon->setVisible(false);
		addChild(icon);
		toolIcons.push_back(icon);
	}

	// 更新显示
	updateDisplay();

	Tool* axe = Axe::create();
	addTool(axe);
	Tool* pickaxe = Pickaxe::create();
	addTool(pickaxe);
	Tool* hoe = Hoe::create();
	addTool(hoe);
	Tool* fisingRod = FishingRod::create();
	addTool(fisingRod);
	Tool* scythe = Scythe::create();
	addTool(scythe);
	Tool* kettle = Kettle::create();
	addTool(kettle);
	Tool* seed = Seed::create();
	addTool(seed);
	selectTool(0);

	return true;
}

bool Bag::addTool(Tool* tool) {
	// 检查是否有空位
	for (int i = 0; i < capacity; ++i) {
		if (tools[i] == nullptr) {
			tools[i] = tool;
			addChild(tool);
			updateDisplay();
			return true;
		}
	}
	return false;
}

void Bag::removeTool(int index) {
	if (index >= 0 && index < capacity && tools[index]) {
		removeChild(tools[index]);
		tools[index] = nullptr;
		updateDisplay();
	}
}

Tool* Bag::getTool(int index) const {
	if (index >= 0 && index < capacity) {
		return tools[index];
	}
	return nullptr;
}

void Bag::selectTool(int index) {
	if (index >= 0 && index < capacity && tools[index]) {
		selectedIndex = index;
		Player::getInstance()->setCurrentTool(tools[index]);
	}
	updateDisplay();
}

Tool* Bag::getSelectedTool() const {
	if (selectedIndex >= 0 && selectedIndex < capacity && tools[selectedIndex]) {
		return tools[selectedIndex];
	}
	return nullptr;
}

void Bag::updateDisplay() {
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const float startX = visibleSize.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 50.0f; // 背包显示在屏幕底部，距底部 50 像素

	// 更新工具图标
	for (int i = 0; i < capacity; ++i) {
		auto icon = toolIcons[i];
		if (tools[i]) {
			icon->setTexture("tools/" + tools[i]->getToolName() + ".png");
			icon->setVisible(true);
		}
		else
			icon->setVisible(false);

			// 设置位置
			icon->setPosition(Vec2(
				startX + i * (iconSize + spacing) + iconSize / 2,
				startY + iconSize / 2
			));

			// 如果是选中工具,添加高亮
			if (i == selectedIndex) {
				icon->setColor(Color3B::YELLOW);
			}
			else {
				icon->setColor(Color3B::WHITE);
			}
	}

	//更新item图标
	for (int i = 0; i < items.size(); i++) {
		if (i + tools.size() < capacity) {
			items[i]->setPosition(Vec2(
				startX + i * (iconSize + spacing) + iconSize / 2,
				startY + iconSize / 2
			));
		}
	}
}

bool Bag::addItem(Item* item) {
	// 判断背包中是否已经存在相同的物品
	for (auto& existingItem : items) {
		if (existingItem->isSameItem(*item)) {
			// 如果物品存在，增加数量
			existingItem->increaseCount();
			updateDisplay();  // 更新显示
			return true;
		}
	}

	// 如果没有找到相同的物品，添加新的物品
	if (tools.size() + items.size() < capacity) {
		items.push_back(item);  // 添加新物品
		addChild(item);         // 将物品添加到场景中
		updateDisplay();        // 更新显示
		return true;
	}
	return false;
}

const std::vector<Item*>& Bag::getItems() const
{
	return items;
}
