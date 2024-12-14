#include "Cow.h"
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
	return Cow::initWithFile(COW);
}

// Cow类：构造函数
Cow::Cow(Vec2 position) :
	Animal(position) {
	milkProduction = 0;
}

// Cow类：析构函数
Cow::~Cow() {
}