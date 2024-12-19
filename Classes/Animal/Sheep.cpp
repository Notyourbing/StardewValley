#include "Sheep.h"
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
	return Sheep::initWithFile(SHEEP);
}

// 构造函数
Sheep::Sheep(const Vec2& position) :
	Animal(position) {
	woolProduction = 0;
}

// 析构函数
Sheep::~Sheep() {
}