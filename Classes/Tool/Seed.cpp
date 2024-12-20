/****************************************************************
 * File Function: 种子物品类的具体实现
 * Author:        高鑫
 ****************************************************************/
#include "Seed.h"
#include "cocos2d.h"

USING_NS_CC;

// 初始化
bool Seed::init(const SeedType& seedType) {
    // 对于不同的种类进行初始化
    switch (seedType){ 
    case SeedType::DogbaneSeed:
        seedName = "dogbaneSeed";
        return Tool::init({ "dogbaneSeed", DOGBANE_SEED});
        break;
    case SeedType::CornSeed:
        seedName = "cornSeed";
        return Tool::init({ "cornSeed", CORN_SEED});
        break;
    case SeedType::CarrotSeed:
        seedName = "carrotSeed";
        return Tool::init({ "carrotSeed", CARROT_SEED});
        break;
    }
    return false;
}

void Seed::useItem() {
    return;
}

// 静态创建函数
DogbaneSeed* DogbaneSeed::create() {
    DogbaneSeed* seed = new (std::nothrow) DogbaneSeed();
    if (seed && seed->init(SeedType::DogbaneSeed)) {
        seed->autorelease();
        return seed;
    }
    CC_SAFE_DELETE(seed);
    return nullptr;
}

// 静态创建函数
CornSeed* CornSeed::create() {
    CornSeed* seed = new (std::nothrow) CornSeed();
    if (seed && seed->init(SeedType::CornSeed)) {
        seed->autorelease();
        return seed;
    }
    CC_SAFE_DELETE(seed);
    return nullptr;
}

// 静态创建函数
CarrotSeed* CarrotSeed::create() {
    CarrotSeed* seed = new (std::nothrow) CarrotSeed();
    if (seed && seed->init(SeedType::CarrotSeed)) {
        seed->autorelease();
        return seed;
    }
    CC_SAFE_DELETE(seed);
    return nullptr;
}
