/****************************************************************
 * File Function: 食物类，是一个抽象基类，继承Item类，能够放入背包，同时可以进行烹饪
 * Author:        韦瑾钰
 ****************************************************************/
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
    virtual void useItem() override {};

    // 析构函数
    virtual ~Food() {}
};

#endif // ITEM_H
