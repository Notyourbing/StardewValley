#include "Food.h"

// create方法：用于创建并返回初始化的Food对象
Food* Food::create(const FishInfo& fish_info) {
    Food* food = new Food();
    if (food && food->init(fish_info)) {
        return food;
    }
    delete food;  // 初始化失败时，删除对象
    return nullptr;
}

// init方法：用于初始化Food对象的内部状态
bool Food::init(const FishInfo& fish_info) {
    name = fish_info.name;
    imagePath = fish_info.image;
    quantity = fish_info.quantity;

    // 使用图片路径创建精灵
    initWithFile(imagePath);

    // 初始化数量显示（可以使用一个 Label 来显示数量）
    updateQuantityDisplay();

    return true;  // 返回true表示初始化成功
}

void Food::addQuantity(int count) {
    quantity += count;
    updateQuantityDisplay();  // 更新数量显示
}

void Food::updateQuantityDisplay() {
    // 显示物品的数量，如果数量大于1则显示
    if (quantity > 1) {
        auto quantityLabel = cocos2d::Label::createWithTTF(std::to_string(quantity), "fonts/arial.ttf", 20);
        quantityLabel->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, -10));  // 放置在精灵的下方
        addChild(quantityLabel, 1);  // 将数量标签添加到物品精灵下
    }
}

// 拷贝构造函数
Food::Food(const Food& other)
    : name(other.name), imagePath(other.imagePath) {
}

// 赋值操作符
Food& Food::operator=(const Food& other) {
    if (this != &other) {
        name = other.name;
        imagePath = other.imagePath;
    }
    return *this;
}

void Food::increaseCount() {
    quantity++;
}

bool Food::isSameItem(const Food& other) const {
    return name == other.name;
}