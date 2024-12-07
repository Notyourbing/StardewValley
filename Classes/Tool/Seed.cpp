#include "Seed.h"
#include "cocos2d.h"

USING_NS_CC;

Seed* Seed::create() {
    Seed* seed = new (std::nothrow) Seed();
    if (seed && seed->init()) {
        seed->autorelease();
        return seed;
    }
    CC_SAFE_DELETE(seed);
    return nullptr;
}

bool Seed::init() {
    // 调用基类的初始化方法
    return Tool::init("seed");
}

void Seed::useItem() {
    return;
}