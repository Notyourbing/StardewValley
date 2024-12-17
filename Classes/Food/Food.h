#ifndef __FOOD_H_
#define __FOOD_H_

#include "cocos2d.h"
#include "../Item/Item.h"
#include "../Constant/Constant.h"

class Food : public Item {
public:
    // 静态创建方法
    static Food* create(const ItemInfo& item_info);

    // 初始化方法
    virtual bool init(const ItemInfo& item_info) override;

    // 重写使用物品
    virtual void useItem() override;

    // 判断是否是相同物品，建议放到Item类中（我不知道为什么放在这里，如果是这个类独有的最好起名isSameFood）
    bool isSameItem(const Food& other) const;

    virtual ~Food() {}
};

#endif // ITEM_H
