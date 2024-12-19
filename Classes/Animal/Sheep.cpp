#include "Sheep.h"
#include "../Behavior/MovementBehavior .h"
#include "../Behavior/PatrolMovement.h"
#include "../Behavior/WanderMovement.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// 静态成员函数，用于创建并返回一个新的Sheep类型对象的实例
Sheep* Sheep::create(const Vec2& position) {
	Sheep* sheep = new (std::nothrow) Sheep(position);
	if (sheep && sheep->init()) {
		sheep->autorelease();
		return sheep;
	}

	CC_SAFE_DELETE(sheep);
	return nullptr;
}

// 初始化对象
bool Sheep::init() {
	// ANIMAL初始化
	if (!Animal::initWithFile(SHEEP)) {
		return false;
	}

	// 设置移动行为
	movementBehavior = WanderMovement::create(SHEEP_MOVE_RADIUS, SHEEP_MOVE_INTERVAL);

	// 启动移动调度
	setMovementBehavior(movementBehavior);

	return true;
}

// 构造函数
Sheep::Sheep(const Vec2& position) :
	Animal(position) {
	woolProduction = 0;
}

// 析构函数
Sheep::~Sheep() {

}

// 设置移动行为
void Sheep::setMovementBehavior(MovementBehavior* behavior) {
	if (behavior) {
		dynamic_cast<WanderMovement*>(behavior)->execute(this);
	}
}