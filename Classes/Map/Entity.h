#ifndef __Entity_H__
#define __Entity_H__

#include "cocos2d.h"
#include "Crop.h"
#include "Animal.h"

class Entity {
protected:
    // 实体类型 (e.g., "crop", "animal")
    std::string type;  
    // 实体所在位置
    Vec2 position;     
public:
    // 构造函数
    Entity(const std::string& entityType, const Vec2& pos)
        : type(entityType), position(pos) {}

    // 获取实体类型
    virtual std::string getType() const {
        return type;
    }

    // 获取位置
    virtual Vec2 getPosition() const {
        return position;
    }

    // 设置位置
    virtual void setPosition(const Vec2& newPosition) {
        position = newPosition;
    }

    // 每日更新逻辑 (虚函数，子类实现具体逻辑)
    //virtual void updateDaily() = 0;

    // 虚析构函数
    virtual ~Entity() {}
};

#endif