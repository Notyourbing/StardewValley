#include "Chicken.h"
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