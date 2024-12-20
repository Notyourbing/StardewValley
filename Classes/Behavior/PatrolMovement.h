/****************************************************************
 * File Function: 巡逻移动控制类，继承自移动控制基类，控制精灵沿着固定路径移动
 * Author:        高鑫
 ****************************************************************/
#ifndef __PATROLMOVEMENT_H__
#define __PATROLMOVEMENT_H__

#include "cocos2d.h"
#include "MovementBehavior .h"
#include "../Animal/Animal.h"
#include <vector>

// 巡逻移动控制类
class PatrolMovement : public MovementBehavior {
public:
    // 静态构造函数，接受路径点
    static PatrolMovement* create(const std::vector<cocos2d::Vec2>& patrolPoints, float speed, bool loop = true);

    // 初始化
    bool init(const std::vector<cocos2d::Vec2>& patrolTrailPoints, float patrolSpeed, bool patrolLoop = true);

    // 构造函数
    PatrolMovement();

    // 析构函数
    virtual ~PatrolMovement();

    // 执行移动行为函数
    void execute(Animal* animal);

    // 天气影响
    void weatherChanged(float& radius, float& moveDuration) override;

private:
    // 巡逻路径点
    std::vector<cocos2d::Vec2> patrolPoints;

    // 移动速度（像素/秒）
    float baseSpeed;

    // 是否循环巡逻
    bool loop;

    // 当前目标路径点索引
    size_t currentPointIndex;

    // 动物的初始位置
    cocos2d::Vec2 initialPosition;

    // 具体移动实现
    void moveToNextPoint(Animal* animal);

    // 边界检测，确保目标位置在地图内
    cocos2d::Vec2 clampPosition(const cocos2d::Vec2& position, const cocos2d::Size& mapSize);
};

#endif // __PATROLMOVEMENT_H__