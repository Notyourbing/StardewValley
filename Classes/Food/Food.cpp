#include "Food.h"

// create方法：用于创建并返回初始化的Food对象
Food* Food::create(const ItemInfo& item_info) {
    Food* food = new Food();

    // 使用 item_info 初始化 Food 的状态
    if (food && food->init(item_info)) {

        // 初始化数量显示
        food->updateQuantityDisplay();

        return food;
    }

    delete food;  // 初始化失败时，删除对象
    return nullptr;
}


// init方法：用于初始化Food对象的内部状态
bool Food::init(const ItemInfo& item_info) {
    itemName = item_info.name;
    itemImage = item_info.image;
    quantity = item_info.quantity;
    return true;  // 返回true表示初始化成功
}

void Food::useItem()
{
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

//// 拷贝构造函数
//Food::Food(const Food& other)
//    : itemName(other.itemName), itemImage(other.itemImage) {
//}
//
//// 赋值操作符
//Food& Food::operator=(const Food& other) {
//    if (this != &other) {
//        name = other.name;
//        imagePath = other.imagePath;
//    }
//    return *this;
//}

void Food::increaseCount() {
    quantity++;
}

bool Food::isSameItem(const Food& other) const {
    return itemName == other.itemName;
}