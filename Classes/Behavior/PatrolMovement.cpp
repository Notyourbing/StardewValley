/****************************************************************
 * File Function: 循环移动移动类的实现，控制精灵循环移动，同时受天气等诸多因素影响
 * Author:        高鑫
 ****************************************************************/
#include "PatrolMovement.h"
#include "../Date/DateManage.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// 构造函数
PatrolMovement::PatrolMovement(){

}

// 析构函数
PatrolMovement::~PatrolMovement(){

}

// 静态创建函数
PatrolMovement* PatrolMovement::create(const std::vector<Vec2>& patrolPoints, float speed, bool loop){
    PatrolMovement* ret = new (std::nothrow) PatrolMovement();
    if (ret && ret->init(patrolPoints, speed, loop)) {
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

// 初始化
bool PatrolMovement::init(const std::vector<Vec2>& patrolTrailPoints, float patrolSpeed, bool patrolLoop){
    // 初始化路径点是否为空
    if (patrolTrailPoints.empty()) {
        CCLOG("PatrolMovement: patrolPoints is empty!");
        return false;
    }

    // 初始化路径参数
    patrolPoints= patrolTrailPoints;
    baseSpeed= patrolSpeed;
    loop= patrolLoop;
    currentPointIndex = 0;

    return true;
}

// 执行动物移动
void PatrolMovement::execute(Animal* animal){
    // 判断动物实例
    if (!animal) return;

    // 存储动物的初始位置
    initialPosition= animal->getAnimalPosition();

    // 开始移动到第一个路径点
    moveToNextPoint(animal);
}

void PatrolMovement::moveToNextPoint(Animal* animal){
    // 判断动物实例
    if (!animal) return;

    // 判断巡逻
    if (currentPointIndex >= patrolPoints.size()) {
        if (loop) {
            currentPointIndex = 0;
        }
        else {
            return;     // 不循环，巡逻结束
        }
    }

    Vec2 target = patrolPoints[currentPointIndex];
    currentPointIndex++;

    // 获取地图尺寸，假设地图尺寸通过某种方式传递给 PatrolMovement
    Size mapSize = Director::getInstance()->getVisibleSize(); // 您需要根据实际情况获取地图尺寸

    // 限制目标位置在地图边界内
    target = clampPosition(target, mapSize);

    // 计算移动时间
    float radius= initialPosition.distance(target);
    float moveDuration =0.0f;

    // 天气影响
    weatherChanged(radius,moveDuration);

    // 创建移动动作
    auto moveAction = MoveTo::create(moveDuration, target);

    animal->runAction(moveAction);

    // 移动完成后，继续巡逻
    auto sequence = Sequence::create(moveAction, CallFunc::create([=]() {
        // 继续移动到下一个点
        this->moveToNextPoint(animal);
        }), nullptr);
    animal->runAction(sequence);
}

Vec2 PatrolMovement::clampPosition(const Vec2& position, const Size& mapSize)
{
    // 判断在地图界内
    float clampedX = clampf(position.x, 0.0f, FARMMAP_SIZE_WIDTH);
    float clampedY = clampf(position.y, 0.0f, FARMMAP_SIZE_HEIGHT);
    return Vec2(clampedX, clampedY);
}

void PatrolMovement::weatherChanged(float& radius, float& moveDuration){
    // 获取当前天气
    DateManage* dateManage = DateManage::getInstance();
    Weather weather = dateManage->getCurrentWeather();

    float speed = 0.0f;

    switch (weather) {
    case Weather::Sunny:
        speed = baseSpeed + SUNNY_SPEED_INFLUENCE; // 定义在 Constant.h
        break;
    case Weather::LightRain:
        speed = baseSpeed + LIGHTRAIN_SPEED_INFLUENCE;
        break;
    case Weather::HeavyRain:
        speed = baseSpeed + HEAVYRAIN_SPEED_INFLUENCE;
        break;
    case Weather::Snowy:
        speed = 0.0f; // 停止移动
        break;
    }

    // 计算移动时间，根据当前速度和距离
    moveDuration = (speed > 0) ? (radius / speed) : 1.0f; // 确保持续时间不为0
}
