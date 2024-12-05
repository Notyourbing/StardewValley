#ifndef ITEM_H
#define ITEM_H

#include "cocos2d.h"
#include <string>

class Item : public cocos2d::Sprite {
public:
    std::string name;         // 物品的名称
    std::string imagePath;    // 物品的图标路径
    int quantity;             // 物品的数量

    // 构造函数
    Item(const std::string& itemName, const std::string& itemImagePath, int itemQuantity = 1);

    // 增加物品数量
    void addQuantity(int count);

    // 设置物品数量显示
    void updateQuantityDisplay();

    Item(const Item& other);

    Item& operator=(const Item& other);
    void increaseCount();
    bool isSameItem(const Item& other) const;
};

#endif // ITEM_H
