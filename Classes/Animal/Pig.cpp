#include "Pig.h"
#include "../Behavior/MovementBehavior .h"
#include "../Behavior/WanderMovement.h"
#include "../Behavior/PatrolMovement.h"
#include "../Constant/Constant.h"

USING_NS_CC;

// 静态成员函数，用于创建并返回一个新的Sheep类型对象的实例
Pig* Pig::create(const Vec2& position) {
	Pig* pig = new (std::nothrow) Pig(position);
	if (pig && pig->init()) {
		pig->autorelease();
		return pig;
	}

	CC_SAFE_DELETE(pig);
	return nullptr;
}

// 初始化对象
bool Pig::init() {
	// 创建猪的路径
	Vec2 position = getAnimalPosition();
	std::vector<Vec2> patrolPoints = {
		Vec2(position.x, position.y),												// 第一个点
		Vec2(position.x + PATROL_OFFSET, position.y),								// 第二个点
		Vec2(position.x + PATROL_OFFSET/2, position.y + sin(M_PI/3)*(PATROL_OFFSET))				// 第三个点（高为50 * sin(60°) ≈ 43.3）
	};

	// 创建并设置巡逻移动行为
	PatrolMovement* patrolMovement = PatrolMovement::create(patrolPoints, 100.0f, true);
	if (patrolMovement) {
		setMovementBehavior(patrolMovement);
	}

	return Pig::initWithFile(PIG);
}

// 构造函数
Pig::Pig(const Vec2& position) :
	Animal(position) {
	truffleCount = 0;
}

// 析构函数
Pig::~Pig() {
}

// 获取松露数量
int Pig::getTruffleCount() const {
	return truffleCount;
}

// 设置移动行为
void Pig::setMovementBehavior(MovementBehavior* behavior) {
	if (behavior) {
		dynamic_cast<PatrolMovement*>(behavior)->execute(this);
	}
}