#ifndef ITEM_H
#define ITEM_H

#include "cocos2d.h"
#include "../Constant/Constant.h"

class Item : public cocos2d::Sprite {
public:
    const char* name;         // 物品的名称
    const char* imagePath;    // 物品的图标路径
    int quantity;             // 物品的数量
    bool isEdible;                // 是否可食用

    // 默认构造函数
    Item()
        : name(nullptr), imagePath(nullptr), quantity(0), isEdible(false) {}

    static Item* create(const FishInfo& fish_info);

    // 初始化方法
    bool init(const FishInfo& fish_info);

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
