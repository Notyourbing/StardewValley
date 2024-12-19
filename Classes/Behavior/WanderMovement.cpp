#include "WanderMovement.h"
#include "../DateManage/DateManage.h"
#include "../Map/FarmMap.h"
#include "cocos2d.h"

USING_NS_CC;

// 静态构造函数
WanderMovement* WanderMovement::create(float radius,float interval) {
    WanderMovement* wanderMovement = new (std::nothrow) WanderMovement();
    if (wanderMovement && wanderMovement->init(radius,interval)) {
        return wanderMovement;
    }
    CC_SAFE_DELETE(wanderMovement);
    return nullptr;
}

// 静态创建函数的初始化
bool WanderMovement::init(float radius , float interval ) {
    // 移动范围设置
    moveRadius = radius;
    moveInterval = interval;

    return true;
}

// 构造函数
WanderMovement::WanderMovement() {
}

// 析构函数
WanderMovement::~WanderMovement() {

}

// 执行移动
void WanderMovement::execute(Animal* animal) {
    // 初始化位置
    initialPosition = animal->getAnimalPosition();

	// 定时调度 performRandomMove
	animal->schedule([=](float dt) {
		this->performRandomMove(animal);
		}, moveInterval,"WanderMovement_Schedule");


}

void WanderMovement::performRandomMove(Animal* animal){
    // 天气影响
    float radius;
    float moveDuration;
    weatherChanged(radius,moveDuration);

    // 生成随机偏移量
    float angle = CCRANDOM_0_1() * 2 * M_PI; // 随机角度
    float distance = CCRANDOM_0_1() * radius; // 随机距离

    // 计算新的目标位置
    Vec2 offset = Vec2(cos(angle), sin(angle)) * distance;
    Vec2 targetPosition = initialPosition + offset;

    // 确保目标位置在可见范围内（可选）
    float mapWidth = 1980.0f;  // 根据实际地图尺寸调整
    float mapHeight = 1080.0f;  // 根据实际地图尺寸调整
    targetPosition.x = clampf(targetPosition.x, 0.0f, mapWidth);
    targetPosition.y = clampf(targetPosition.y, 0.0f, mapHeight);

    auto moveAction = MoveTo::create(moveDuration, targetPosition);

    animal->runAction(moveAction);
}

// 天气影响
void WanderMovement::weatherChanged(float& radius,float& moveDuration) {
    // 获取当前天气
    DateManage* dateManage = DateManage::getInstance();
    Weather weather = dateManage->getCurrentWeather();

    switch (weather) {
    case Weather::Sunny:
        radius = moveRadius+SUNNY_WANDER_RADIUS_INFLUENCE;
        moveDuration = moveInterval + SUNNY_WANDER_MOVEDURATION_INFLUENCE;
        break;
    case Weather::LightRain:
        radius = moveRadius + LIGHTRAIN_WANDER_RADIUS_INFLUENCE;
        moveDuration = moveInterval +LIGHTRAIN_WANDER_MOVEDURATION_INFLUENCE;
        break;
    case Weather::HeavyRain:
        radius = moveRadius + HEAVYRAIN_WANDER_RADIUS_INFLUENCE;
        moveDuration = moveInterval + HEAVYRAIN_WANDER_MOVEDURATION_INFLUENCE;
        break;
    case Weather::Snowy:
        radius = 0.0f;
        moveDuration = 0.0f;
    }
}