/****************************************************************
 * File Function: 篝火类，继承Item类，用于烹饪食物
 * Author:        韦瑾钰
 ****************************************************************/
#ifndef __CampFire_H__
#define __CampFire_H__

#include "Item.h"

// 篝火类，继承自Item类
class CampFire : public Item {
public:
    // 初始化篝火：设置篝火的名称、图片等
    bool init(const ItemInfo& item_info) override;

    // 单例模式获取实例
    static CampFire* getInstance();

    // 创建篝火
    CampFire* create(const ItemInfo& item_info);

    // 使用篝火：将食物烤熟（如果靠近篝火）
    void useItem() override;

    // get set status
    bool getStatus() const { return status; }
    bool setStatus(bool value) { return status = value; }

private:
    // 单例实例
    static CampFire* instance;

    // 篝火状态
    static bool status;
};

#endif // __CampFire_H__
