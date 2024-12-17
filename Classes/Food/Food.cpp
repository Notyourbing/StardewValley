#include "Food.h"

// create方法：用于创建并返回初始化的Food对象
Food* Food::create(const ItemInfo& item_info) {
    Food* food = new (std::nothrow) Food();

    // 使用 item_info 初始化 Food 的状态
    if (food && food->init(item_info)) {
        food->autorelease();
        return food;
    }
    else {
        CC_SAFE_DELETE(food);
        return nullptr;
    }
}

// init方法：用于初始化Food对象的内部状态
bool Food::init(const ItemInfo& item_info) {
    itemName = item_info.name;
    itemImage = item_info.image;
    return Sprite::initWithFile(item_info.image);
}

void Food::useItem()
{
}

bool Food::isSameItem(const Food& other) const {
    return itemName == other.itemName;
}