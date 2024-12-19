#include "cocos2d.h"
#include "Cow.h"
#include "FarmMap.h"
#include "../Behavior/WanderMovement.h"
#include "../Behavior/MovementBehavior .h"
#include "../Constant/Constant.h"

USING_NS_CC;

// 静态函数，创建并返回Cow对象
Cow* Cow::create(Vec2 position) {
	Cow* cow = new (std::nothrow) Cow(position);
	if (cow && cow->init()) {
		cow->autorelease();
		return cow;
	}
	CC_SAFE_DELETE(cow);
	return nullptr;
}

// 初始化对象
bool Cow::init(){
    // ANIMAL初始化
    if (!Animal::initWithFile(COW)) {
        return false;
    }

    // 设置牛的移动行为
    movementBehavior = WanderMovement::create(COW_MOVE_RADIUS,COW_MOVE_INTERVAL);

    // 启动移动调度
    setMovementBehavior(movementBehavior);

    return true;
}

// Cow类：构造函数
Cow::Cow(Vec2 position) :
	Animal(position) {
	milkProduction = 0;
}

// Cow类：析构函数
Cow::~Cow() {

}

// 设置移动行为
void Cow::setMovementBehavior(MovementBehavior* behavior){
    if (behavior) {
        dynamic_cast<WanderMovement*>(behavior)->execute(this);
    }
}