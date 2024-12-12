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

	// 初始化背包大小
	items.resize(row * capacity, nullptr);
	quantities.resize(row * capacity, 0);
	itemLabels.resize(row * capacity, nullptr);
	selectedIndex = 0;

	// 背包左下角的位置
	const float startX = WINSIZE.width / 2 - (capacity * iconSize + (capacity - 1) * spacing) / 2;
	const float startY = 60.0f; // 背包显示在屏幕底部，距底部 60 像素

	// 背包背景
	bagBackground = Sprite::create(ResPath::BAG_BACKGROUND);
	if (bagBackground) {
		bagBackground->setPosition(Vec2(startX + (capacity * (iconSize + spacing)) / 2, startY + iconSize / 2));
		this->addChild(bagBackground, 0, "bagBackground");
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
	//Tool* cornSeed2 = CornSeed::create();
	//addItem(cornSeed2);
	Tool* carrotSeed = CarrotSeed::create();
	addItem(carrotSeed);
	Tool* fertilizer = Fertilizer::create();
	addItem(fertilizer);
	Food* tuna = Food::create(TUNA);
	addItem(tuna);

	selectItem(0);


	// 创建一个 DrawNode 对象
	auto drawNode = DrawNode::create();

	// 定义正方形的四个顶点
	const float expand = 4.0f;
	Vec2 bottomLeft(-expand, -expand * 1.5f);									// 左下角顶点
	Vec2 bottomRight = bottomLeft + Vec2(iconSize + 2 * expand, 0.0f);	// 右下角定点
	Vec2 topRight = bottomLeft + Vec2(iconSize + 2 * expand, iconSize + 2 * expand);	// 右上角顶点
	Vec2 topLeft = bottomLeft + Vec2(0.0f, iconSize + 2 * expand);		// 左上角顶点

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
			addChild(item);
			quantities[i] = 1;

			// 创建标签并加入背包
			auto label = Label::createWithTTF(std::to_string(quantities[i]), ResPath::FONT_TTF, 14);
			itemLabels[i] = label;
			addChild(label, 3);
			updateDisplay();
			return true;
		}
	}
	return false;
}

// 从背包中移出物品item
void Bag::removeItem(const int index) {
	if (index >= 0 && index < row * capacity && items[index]) {
		// 移出当前物体
		removeChild(items[index]);
		removeChild(itemLabels[index]);
		items[index] = nullptr;
		quantities[index] = 0;
		// 后面的每一个物品向前移
		for (int i = index + 1; i < row * capacity - 1; ++i) {
			if (!items[i]) {
				break;
			}
			items[i - 1] = items[i];
			quantities[i - 1] = quantities[i];
			itemLabels[i - 1] = itemLabels[i];
		}
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

		icon->setVisible(true);
		icon->setPosition(iconPositon);

		// 获取标签并显示标签
		auto label = itemLabels[i];
		if (label && quantities[i]) {
			label->setString(std::to_string(quantities[i])); // 设置数量显示
			const float dPosition = 4.0f;
			label->setPosition(icon->getPosition() + Vec2(iconSize / 2 - dPosition, -iconSize / 2 + dPosition));  // 显示在图标的右下角
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
int Bag::getItemIndex(const std::string& itemName) {
	// 遍历存储工具的位置
	for (int i = 0; i < static_cast<int>(items.size()); i++) {
		if (items[i]->getItemName() == itemName) {
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

const Size& Bag::getContentSize() const {
	// 背包的图像大小就是背包背景的大小
	auto bagBackground = getChildByName("bagBackground");
	return bagBackground->getContentSize();
}