#ifndef __FOOD_H_
#define __FOOD_H_

#include "cocos2d.h"
#include "../Constant/Constant.h"

class Food : public cocos2d::Sprite {
public:
    const char* name;         // 物品的名称
    const char* imagePath;    // 物品的图标路径
    int quantity;             // 物品的数量

    // 默认构造函数
    Food()
        : name(nullptr), imagePath(nullptr), quantity(0) {}

    static Food* create(const FishInfo& fish_info);

    // 初始化方法
    bool init(const FishInfo& fish_info);

    // 增加物品数量
    void addQuantity(int count);

    // 设置物品数量显示
    void updateQuantityDisplay();

    Food(const Food& other);

    Food& operator=(const Food& other);
    void increaseCount();
    bool isSameItem(const Food& other) const;
};

#endif // ITEM_H
