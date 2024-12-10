#include "Bag.h"
#include "../Tool/Axe.h"
#include "../Tool/PickAxe.h"
#include "../Tool/Hoe.h"
#include "../Tool/Scythe.h"
#include "../Tool/FishingRod.h"
#include "../Tool/Kettle.h"
#include "../Player/Player.h"
#include "../Tool/Seed.h"
#include "../Tool/Fertilizer.h"
#include "../Constant/Constant.h"

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

Bag::Bag() {}

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
	items.resize(row * capacity, nullptr);
	quantities.resize(row * capacity, 0);
	selectedIndex = 0;

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const float startX = visibleSize.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 60.0f; // 背包显示在屏幕底部，距底部 60 像素


	bagBackground = Sprite::create(ResPath::BAG_BACKGROUND);
	if (bagBackground) {
		bagBackground->setPosition(Vec2(startX + (capacity * (iconSize + spacing)) / 2, startY + iconSize / 2));
		this->addChild(bagBackground, 0);
	}


	// 初始化工具图标
	for (int i = 0; i < row * capacity; ++i) {
		auto icon = Sprite::create(); // 空白图标
		icon->setVisible(false);
		itemIcons.push_back(icon);
		auto label = Label::createWithTTF(std::to_string(quantities[i]), "fonts/arial.ttf", 30);
		label->setVisible(false);
		itemLabels.push_back(label);
		addChild(icon, 1);
		addChild(label, 2);
	}

	// 更新显示
	updateDisplay();

	Tool* axe = Axe::create();
	addItem(axe);
	Tool* pickaxe = Pickaxe::create();
	addItem(pickaxe);
	Tool* hoe = Hoe::create();
	addItem(hoe);
	Tool* fisingRod = FishingRod::create();
	addItem(fisingRod);
	Tool* scythe = Scythe::create();
	addItem(scythe);
	Tool* kettle = Kettle::create();
	addItem(kettle);
	Tool* appleSeed = AppleSeed::create();
	addItem(appleSeed);
	Tool* cornSeed = CornSeed::create();
	addItem(cornSeed);
	Tool* carrotSeed = CarrotSeed::create();
	addItem(carrotSeed);
	Tool* fertilizer = Fertilizer::create();
	addItem(fertilizer);
	selectItem(0);

	return true;
}

bool Bag::addItem(Item* item) {
	// 检查是否有空位
	for (int i = 0; i < row * capacity; ++i) {
		if (items[i] && (item->getItemName() == items[i]->getItemName())) {
			quantities[i]++;
			updateDisplay();
			return true;
		}
		if (items[i] == nullptr) {
			items[i] = item;
			quantities[i] = item->getQuantity();
			addChild(item);
			auto icon = Sprite::create(item->getItemImage());
			itemIcons[i] = icon;
			addChild(icon);
			updateDisplay();
			return true;
		}
	}
	return false;
}

void Bag::removeItem(const int index) {
	if (index >= 0 && index < row * capacity && items[index]) {
		removeChild(items[index]);
		items[index] = nullptr;
		updateDisplay();
	}
}

Item* Bag::getItem(const int index) const {
	if (index >= 0 && index < row * capacity) {
		return items[index];
	}
	return nullptr;
}

void Bag::selectItem(const int index) {
	if (index >= 0 && index < row * capacity && items[index]) {
		selectedIndex = index;
		Player::getInstance()->setCurrentItem(items[index]);
	}
	updateDisplay();
}

Item* Bag::getSelectedItem() const {
	if (selectedIndex >= 0 && selectedIndex < capacity && items[selectedIndex]) {
		return items[selectedIndex];
	}
	return nullptr;
}

void Bag::updateDisplay() {
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const float startX = visibleSize.width / 2 - (capacity * iconSize + (capacity - 2) * spacing) / 2;
	const float startY = 100.0f; // 背包显示在屏幕底部，距底部 100 像素

	// 更新工具图标
	for (int i = 0; i < row * capacity; ++i) {
		auto icon = itemIcons[i];
		auto label = itemLabels[i];
		if (items[i]) {
			icon->setTexture("tools/" + items[i]->getItemName() + ".png");
			icon->setVisible(true);

			// 设置数量显示
			if (quantities[i] > 1) {
				label->setString(std::to_string(quantities[i]));
				label->setVisible(true);
				
			}

		}
		else
			icon->setVisible(false);

		// 设置位置
		icon->setPosition(Vec2(
			startX + i % capacity * (iconSize + spacing)  + iconSize / 2,
			startY + iconSize / 2 - (iconSize + spacing) * (i / capacity)
		));
		label->setPosition(icon->getPosition() + Vec2(20, 20));  // 显示在图标的右上角
		// 如果是选中工具,添加高亮
		if (i == selectedIndex) {
			icon->setColor(Color3B::YELLOW);
		}
		else {
			icon->setColor(Color3B::WHITE);
		}
	}
}

// 获取工具的索引
int Bag::getToolIndex(std::string toolName) {
	// 遍历存储工具的位置
	for (int i = 0; i < static_cast<int>(items.size()); i++) {
		if (items[i]->getItemName() == toolName) {
			return i;
		}
	}
}