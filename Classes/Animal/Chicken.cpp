#include "Chicken.h"
#include "../Behavior/MovementBehavior .h"
#include "../Behavior/PatrolMovement.h"
#include "../Behavior/WanderMovement.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// 静态成员函数，用于创建并返回一个新的Chicken类型对象的实例
Chicken* Chicken::create(const Vec2& position) {
	Chicken* chicken = new (std::nothrow) Chicken(position);
	if (chicken && chicken->init()) {
		chicken->autorelease();
		return chicken;
	}

	CC_SAFE_DELETE(chicken);
	return nullptr;
}
   
// 初始化对象
bool Chicken::init() {
	// 创建鸡的路径
	Vec2 position = getAnimalPosition();
	std::vector<Vec2> patrolPoints = {
	   Vec2(position.x, position.y),
	   Vec2(position.x + PATROL_OFFSET, position.y),
	   Vec2(position.x + PATROL_OFFSET, position.y +PATROL_OFFSET),
	   Vec2(position.x, position.y +PATROL_OFFSET)
	};

	// 创建并设置巡逻移动行为
	PatrolMovement* patrolMovement = PatrolMovement::create(patrolPoints, 100.0f, true);
	if (patrolMovement) {
		setMovementBehavior(patrolMovement);
	}

	return Chicken::initWithFile(CHICKEN);
}

// 构造函数
Chicken::Chicken(const Vec2& position) :
	Animal(position){
	eggCount = 0;
}

// 析构函数
Chicken::~Chicken() {

}

// 设置移动行为
void Chicken::setMovementBehavior(MovementBehavior* behavior) {
	if (behavior) {
		dynamic_cast<PatrolMovement*>(behavior)->execute(this);
	}
}