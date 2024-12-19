#include "Pig.h"
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