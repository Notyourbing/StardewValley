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

	// 背包的左下角位置
	const float startX = WINSIZE.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 60.0f; // 背包显示在屏幕底部，距底部 60 像素

	bagBackground = Sprite::create(ResPath::BAG_BACKGROUND);
	if (bagBackground) {
		bagBackground->setPosition(Vec2(startX + (capacity * (iconSize + spacing)) / 2, startY + iconSize / 2));
		this->addChild(bagBackground, 0);
	}

	// 初始化工具图标
	for (int i = 0; i < row * capacity; ++i) {
		auto label = Label::createWithTTF(std::to_string(quantities[i]), ResPath::FONT_TTF, 30);
		label->setVisible(false);
		itemLabels.push_back(label);
		addChild(label, 2);
	}

	// 添加初始化的物品
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

	// 创建一个 DrawNode 对象
	auto drawNode = DrawNode::create();

	// 定义正方形的四个顶点
	Vec2 bottomLeft(0,0);									// 左下角顶点
	Vec2 bottomRight = bottomLeft + Vec2(iconSize, 0.0f);	// 右下角定点
	Vec2 topRight = bottomLeft + Vec2(iconSize, iconSize);	// 右上角顶点
	Vec2 topLeft = bottomLeft + Vec2(0.0f, iconSize);		// 左上角顶点

	// 使用 drawPolygon 绘制红色边框的正方形
	Vec2 vertices[] = { bottomLeft, bottomRight, topRight, topLeft };
	drawNode->drawPolygon(
		vertices,               // 顶点数组
		4,                      // 顶点个数
		Color4F(0, 0, 0, 0),    // 填充颜色（透明）
		2.0f,                   // 边框宽度
		Color4F::RED            // 边框颜色（红色）
	);
	addChild(drawNode, 2, "drawNode");

	// 更新显示
	updateDisplay();
	return true;
}

bool Bag::addItem(Item* item) {
	// 遍历整个背包
	for (int i = 0; i < row * capacity; ++i) {
		// 要加入的物品已经在背包中存在
		if (items[i] && (item->getItemName() == items[i]->getItemName())) {
			quantities[i]++;
			updateDisplay();
			return true;
		}
		// 找到了一个空位
		if (items[i] == nullptr) {
			items[i] = item;
			quantities[i] = item->getQuantity();
			addChild(item);
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
	const auto WINSIZE = Director::getInstance()->getVisibleSize();
	const float startX = WINSIZE.width / 2 - (capacity * iconSize + (capacity - 2) * spacing) / 2;
	const float startY = 100.0f; // 背包显示在屏幕底部，距底部 100 像素

	// 更新工具图标
	for (int i = 0; i < row * capacity; ++i) {
		auto icon = items[i];
		if (icon == nullptr) {
			continue;
		}
		const auto iconPositon = Vec2(
			startX + i % capacity * (iconSize + spacing) + iconSize / 2,
			startY + iconSize / 2 - (iconSize + spacing) * (i / capacity));

		auto label = itemLabels[i];
		icon->setVisible(true);
	
		// 设置位置
		icon->setPosition(iconPositon);
		if (label) {
			label->setPosition(icon->getPosition() + Vec2(20, 20));  // 显示在图标的右上角
			// 数量超过一个
			if (quantities[i] > 1) {
				label->setString(std::to_string(quantities[i])); // 设置数量显示
			}
		}

		// 红色矩形框
		if (i == selectedIndex) {
			auto drawNode = getChildByName("drawNode");
			if (drawNode) {
				drawNode->setPosition(iconPositon - Vec2(iconSize / 2, iconSize / 2));
			}
		}

		// 如果是选中物品,添加高亮
		if (i == selectedIndex) {
			icon->setColor(Color3B::ORANGE);
		}
		else {
			icon->setColor(Color3B::WHITE);
		}
	}
}

// 获取工具的索引
int Bag::getToolIndex(const std::string& toolName) {
	// 遍历存储工具的位置
	for (int i = 0; i < static_cast<int>(items.size()); i++) {
		if (items[i]->getItemName() == toolName) {
			return i;
		}
	}
	return 0; // 没找到就默认第一个
}

int Bag::getSize() {
	for (int i = 0; i < row * capacity; ++i) {
		if (items[i] == nullptr) {
			return i;
		}
	}
	return row * capacity;
}