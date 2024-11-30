#include "Bag.h"

USING_NS_CC;

Bag* Bag::create() {
	Bag* bag = new (std::nothrow) Bag();
	if (bag && bag->init()) {
		bag->autorelease();
		return bag;
	}
	CC_SAFE_DELETE(bag);
	return nullptr;
}

bool Bag::init() {
	if (!Node::init()) {
		return false;
	}

	// 初始化工具
	tools.resize(capacity, nullptr);
	selectedIndex = -1; // 无法选中工具

	// 创建背包背景框
	bagBackground = DrawNode::create();
	addChild(bagBackground);

	// 初始化工具图标
	for (int i = 0; i < capacity; ++i) {
		auto icon = Sprite::create(); // 空白图标
		icon->setVisible(false);
		addChild(icon);
		toolIcons.push_back(icon);
	}

	// 更新显示
	updateDisplay();

	return true;
}

bool Bag::addTool(Tool* tool) {
	// 检查是否有空位
	for (int i = 0; i < capacity; ++i) {
		if (tools[i] == nullptr) {
			tools[i] = tool;
			updateDisplay();
			return true;
		}
	}
	return false;
}

void Bag::removeTool(int index) {
	if (index >= 0 && index < capacity) {
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
	if (index >= 0 && index < capacity && tools[index] != nullptr) {
		selectedIndex = index;
	}
	updateDisplay();
}

Tool* Bag::getSelectedTool() const {
	if (selectedIndex >= 0 && selectedIndex < capacity) {
		return tools[selectedIndex];
	}
	return nullptr;
}

void Bag::updateDisplay() {
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const float startX = visibleSize.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 50; // 背包显示在屏幕底部，距底部 50 像素

	// 绘制背景框
	bagBackground->clear();
	bagBackground->drawSolidRect(
		Vec2(startX - 10, startY - 10),
		Vec2(startX + capacity * (iconSize + spacing) - spacing + 10, startY + iconSize + 10),
		Color4F(0, 0, 0, 0.5f) // 半透明黑色背景
	);

	// 更新工具图标
	for (int i = 0; i < capacity; ++i) {
		auto icon = toolIcons[i];
		if (tools[i]) {
			icon->setTexture("tools/" + tools[i]->getToolName() + ".png");
			icon->setVisible(true);
		}
		else {
			icon->setVisible(false);
		}

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


	
}