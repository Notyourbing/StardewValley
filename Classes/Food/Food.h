#ifndef __FOOD_H_
#define __FOOD_H_

#include "cocos2d.h"
#include "../Item/Item.h"
#include "../Constant/Constant.h"

class Food : public Item {
public:
    Food() {};

    static Food* create(const ItemInfo& item_info);

    // 初始化方法
    virtual bool init(const ItemInfo& item_info) override;

    virtual void useItem() override;

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
