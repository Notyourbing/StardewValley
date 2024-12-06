#include "Item.h"

// create方法：用于创建并返回初始化的Item对象
Item* Item::create(const FishInfo& fish_info) {
    Item* item = new Item();
    if (item && item->init(fish_info)) {
        return item;
    }
    delete item;  // 初始化失败时，删除对象
    return nullptr;
}

// init方法：用于初始化Item对象的内部状态
bool Item::init(const FishInfo& fish_info) {
    this->name = fish_info.name;
    this->imagePath = fish_info.image;
    this->quantity = fish_info.quantity;
    this->isEdible = fish_info.isEdible;

    // 使用图片路径创建精灵
    this->initWithFile(imagePath);

    // 初始化数量显示（可以使用一个 Label 来显示数量）
    this->updateQuantityDisplay();

    return true;  // 返回true表示初始化成功
}

void Item::addQuantity(int count) {
    quantity += count;
    updateQuantityDisplay();  // 更新数量显示
}

void Item::updateQuantityDisplay() {
    // 显示物品的数量，如果数量大于1则显示
    if (quantity > 1) {
        auto quantityLabel = cocos2d::Label::createWithTTF(std::to_string(quantity), "fonts/arial.ttf", 20);
        quantityLabel->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -10));  // 放置在精灵的下方
        this->addChild(quantityLabel, 1);  // 将数量标签添加到物品精灵下
    }
}

// 拷贝构造函数
Item::Item(const Item& other)
    : name(other.name), imagePath(other.imagePath) {
}

// 赋值操作符
Item& Item::operator=(const Item& other) {
    if (this != &other) {
        name = other.name;
        imagePath = other.imagePath;
    }
    return *this;
}

void Item::increaseCount() {
    quantity++;
}

bool Item::isSameItem(const Item& other) const {
    return name == other.name;
}